#include "Engine.h"
#include "Core/Time/Time.h"
#include "Core/Time/Updater.h"
#include "Function/Framework/Component/Input.h"

#include "Function/Framework/Component/Input.h"
#include "..\Function\Framework\Component\MovementComponent.h"
#include "Function/Framework/Component/SpriteRenderer.h"
#include "Resource/SpriteLoader.h"
#include <Function/Framework/Object/PlayerObject.h>
#include <Function/Framework/Systems/SpriteGraphics/SpriteGraphics.h>
#include <Function/Framework/Systems/PlayerSystem/PlayerSystem.h>
#include <Function/Framework/Systems/Movement/Movement.h>


namespace Engine
{
    bool StartUp(HINSTANCE i_hInstance, int i_nCmdShow, const char* i_pWindowName,
                 unsigned int i_WindowWidth, unsigned int i_WindowHeight)
    {
        const bool b_Success = GLib::Initialize(
            i_hInstance,
            i_nCmdShow,
            i_pWindowName,
            -1,
            i_WindowWidth,
            i_WindowHeight,
            true
        );
        assert(b_Success);

        Time::Updater::Create();

        world = std::make_unique<RXECS::World>(
            std::make_unique<RXECS::EntityManager>()
        );
        auto renderSystem = std::make_unique<SpriteGraphics>();
        auto playerSystem = std::make_unique<PlayerSystem>();
        auto movementSystem = std::make_unique<MovementSystem>();

        Engine::world->AddSystem(std::move(renderSystem));
        Engine::world->AddSystem(std::move(playerSystem));
        Engine::world->AddSystem(std::move(movementSystem));

        player = std::make_unique<Player>(*world);
        player->Initialize("Data/player.json");

        world->Init();

        s_Quit = false;

        return true;
    }

    void Run()
    {
        static constexpr float desired_dt = 1000.f / 60.f;
        
        // Get tickable system
        static Engine::Time::Updater* updater = Engine::Time::Updater::Get();

        while (!s_Quit)
        {
            const float dt = Engine::Time::CalculateLastFrameTime_ms();

            GLib::Service(s_Quit);

            world->Render();
            world->Tick(dt);
        }
    }

    void Shutdown()
    {
        Engine::Time::Updater::Destroy();

        GLib::Shutdown();
        s_Quit = true;
    }

    void RequestQuit()
    {
        s_Quit = true;
    }
}
