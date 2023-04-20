#pragma once

struct Vector2
{
    float x, y;

    Vector2() : x(0), y(0) {}
    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+ (const Vector2& value) const
    {
        return Vector2(x + value.x, y + value.y);
    }
    Vector2 operator- (const Vector2& value) const
    {
        return Vector2(x - value.x, y - value.y);
    }
    Vector2 operator* (const float& value) const
    {
        return Vector2(x * value, y * value);
    }

    void operator+= (const Vector2& value)
    {
        x += value.x;
        y += value.y;
    }
    void operator-= (const Vector2& value)
    {
        x -= value.x;
        y -= value.y;
    }
    void operator*= (const float& value)
    {
        x *= value;
        y *= value;
    }

    float Length() const
    {
        return sqrt(x * x + y * y);
    }

    Vector2 Normalize() const
    {
        return Vector2(x / Length(), y / Length());
    }

    float Cross(const Vector2& value) const
    {
        return x * value.y - y * value.x;
    }
};