#include "ConsoleManager.h"
#include "GameAssert.h"
#include "LevelView.h"
#include "StringUtils.h"

LevelView::LevelView(GameContext* context)
{
	GAME_CHECK(context != nullptr);
	_context = context;
	_consoleMgr = ConsoleManager::GetPtr();

	_levelViewPosition = { 22, 5 };
	_isInitialized = true;
}

LevelView::~LevelView() {}

void LevelView::Tick(float deltaSeconds)
{
	const LevelInfo& levelInfo = _context->GetCurrentLevelInfo();
	int32_t currentLevel = levelInfo.GetLevel();
	if (currentLevel != _level)
	{
		_level = currentLevel;
		_isDirty = true;
	}
}

void LevelView::Render()
{
	if (!_isDirty)
	{
		return;
	}

	_consoleMgr->Print(_levelViewPosition.x, _levelViewPosition.y, StringUtils::PrintF("LEVEL: %2d", _level));
	_isDirty = false;;
}

void LevelView::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_context = nullptr;
	_isInitialized = false;
}
