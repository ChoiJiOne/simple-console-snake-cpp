#include "IApp.h"
#include "GenericAssert.h"

IApp* IApp::_app = nullptr;

IApp::IApp()
{
	_app = this;
}

IApp::~IApp()
{
	if (_isInitialized)
	{
		Shutdown();
	}

	if (_app != nullptr)
	{
		_app = nullptr;
	}
}

void IApp::Startup()
{
	if (_isInitialized)
	{
		return;
	}

	_consoleMgr = ConsoleManager::GetPtr();
	_inputMgr = InputManager::GetPtr();
	_actorMgr = ActorManager::GetPtr();

	_consoleMgr->Startup();
	_inputMgr->Startup();
	_actorMgr->Startup();

	// NOTE: 하위 클래스에서 _isInitialized 값을 true로 설정.
}

void IApp::Run()
{
	_timer.Start();
	_isDoneLoop = false;

	while (!_isDoneLoop)
	{
		UpdateTick();
		if (_processTick != nullptr)
		{
			_processTick(_timer.GetDeltaSeconds());
		}
	}
}

void IApp::Shutdown()
{
	if (!_isInitialized)
	{
		return; // TODO: 에러 로그 처리 필요.
	}

	if (_actorMgr != nullptr)
	{
		_actorMgr->Shutdown();
		_actorMgr = nullptr;
	}

	if (_inputMgr != nullptr)
	{
		_inputMgr->Shutdown();
		_inputMgr = nullptr;
	}

	if (_consoleMgr != nullptr)
	{
		_consoleMgr->Shutdown();
		_consoleMgr = nullptr;
	}

	// NOTE: 여기에서 _isInitialized 값을 false로 설정.
	_isInitialized = false;
}

void IApp::UpdateTick()
{
	_timer.Tick();
	_inputMgr->Tick();
}