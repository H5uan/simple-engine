#pragma once

#include <bitset>
#include <vector>
#include "ComponentHash.h"
#include "Entity.h"

/*
 * Systems are where the bulk of the game interaction code goes.
 */
namespace RXECS
{
    class World;

    class ISystem
    {
    public:
        ISystem() = default;
        virtual ~ISystem() = default;
        ISystem(const ISystem&) = default;
        ISystem& operator=(const ISystem&) = default;
        ISystem(ISystem&&) noexcept = default;
        ISystem& operator=(ISystem&&) = default;

        /*
         * Called before the game starts but after the world initializes
         */
        virtual void Init() =0;

        /*
         * Called every game update
         */
        virtual void Tick(float dt) = 0;

        /*
         * Called every frame
         */
        virtual void Render() = 0;

        /*
         * When a system is added to the world, the world will register itself
         */
        void RegisterWorld(World* world);

        /*
         * When a component is added such that this system should begin acting on it,
         * register will be called.
         */
        void RegisterEntity(Entity const& entity);

        /*
         * If a component is removed from an entity such that the system should stop
         * acting on it, unRegister will be called.
         */
        void UnRegisterEntity(Entity const& entity);
        ComponentHash GetSignature() const;

    protected:
        std::vector<Entity> m_RegisteredEntities;
        World* m_ParentWorld;
        ComponentHash m_Signature;
    };
}
