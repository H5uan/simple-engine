#pragma once

#include <GLib.h>

struct SpriteRenderable : RXECS::Component<SpriteRenderable>
{
    GLib::Sprite* m_Sprite;

    explicit SpriteRenderable(GLib::Sprite* sprite): m_Sprite(sprite)
    {
    }

    ~SpriteRenderable()
    {
    };
};
