#pragma once

#include <cstdint>
#include <string>

#include "IManager.h"

class ConsoleManager : public IManager<ConsoleManager>
{
public:
	DISALLOW_COPY_AND_ASSIGN(ConsoleManager);

	void Startup();
	virtual void Shutdown() override;
	
	void MoveCursor(int32_t x, int32_t y);
	void SetVisibleCursor(bool isVisible);
	void SetTitle(const std::string_view& title);

	void Print(int32_t x, int32_t y, char c);
	void Print(int32_t x, int32_t y, const std::string_view& str);

private:
	friend class IManager<ConsoleManager>;
	
	ConsoleManager() = default;
	virtual ~ConsoleManager() = default; // 반드시 Shutdown을 통해 리소스 정리.

private:
	void* _outputHandle = nullptr;
};