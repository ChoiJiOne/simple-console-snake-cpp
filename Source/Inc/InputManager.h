#pragma once

#include <map>
#include <vector>

#include "IManager.h"

/**
 * --------------------------------------
 * | 이전 프레임 | 현재 프레임 | 입력 상태 |
 * --------------------------------------
 * |     0      |     0      | NONE     |
 * |     0      |     1      | PRESSED  |
 * |     1      |     0      | RELEASED |
 * |     1      |     1      | HELD     |
 * --------------------------------------
 */
enum class EPress : int32_t
{
	NONE = 0x00,
	PRESSED = 0x01,
	RELEASED = 0x02,
	HELD = 0x03
};

enum class EKey : int32_t
{
	NONE   = 0x00,
	SPACE  = 0x20,
	LEFT   = 0x25,
	UP     = 0x26,
	RIGHT  = 0x27,
	DOWN   = 0x28,
	ESCAPE = 0x1B,
};

class InputManager : public IManager<InputManager>
{
public:
	DISALLOW_COPY_AND_ASSIGN(InputManager);

	void Startup();
	virtual void Shutdown() override;

	void Tick();
	EPress GetKeyPress(const EKey& key);

private:
	friend class IManager<InputManager>;

	InputManager() = default;
	virtual ~InputManager() = default; // 반드시 Shutdown을 통해 리소스 정리.

	bool IsPressKey(const std::map<EKey, bool>& keyPressMap, const EKey& key);
		
private:
	std::vector<EKey> _keys;

	std::map<EKey, bool> _prevKeyPressMap;
	std::map<EKey, bool> _currKeyPressMap;
};