#pragma once

struct Hitbox {
    Hitbox()
    :x(0.0f), y(0.0f), width(0.0f), lenght(0.0f)
    {}

    Hitbox(float m_x, float m_y, float m_width, float m_lenght)
    :x(m_x), y(m_y), width(m_width), lenght(m_lenght)
    {}

    float x;
    float y;
    float width;
    float lenght;

};