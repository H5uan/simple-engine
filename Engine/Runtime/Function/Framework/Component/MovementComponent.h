#pragma once
#include "Core/Math/Vector2.h"
#include "Function/Framework/ECSFramework/Component.h"

static constexpr float DEFAULT_MASS = 50.f;
static constexpr float DEFAULT_COEFF_DRAG = 0.09f;
static constexpr float MAX_COEFF_DRAG = 0.9f;
static constexpr float MIN_VELOCITY_LENGTH_SQUARED = 0.75f;
static constexpr float MAX_VELOCITY_LENGTH_SQUARED = 6.00f;
static constexpr int IMPULSE_STRENTH = static_cast<int>(50.f);

struct MovementComponent : RXECS::Component<MovementComponent>
{
    MovementComponent(float mass = DEFAULT_MASS, float drag_coeff = DEFAULT_COEFF_DRAG): m_Mass(mass),
        m_InverseMass((mass != 0.0f) ? 1.0f / mass : 0.0f),
        m_DragCoeff(drag_coeff)
    {
    }

    bool m_IsAwake = false;
    float m_Mass = DEFAULT_MASS;
    float m_InverseMass = (DEFAULT_MASS != 0.0f) ? 1.0f / DEFAULT_MASS : 0.0f;
    float m_DragCoeff = DEFAULT_COEFF_DRAG;
    Engine::Math::Vector2 m_MoveDirection = Engine::Math::Vector2::ZERO;
};

struct CommonComponent : RXECS::Component<CommonComponent>
{
    CommonComponent(float velocity, float position): m_CurrentVelocity(velocity), m_Position(position)
    {
    }

    Engine::Math::Vector2 m_CurrentVelocity = Engine::Math::Vector2::ZERO;
    Engine::Math::Vector2 m_Position = Engine::Math::Vector2::ZERO;
};
