#include "StringUtils.h"

#include "GameRenderer.h"

GameRenderer::GameRenderer(ConsoleManager* consoleMgr, GameContext* gameCtx)
	: _consoleMgr(consoleMgr)
	, _gameCtx(gameCtx)
{
	_tileCharMap =
	{
		{ ETile::EMPTY, ' ' },
		{ ETile::WALL, '#' },
		{ ETile::BODY, 'o' },
		{ ETile::HEAD, '@' },
		{ ETile::FOOD, '*' },
	};

	_currentScoreViewPosition = { 22, 3 };
	_bestScoreViewPosition = { 22, 4 };
}

GameRenderer::~GameRenderer() {}

void GameRenderer::Render()
{
	RenderTile();
	RenderScore();
	RenderBestScore();

}

void GameRenderer::RenderTile()
{
	if (!_gameCtx->IsDirtyTile())
	{
		return;
	}

	_consoleMgr->MoveCursor(0, 0);
	int32_t rowSize = _gameCtx->GetRowSize();
	int32_t colSize = _gameCtx->GetColSize();

	for (int32_t y = 0; y < rowSize; ++y)
	{
		for (int32_t x = 0; x < colSize; ++x)
		{
			auto it = _tileCharMap.find(_gameCtx->GetTile(x, y));
			if (it != _tileCharMap.end())
			{
				_consoleMgr->Print(x, y, it->second);
			}
		}
	}

	_gameCtx->SetDirtyTile(false);
}

void GameRenderer::RenderScore()
{
	if (!_gameCtx->IsDirtyScore())
	{
		return;
	}

	int32_t score = _gameCtx->GetCurrentScore();
	_consoleMgr->Print(_currentScoreViewPosition.x, _currentScoreViewPosition.y, StringUtils::PrintF("FOOD: %3d", score));
	_gameCtx->SetDirtyScore(false);
}

void GameRenderer::RenderBestScore()
{
	if (!_gameCtx->IsDirtyBestScore())
	{
		return;
	}

	int32_t bestScore = _gameCtx->GetBestScore();
	_consoleMgr->Print(_bestScoreViewPosition.x, _bestScoreViewPosition.y, StringUtils::PrintF("BEST: %3d", bestScore));
	_gameCtx->SetDirtyBestScore(false);
}
