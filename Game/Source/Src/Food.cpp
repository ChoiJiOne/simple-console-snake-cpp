#include "ConsoleManager.h"
#include "GameAssert.h"
#include "Food.h"
#include "MathUtils.h"
#include "StringUtils.h"

Food::Food(GameContext* context)
{
	GAME_CHECK(context != nullptr);
	_context = context;
	_consoleMgr = ConsoleManager::GetPtr();

	_context->TrySpawnFood(_position); // CHECKME: 이거 실패했을 때 처리 필요한 지 확인 필요.
	_count = _context->GetSpawnedFoodCount();
	_isDirty = true; // CHECKME: 이거 없으면 0개일 때 표시 안함.

	_countViewPosition = { 22, 3 };
	_isInitialized = true;
}

Food::~Food() {}

void Food::Tick(float deltaSeconds)
{
	const ETile& tile = _context->GetTile(_position);
	if (tile != ETile::FOOD)
	{
		if (!_context->TrySpawnFood(_position))
		{
			// TODO: 여기에 게임 오버 처리 필요.
			return;
		}
		
		_count = _context->GetSpawnedFoodCount();
		_isDirty = true;
	}
}

void Food::Render()
{
	if (!_isDirty)
	{
		return;
	}

	_consoleMgr->Print(_countViewPosition.x, _countViewPosition.y, StringUtils::PrintF("FOOD: %3d", _count - 1));
	_isDirty = false;
}

void Food::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_context = nullptr;
	_isInitialized = false;
}