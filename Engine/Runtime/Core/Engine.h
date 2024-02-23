#pragma once
#include "Function/Framework/ECSFramework/RXECS.h"
#include <Windows.h>
#include <GLib.h>
#include <Function/Framework/Object/PlayerObject.h>

namespace Engine
{
    static bool s_Quit;

    bool StartUp(HINSTANCE i_hInstance, int i_CmdShow, const char* i_pWindowName,
                 unsigned int i_WindowWidth, unsigned int i_WindowHeight);

    void Run();

    void Shutdown();

    void RequestQuit();

    inline RXECS::EntityManager entity_manager;
    inline std::unique_ptr<RXECS::World> world;
    inline std::unique_ptr<Player> player;
    inline GLib::Sprite* pGoodGuy;
}
