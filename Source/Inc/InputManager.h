#pragma once

#include "IManager.h"

class InputManager : public IManager<InputManager>
{
public:
	DISALLOW_COPY_AND_ASSIGN(InputManager);

	void Startup();
	virtual void Shutdown() override;

private:
	friend class IManager<InputManager>;

	InputManager() = default;
	virtual ~InputManager() = default; // 반드시 Shutdown을 통해 리소스 정리.
};