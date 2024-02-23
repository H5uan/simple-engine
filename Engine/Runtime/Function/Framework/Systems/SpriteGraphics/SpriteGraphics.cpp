#include "SpriteGraphics.h"

#include <DirectXColors.h>

#include "GLib.h"

void SpriteGraphics::Init()
{
}


void SpriteGraphics::Tick(float dt)
{
}

void SpriteGraphics::Render()
{
    GLib::BeginRendering(DirectX::Colors::Blue);
    GLib::Sprites::BeginRendering();

    for (const RXECS::Entity& entity : m_RegisteredEntities)
    {
        RXECS::ComponentHandle<SpriteRenderable> sprite_render_component;
        RXECS::ComponentHandle<CommonComponent> common_component;
        m_ParentWorld->Unpack(entity,  common_component,sprite_render_component);
        GLib::Point2D offset = {
            common_component->m_Position.x(),
            common_component->m_Position.y()
        };
        GLib::Render(*sprite_render_component->m_Sprite, offset, 0.f, 0.f);
    }
    GLib::Sprites::EndRendering();
    GLib::EndRendering();
}
