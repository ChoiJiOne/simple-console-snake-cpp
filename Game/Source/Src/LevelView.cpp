#include "ConsoleManager.h"
#include "GameAssert.h"
#include "LevelView.h"
#include "StringUtils.h"

LevelView::LevelView(GameContext* context)
{
	GAME_CHECK(context != nullptr);
	_context = context;
	_consoleMgr = ConsoleManager::GetPtr();

	_levelViewPosition = { 21, 5 };
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

	Position consolePosition = _levelViewPosition;

	const std::vector<LevelInfo>& levelInfos = _context->GetLevelInfos();
	for (const auto& levelInfo : levelInfos)
	{
		int32_t level = levelInfo.GetLevel();
		char mark = level == _level ? '*' : ' ';

		_consoleMgr->Print(consolePosition.x, consolePosition.y, StringUtils::PrintF("%cLEVEL:%2d%c", mark, level, mark));
		consolePosition.y++;
	}

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
