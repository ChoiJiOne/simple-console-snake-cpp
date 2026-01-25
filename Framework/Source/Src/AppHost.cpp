#include "AppHost.h"

AppHost::~AppHost()
{
	if (_isInitialized)
	{
		Shutdown();
	}
}

Result<void> AppHost::Startup()
{
	if (_isInitialized)
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::ALREADY_INITIALIZED, "FAILED_TO_STARTUP_FRAMEWORK_APP"));
	}

	ConsoleManager& consoleMgr = ConsoleManager::Get();
	Result<void> resultConsoleMgrStartup = consoleMgr.Startup();
	if (!resultConsoleMgrStartup.IsSuccess())
	{
		return resultConsoleMgrStartup;
	}

	InputManager& inputMgr = InputManager::Get();
	Result<void> resultInputMgrStartup = inputMgr.Startup();
	if (!resultInputMgrStartup.IsSuccess())
	{
		return resultInputMgrStartup;
	}

	ActorManager& actorMgr = ActorManager::Get();
	Result<void> resultActorMgrStartup = actorMgr.Startup();
	if (!resultActorMgrStartup.IsSuccess())
	{
		return resultActorMgrStartup;
	}

	_isInitialized = true;
	return Result<void>::Success();
}

Result<void> AppHost::Run(IGame& game)
{
	AppContext ctx(ActorManager::GetPtr(), ConsoleManager::GetPtr(), InputManager::GetPtr());
	ctx.SetRequestQuit([this]() { _isQuit = true; });

	Result<void> resultStartup = game.OnStartup(ctx);
	if (!resultStartup.IsSuccess())
	{
		return resultStartup;
	}

	while (!_isQuit)
	{
		UpdateTick(ctx.GetInputManager());
		game.OnPreTick(ctx, _timer.GetDeltaSeconds());
		game.OnTick(ctx, _timer.GetDeltaSeconds());
		game.OnPostTick(ctx, _timer.GetDeltaSeconds());
	}

	Result<void> resultShutdown = game.OnShutdown(ctx);
	if (!resultShutdown.IsSuccess())
	{
		return resultShutdown;
	}

	return Result<void>::Success();
}

Result<void> AppHost::Shutdown()
{
	if (!_isInitialized)
	{
		return Result<void>::Fail(MAKE_ERROR(EErrorCode::NOT_INITIALIZED, "FAILED_TO_SHUTDOWN_FRAMEWORK_APP"));
	}

	ActorManager& actorMgr = ActorManager::Get();
	Result<void> resultActorMgrShutdown = actorMgr.Shutdown();
	if (!resultActorMgrShutdown.IsSuccess())
	{
		return resultActorMgrShutdown;
	}

	InputManager& inputMgr = InputManager::Get();
	Result<void> resultInputMgrShutdown = inputMgr.Shutdown();
	if (!resultInputMgrShutdown.IsSuccess())
	{
		return resultInputMgrShutdown;
	}

	ConsoleManager& consoleMgr = ConsoleManager::Get();
	Result<void> resultConsoleMgrShutdown = consoleMgr.Shutdown();
	if (!resultConsoleMgrShutdown.IsSuccess())
	{
		return resultConsoleMgrShutdown;
	}

	_isInitialized = false;
	return Result<void>::Success();
}

void AppHost::UpdateTick(InputManager* inputMgr)
{
	_timer.Tick();
	if (inputMgr != nullptr)
	{
		inputMgr->Tick();
	}
}