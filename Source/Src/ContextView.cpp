#include "ContextView.h"
#include "GameAssert.h"
#include "ConsoleManager.h"

ContextView::ContextView(GameContext* context)
{
	GAME_CHECK(context != nullptr);
	_consoleMgr = ConsoleManager::GetPtr();
	_context = context;
	_tileCharMap =
	{
		{ ETile::EMPTY, ' ' },
		{ ETile::WALL, '#' },
		{ ETile::BODY, 'o' },
		{ ETile::HEAD, '@' },
		{ ETile::FOOD, '*' },
	};

	_isInitialized = true;
}

ContextView::~ContextView() {}

void ContextView::Tick(float deltaSeconds)
{
}

void ContextView::Render()
{
	if (!_context->IsDirty())
	{
		return;
	}

	_consoleMgr->MoveCursor(0, 0);
	int32_t rowSize = _context->GetRowSize();
	int32_t colSize = _context->GetColSize();

	for (int32_t y = 0; y < rowSize; ++y)
	{
		for (int32_t x = 0; x < colSize; ++x)
		{
			auto it = _tileCharMap.find(_context->GetTile(x, y));
			if (it != _tileCharMap.end())
			{
				_consoleMgr->Print(x, y, it->second);
			}
		}
	}

	_context->SetDirty(false);
}

void ContextView::Release()
{
	if (_isInitialized)
	{
		return;
	}

	_consoleMgr = nullptr;
	_context = nullptr;
	_isInitialized = false;
}