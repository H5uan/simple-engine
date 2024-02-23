#pragma once

namespace Engine::Time
{
    class ITickable
    {
    public:
        virtual ~ITickable() = default;
        virtual void Tick(float dt) = 0;
    };
}
