#include "ConsoleManager.h"
#include "GameAssert.h"
#include "InputManager.h"
#include "Snake.h"

Snake::Snake(GameContext* context, int32_t defaultBodyCount, EMoveDirection defaultMoveDirection, float moveIntervalTime)
	: _moveDirection(defaultMoveDirection)
	, _moveIntervalTime(moveIntervalTime)
{
	GAME_CHECK(context != nullptr);
	_context = context;

	_inputMgr = InputManager::GetPtr();
	GAME_CHECK(_inputMgr != nullptr);
		
	_keyDirectionMap =
	{
		{ EKey::NONE,  EMoveDirection::NONE },
		{ EKey::LEFT,  EMoveDirection::LEFT},
		{ EKey::RIGHT, EMoveDirection::RIGHT},
		{ EKey::UP,    EMoveDirection::UP },
		{ EKey::DOWN,  EMoveDirection::DOWN},
	};

	_head = { _context->GetColSize() / 2, _context->GetRowSize() / 2};
	_context->SetTile(_head, ETile::HEAD);

	for (int32_t count = 1; count <= defaultBodyCount; ++count)
	{
		Position position = _head;
		position.x += (_moveDirection == EMoveDirection::LEFT) ? count : (_moveDirection == EMoveDirection::RIGHT) ? -count : 0;
		position.y += (_moveDirection == EMoveDirection::DOWN) ? count : (_moveDirection == EMoveDirection::UP) ? -count : 0;

		AddBody(position);
	}

	_isInitialized = true;
}

Snake::~Snake() {}

void Snake::Tick(float deltaSeconds)
{
	if (_isDead)
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
			_isDead = true;
		}
		return;
	}

	Move();
}

void Snake::Render()
{
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

		if (_inputMgr->GetKeyPress(key) == EPress::PRESSED  && _moveDirection != direction)
		{
			isUpdate = true;
			_moveDirection = direction;
		}
	}

	return isUpdate;
}

EMoveResult Snake::Move()
{
	_moveElapsedTime = 0.0f;

	Position cacheHead = _head;
	EMoveResult result = _context->Move(_head, _moveDirection);
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
		_bodys.push_back(tail);
		_context->SetTile(tail, ETile::BODY);
	}

	return result;
}