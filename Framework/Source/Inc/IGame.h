#pragma once

#include "AppContext.h"
#include "Result.h"

class IGame
{
public:
	virtual Result<void> OnStartup(const AppContext& appCtx) = 0;
	virtual void OnPreTick(const AppContext& appCtx, float deltaSeconds) = 0;
	virtual void OnTick(const AppContext& appCtx, float deltaSeconds) = 0;
	virtual void OnPostTick(const AppContext& appCtx, float deltaSeconds) = 0;
	virtual Result<void> OnShutdown(const AppContext& appCtx) = 0;
};