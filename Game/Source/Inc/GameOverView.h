#pragma once

#include "IActor.h"
#include "GameContext.h"

class ConsoleManager;

class GameOverView : public IActor
{
public:
	GameOverView(GameContext* context);
	virtual ~GameOverView();

	DISALLOW_COPY_AND_ASSIGN(GameOverView);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void Reset();

private:
	GameContext* _context = nullptr;
	ConsoleManager* _consoleMgr = nullptr;
	bool _isDirty = true;

	std::string _gameOverText;
	Position _gameOverPosition = { 0, 0 };

	std::string _foodText;
	Position _foodPosition = { 0, 0 };

	std::string _levelText;
	Position _levelPosition = { 0, 0 };

	std::string _gameStartKeyText;
	Position _gameStartKeyViewPosition = { 0, 0 };
};