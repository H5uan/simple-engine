#include "PlayerSystem.h"

#include "GLib.h"
#include "Function/Framework/Component/Input.h"
#include "Function/Framework/ECSFramework/ComponentHandle.h"
#include "Function/Framework/ECSFramework/world.h"
#include "Function/Framework/Systems/Movement/Movement.h"

void PlayerSystem::Init()
{
	auto keyStateChangeCallback = [this](unsigned int i_VKeyID, bool bWentDown) {
		switch (i_VKeyID)
		{
		case 0x41: // 'A' key
			KEY_A_PRESSED = bWentDown;
			break;
		case 0x44: // 'D' key
			KEY_D_PRESSED = bWentDown;
			break;
		case 0x53: // 'S' key
			KEY_S_PRESSED = bWentDown;
			break;
		case 0x57: // 'W' key
			KEY_W_PRESSED = bWentDown;
			break;
		case 0x51: // 'Q' key, for quit
			if (bWentDown) Engine::RequestQuit();
			break;
		default:
			break;
		}
	};

	GLib::SetKeyStateChangeCallback(keyStateChangeCallback);
}

void PlayerSystem::Tick(float dt)
{
	for (const RXECS::Entity& entity : m_RegisteredEntities)
	{
		RXECS::ComponentHandle<MovementComponent> move_component;

		m_ParentWorld->Unpack(entity, move_component);

		auto setMoveDirection = [move_component](float x, float y) {
			move_component->m_MoveDirection = Engine::Math::Vector2(x, y);
			};

		auto setMoveLeft = std::bind_front(setMoveDirection, -1.0f, 0.0f);
		auto setMoveRight = std::bind_front(setMoveDirection, 1.0f, 0.0f);
		auto setMoveUp = std::bind_front(setMoveDirection, 0.0f, 1.0f);
		auto setMoveDown = std::bind_front(setMoveDirection, 0.0f, -1.0f);
		auto setMoveStop = std::bind_front(setMoveDirection, 0.0f, 0.0f);

		if (KEY_A_PRESSED) setMoveLeft();
		else if (KEY_D_PRESSED) setMoveRight();
		else if (KEY_W_PRESSED) setMoveUp();
		else if (KEY_S_PRESSED) setMoveDown();
		else setMoveStop();
	}
}

void PlayerSystem::Render()
{
}


