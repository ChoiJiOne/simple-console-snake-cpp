#include "ConsoleManager.h"
#include "GameAssert.h"
#include "Snake.h"

Snake::Snake(GameContext* context, int32_t defaultBodyCount, EMoveDirection defaultMoveDirection)
	: _moveDirection(defaultMoveDirection)
{
	GAME_CHECK(context != nullptr);
	_context = context;

	_head = { _context->GetColSize() / 2, _context->GetRowSize() / 2};
	_context->SetTile(_head, ETile::HEAD);

	for (int32_t count = 1; count <= defaultBodyCount; ++count)
	{
		Position position = _head;
		position.x += (_moveDirection == EMoveDirection::LEFT) ? count : (_moveDirection == EMoveDirection::RIGHT) ? -count : 0;
		position.y += (_moveDirection == EMoveDirection::DOWN) ? count : (_moveDirection == EMoveDirection::UP) ? -count : 0;

		if (_context->IsValidTile(position))
		{
			_bodys.push_back(position);
			_context->SetTile(position, ETile::BODY);
		}
	}

	_isInitialized = true;
}

Snake::~Snake() {}

void Snake::Tick(float deltaSeconds)
{
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
