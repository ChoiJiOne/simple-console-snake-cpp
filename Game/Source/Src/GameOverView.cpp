#include "ConsoleManager.h"
#include "GenericAssert.h"

#include "GameOverView.h"
#include "StringUtils.h"

GameOverView::GameOverView(GameContext* context)
{
	CHECK(context != nullptr);
	_context = context;
	_consoleMgr = ConsoleManager::GetPtr();

	_gameOverText = "GAME OVER";
	_gameOverPosition = { 5, 7 };

	_foodText = "FOOD: %d";
	_foodPosition = { 5, 9 };

	_levelText = "LEVEL: %d";
	_levelPosition = { 5, 10 };

	_gameStartKeyText = "PRESS SPACE KEY";
	_gameStartKeyViewPosition = { 3, 12 };

	_isInitialized = true;
}

GameOverView::~GameOverView() {}

void GameOverView::Tick(float deltaSeconds)
{
}

void GameOverView::Render()
{
	if (!_isDirty)
	{
		return;
	}

	_consoleMgr->Print(_gameOverPosition.x, _gameOverPosition.y, _gameOverText);
	_consoleMgr->Print(_foodPosition.x, _foodPosition.y, StringUtils::PrintF(_foodText.c_str(), _context->GetSpawnedFoodCount() - 1));
	_consoleMgr->Print(_levelPosition.x, _levelPosition.y, StringUtils::PrintF(_levelText.c_str(), _context->GetCurrentLevelInfo().GetLevel()));
	_consoleMgr->Print(_gameStartKeyViewPosition.x, _gameStartKeyViewPosition.y, _gameStartKeyText);

	_isDirty = false;
}

void GameOverView::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_context = nullptr;
	_isInitialized = false;
}

void GameOverView::Reset()
{
	_isDirty = true;
}