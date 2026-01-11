#include "ConsoleManager.h"
#include "GenericAssert.h"
#include "StringUtils.h"

#include "ReadyView.h"

ReadyView::ReadyView()
{
	_consoleMgr = ConsoleManager::GetPtr();

	_titleText = "SNAKE";
	_titleViewPosition = { 8, 7 };

	_gameStartKeyText = "PRESS SPACE KEY";
	_gameStartKeyViewPosition = { 3, 10 };

	_isInitialized = true;
}

ReadyView::~ReadyView()
{
}

void ReadyView::Tick(float deltaSeconds)
{
}

void ReadyView::Render()
{
	if (!_isDirty)
	{
		return;
	}

	_consoleMgr->Print(_titleViewPosition.x, _titleViewPosition.y, _titleText);
	_consoleMgr->Print(_gameStartKeyViewPosition.x, _gameStartKeyViewPosition.y, _gameStartKeyText);

	_isDirty = false;
}

void ReadyView::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_isInitialized = false;
}