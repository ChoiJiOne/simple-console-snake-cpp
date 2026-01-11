#include "ConsoleManager.h"
#include "GenericAssert.h"
#include "FoodView.h"
#include "StringUtils.h"

FoodView::FoodView(GameContext* context)
{
	CHECK(context != nullptr);
	_context = context;
	_consoleMgr = ConsoleManager::GetPtr();

	_countViewPosition = { 22, 3 };
	_isInitialized = true;
}

FoodView::~FoodView() {}

void FoodView::Tick(float deltaSeconds)
{
	int32_t count = _context->GetSpawnedFoodCount();
	if (count > 0 && _count != count)
	{
		_count = count;
		_isDirty = true;
	}
}

void FoodView::Render()
{
	if (!_isDirty)
	{
		return;
	}

	_consoleMgr->Print(_countViewPosition.x, _countViewPosition.y, StringUtils::PrintF("FOOD: %3d", _count - 1));
	_isDirty = false;
}

void FoodView::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_context = nullptr;
	_isInitialized = false;
}