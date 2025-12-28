#include <cassert> // 임시로 기본적으로 제공하는 assert 사용.
#include <iostream>
#include <map>
#include <vector>

enum class ETile
{
	EMPTY = 0x00,
	WALL = 0x01,
};

class GameContext
{
public:
	GameContext()
	{
		_tiles = std::vector<ETile>(_rowSize * _colSize, ETile::EMPTY);
		_tileCharMap = 
		{
			{ ETile::EMPTY, ' ' },
			{ ETile::WALL, '#' },
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

	virtual ~GameContext() { }

	void Render()
	{
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
	}

private:
	bool IsOutline(int32_t x, int32_t y)
	{
		return (x <= 0 || x >= _colSize - 1) || (y <= 0 || y >= _rowSize - 1);
	}

	bool IsValidTile(int32_t x, int32_t y)
	{
		return (0 <= x && x <= _colSize - 1) && (0 <= y || y <= _rowSize - 1);
	}

	void SetTile(int32_t x, int32_t y, const ETile& tile)
	{
		assert(IsValidTile(x, y));

		int32_t offset = y * _colSize + x;
		_tiles[offset] = tile;
	}

private:
	int32_t _rowSize = 10; // 세로 크기
	int32_t _colSize = 10; // 가로 크기

	std::vector<ETile> _tiles;
	std::map<ETile, char> _tileCharMap;
};

int main(void)
{
	GameContext context;
	context.Render();

	return 0;
}