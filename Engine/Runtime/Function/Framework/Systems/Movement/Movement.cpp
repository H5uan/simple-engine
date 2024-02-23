#include "Movement.h"

#include "Function/Framework/Component/Input.h"
#include "Function/Framework/ECSFramework/ComponentHandle.h"
#include "Function/Framework/ECSFramework/world.h"

void MovementSystem::Init()
{
}

void MovementSystem::Tick(float dt)
{
    for (const RXECS::Entity& entity : m_RegisteredEntities)
    {
        RXECS::ComponentHandle<CommonComponent> common_component;
        RXECS::ComponentHandle<MovementComponent> movement_component;
        m_ParentWorld->Unpack(entity, common_component, movement_component);

        ApplyImpulse(common_component.component, movement_component.component,
                     movement_component->m_MoveDirection * IMPULSE_STRENTH);

        if (!movement_component->m_IsAwake)
        {
            continue;
        }

        Engine::Math::Vector2 prev_velocity = common_component->m_CurrentVelocity;
        common_component->m_CurrentVelocity += (
            common_component->m_CurrentVelocity * -movement_component->m_DragCoeff);

        if (common_component->m_CurrentVelocity.LengthSquared() > MIN_VELOCITY_LENGTH_SQUARED)
        {
            Engine::Math::Vector2 new_position = common_component->m_Position + ((prev_velocity + common_component
                ->m_CurrentVelocity) * 0.5f) * dt;
            new_position.x((new_position.x() < -1280 / 2)
                               ? 1280 / 2
                               : (new_position.x() > 1280 / 2
                                      ? -1280 / 2
                                      : new_position.x()));
            new_position.y((new_position.y() < -800 / 2)
                               ? 800 / 2
                               : (new_position.y() > 800 / 2
                                      ? -800 / 2
                                      : new_position.y()));

            common_component->m_Position = new_position;
        }
        else // stationary
        {
            common_component->m_CurrentVelocity = Engine::Math::Vector2::ZERO;
            prev_velocity = Engine::Math::Vector2::ZERO;
            movement_component->m_IsAwake = false;
        }
    }
}

void MovementSystem::Render()
{
}


void MovementSystem::ApplyImpulse(CommonComponent* i_CommonComponent, MovementComponent* i_MovementComponent,
                                  const Engine::Math::Vector2& impulse)
{
    if (impulse == Engine::Math::Vector2::ZERO) return;

    i_MovementComponent->m_IsAwake = true;

    Engine::Math::Vector2 new_velocity = i_CommonComponent->m_CurrentVelocity + (impulse * i_MovementComponent->
        m_InverseMass);
    i_CommonComponent->m_CurrentVelocity = new_velocity.LengthSquared() > MAX_VELOCITY_LENGTH_SQUARED
                                               ? i_CommonComponent->m_CurrentVelocity
                                               : new_velocity;
}
