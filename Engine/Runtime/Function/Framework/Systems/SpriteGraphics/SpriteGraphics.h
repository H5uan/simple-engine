#pragma once

#include "Core/Math/MathUtil.h"
#include "Core/Math/Vector2.h"
#include "Function/Framework/ECSFramework/RXECS.h"
#include "GLib.h"
#include "..\..\Component\MovementComponent.h"
#include "Function/Framework/Component/SpriteRenderer.h"


class SpriteGraphics : public RXECS::ISystem
{
public:
    SpriteGraphics()
    {
        m_Signature.AddComponent<SpriteRenderable>();
        m_Signature.AddComponent<CommonComponent>();
    }

    ~SpriteGraphics() override = default;
    void Init() override;

    void Tick(float dt) override;

    void Render() override;
};
