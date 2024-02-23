#pragma once
#include <vector>

#include "ITickable.h"

namespace Engine::Time
{
    class Updater
    {
    private:
        Updater();
        ~Updater();
        static Updater* m_Instance;

    public:
        static Updater* Create();
        static void Destroy();
        static Updater* Get() { return m_Instance; }

        void AddTickable(ITickable* tickable)
        {
            if (std::ranges::find(m_Tickables, tickable) != m_Tickables.end())
            {
                return;
            }

            m_Tickables.push_back(tickable);
            ++m_NumTickables;
        }

        void RemoveTickable(ITickable* tickable)
        {
            const auto it = std::ranges::find(m_Tickables, tickable);
            if (it == m_Tickables.end())
            {
                return;
            }

            m_Tickables.erase(it);
            --m_NumTickables;
        }

        // tick process
        void Run(float dt);

    public:
        size_t m_NumTickables;
        std::vector<ITickable*> m_Tickables;
    };
}
