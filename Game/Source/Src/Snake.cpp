#include "GenericAssert.h"
#include "InputManager.h"

#include "Snake.h"

Snake::Snake(GameContext* context, int32_t defaultBodyCount, EMoveDirection defaultMoveDirection)
	: _defaultBodyCount(defaultBodyCount)
	, _defaultMoveDirection(defaultMoveDirection)
	, _prevMoveDirection(defaultMoveDirection)
	, _currMoveDirection(defaultMoveDirection)
{
	CHECK(context != nullptr);
	_context = context;

	_inputMgr = InputManager::GetPtr();
	CHECK(_inputMgr != nullptr);

	_keyDirectionMap =
	{
		{ EKey::LEFT,  EMoveDirection::LEFT},
		{ EKey::RIGHT, EMoveDirection::RIGHT},
		{ EKey::UP,    EMoveDirection::UP },
		{ EKey::DOWN,  EMoveDirection::DOWN},
	};

	_isInitialized = true;
}

Snake::~Snake() {}

void Snake::Tick(float deltaSeconds)
{
	if (_context->IsGameOver())
	{
		return;
	}

	if (!UpdateMoveDirection())
	{
		_moveElapsedTime += deltaSeconds;
		if (_moveElapsedTime < _moveIntervalTime)
		{
			return;
		}

		EMoveResult result = Move();
		if (result == EMoveResult::BLOCKED)
		{
			_context->SetGameOver(true);
		}
		else
		{
			_moveElapsedTime = 0.0f;
		}
		return;
	}

	EMoveResult result = Move();
	if (result == EMoveResult::BLOCKED)
	{
		_currMoveDirection = _prevMoveDirection; // NOTE: 해당 향으로 움직일 수 없으므로, 복원.
	}
	else
	{
		_moveElapsedTime = 0.0f;
		_prevMoveDirection = _currMoveDirection;
	}
}

void Snake::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_context = nullptr;
	_isInitialized = false;
}

void Snake::Reset()
{
	_prevMoveDirection = _defaultMoveDirection;
	_currMoveDirection = _defaultMoveDirection;

	_head = { _context->GetColSize() / 2, _context->GetRowSize() / 2 };
	_context->SetTile(_head, ETile::HEAD);

	ClearBodys();
	for (int32_t count = 1; count <= _defaultBodyCount; ++count)
	{
		Position position = _head;
		position.x += (_currMoveDirection == EMoveDirection::LEFT) ? count : (_currMoveDirection == EMoveDirection::RIGHT) ? -count : 0;
		position.y += (_currMoveDirection == EMoveDirection::DOWN) ? count : (_currMoveDirection == EMoveDirection::UP) ? -count : 0;

		AddBody(position);
	}
}

void Snake::ClearBodys()
{
	_bodys.clear();
}

void Snake::AddBody(const Position& position)
{
	if (!_context->IsValidTile(position))
	{
		return;
	}

	_bodys.push_back(position);
	_context->SetTile(position, ETile::BODY);
}

bool Snake::UpdateMoveDirection()
{
	bool isUpdate = false;
	for (const auto& keyDirection : _keyDirectionMap)
	{
		const EKey& key = keyDirection.first;
		const EMoveDirection& direction = keyDirection.second;

		if (_inputMgr->GetKeyPress(key) == EPress::PRESSED && _currMoveDirection != direction)
		{
			isUpdate = true;
			_currMoveDirection = direction;
		}
	}

	return isUpdate;
}

EMoveResult Snake::Move()
{
	Position cacheHead = _head;
	EMoveResult result = _context->Move(_head, _currMoveDirection);
	if (result == EMoveResult::BLOCKED)
	{
		return result;
	}

	Position tail = _bodys.back();
	_bodys.pop_back();
	_bodys.push_front(cacheHead);
	_context->Swap(tail, cacheHead);

	if (result == EMoveResult::CONSUME)
	{
		if (!_context->TrySpawnFood())
		{
			_context->SetGameOver(true); // NOTE: 먹이를 더 이상 생성할 수 없는 상황이라면 강제 GAME OVER.
			return result;
		}

		AddBody(tail);
	}

	return result;
}