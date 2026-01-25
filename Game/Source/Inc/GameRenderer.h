#pragma once

#include <map>

#include "Macro.h"
#include "ConsoleManager.h"

#include "GameContext.h"

class GameRenderer
{
public:
	GameRenderer(ConsoleManager* consoleMgr, GameContext* gameCtx);
	virtual ~GameRenderer();

	DISALLOW_COPY_AND_ASSIGN(GameRenderer);

	void Render();

private:
	void RenderTile();
	void RenderScore();
	void RenderBestScore();
	
private:
	ConsoleManager* _consoleMgr = nullptr;
	GameContext* _gameCtx = nullptr;

	std::map<ETile, char> _tileCharMap;

	Position _currentScoreViewPosition = { 0, 0 };
	Position _bestScoreViewPosition = { 0, 0 };
};