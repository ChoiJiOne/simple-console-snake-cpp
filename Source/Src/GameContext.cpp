#include <cassert>

#include "ConsoleManager.h"
#include "GameContext.h"

GameContext::GameContext()
{
	_tiles = std::vector<ETile>(_rowSize * _colSize, ETile::EMPTY);
	_tileCharMap = 
	{
		{ ETile::EMPTY, ' ' },
		{ ETile::WALL, '#' },
		{ ETile::BODY, 'o' },
		{ ETile::HEAD, '@' },
		{ ETile::FOOD, '*' },
	};

	for (int y = 0; y < _rowSize; ++y)
	{
		for (int x = 0; x < _colSize; ++x)
		{
			if (IsOutline(x, y))
			{
				SetTile(x, y, ETile::WALL);
			}
		}
	}
}

GameContext::~GameContext()
{
}

void GameContext::Render()
{
	if (!_isDirty)
	{
		return;
	}

	ConsoleManager::Get().MoveCursor(0, 0);

	for (int y = 0; y < _rowSize; ++y)
	{
		for (int x = 0; x < _colSize; ++x)
		{
			int32_t offset = y * _colSize + x;

			auto it = _tileCharMap.find(_tiles[offset]);
			if (it != _tileCharMap.end())
			{
				std::cout << it->second;
			}
		}

		std::cout << "\n";
	}

	_isDirty = false;
}

void GameContext::SetTile(int32_t x, int32_t y, const ETile& tile)
{
	assert(IsValidTile(x, y));

	int32_t offset = y * _colSize + x;
	if (_tiles[offset] == tile)
	{
		return;
	}

	_tiles[offset] = tile;
	_isDirty = true;
}

const ETile& GameContext::GetTile(int32_t x, int32_t y)
{
	assert(IsValidTile(x, y));

	int32_t offset = y * _colSize + x;
	return _tiles[offset];
}

bool GameContext::IsOutline(int32_t x, int32_t y)
{
	return (x <= 0 || x >= _colSize - 1) || (y <= 0 || y >= _rowSize - 1);
}

bool GameContext::IsValidTile(int32_t x, int32_t y)
{
	return (0 <= x && x <= _colSize - 1) && (0 <= y || y <= _rowSize - 1);
}
