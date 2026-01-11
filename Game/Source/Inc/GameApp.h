#pragma once

#include "IApp.h"
#include "GameContext.h"

enum class EGameState
{
	NONE = 0x00,
	READY = 0x01,
	PLAY = 0x02,
};

class GameApp : public IApp
{
public:
	GameApp() = default;
	virtual ~GameApp();

	DISALLOW_COPY_AND_ASSIGN(GameApp);

	virtual void Startup() override;
	virtual void Shutdown() override;

	void SetGameState(const EGameState& gameState, bool bNeedAction = true);
	const EGameState& GetGameState() const { return _gameState; }

private:
	void SetGameStateActors(
		const EGameState& gameState, 
		const std::vector<IActor*>& updateActors, 
		const std::vector<IActor*>& renderActors,
		const std::function<void()>& action
	);
	void ProcessTick(float deltaSeconds);

private:
	EGameState _gameState = EGameState::READY;
	GameContext _context;

	std::map<EGameState, std::function<void()>> _actionMap;
	std::map<EGameState, std::vector<IActor*>> _updateActorsMap;
	std::map<EGameState, std::vector<IActor*>> _renderActorsMap;
};