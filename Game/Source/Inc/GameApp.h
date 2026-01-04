#pragma once

#include "IApp.h"
#include "GameContext.h"

enum class EGameState
{
	READY = 0x00,
	PLAYING = 0x01,
	PAUSE = 0x02,
	GAME_OVER = 0x03,
};

class GameApp : public IApp
{
public:
	GameApp() = default;
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;

private:
	void SetGameStateActors(
		const EGameState& gameState, 
		const std::vector<IActor*>& updateActors, 
		const std::vector<IActor*>& renderActors
	);

private:
	EGameState _gameState = EGameState::PLAYING;
	GameContext _context;

	std::map<EGameState, std::vector<IActor*>> _updateActorsMap;
	std::map<EGameState, std::vector<IActor*>> _renderActorsMap;
};