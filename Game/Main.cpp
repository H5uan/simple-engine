#include <Windows.h>
#include <ctime>

#if defined _DEBUG
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include <DirectXMath.h>
#include <DirectXColors.h>

#include "GLib.h"
#include "Core/Engine.h"


int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
    if (Engine::StartUp(i_hInstance,
                        i_nCmdShow,
                        "Monster Chase",
                        1280,
                        800
        )
    )
    {
        Engine::Run();
    }
    Engine::Shutdown();


#if defined _DEBUG
    _CrtDumpMemoryLeaks();
#endif // _DEBUG

    return 0;
}
