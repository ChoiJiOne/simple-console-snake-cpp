#pragma once

#include "IActor.h"
#include "GameContext.h"

class ConsoleManager;

class ReadyView : public IActor
{
public:
	ReadyView();
	virtual ~ReadyView();

	DISALLOW_COPY_AND_ASSIGN(ReadyView);

	virtual void Tick(float deltaSeconds) override;
	virtual void Render() override;
	virtual void Release() override;

	void Reset();

private:
	ConsoleManager* _consoleMgr = nullptr;
	bool _isDirty = true;

	std::string _titleText;
	Position _titleViewPosition = { 0, 0 };

	std::string _gameStartKeyText;
	Position _gameStartKeyViewPosition = { 0, 0 };
};