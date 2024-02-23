#include "Updater.h"

namespace Engine::Time
{
    Updater* Updater::m_Instance = nullptr;

    Updater::Updater() : m_NumTickables(0)
    {
    }

    Updater::~Updater() = default;

    Updater* Updater::Create()
    {
        if (!Updater::m_Instance)
        {
            Updater::m_Instance = new Updater();
        }
        return Updater::m_Instance;
    }

    void Updater::Destroy()
    {
        delete Updater::m_Instance;
    }

    

    void Updater::Run(float dt)
    {
        for (const auto tickable : m_Tickables)
        {
            tickable->Tick(dt);
        }
    }
}
