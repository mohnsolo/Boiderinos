#include "GameUtil.h"

sf::Vector2f getNormal(sf::Vector2f vec)
{
    if (vec.x != 0.f && vec.y != 0.f)
    {
        float mag = std::sqrt(vec.x * vec.x + vec.y * vec.y);
        vec = vec / mag;
    }
    return vec;
}

void normalize(sf::Vector2f& vec)
{
    if (vec.x != 0.f && vec.y != 0.f)
    {
        float mag = std::sqrt(vec.x * vec.x + vec.y * vec.y);
        vec = vec / mag;
    }
}

int resolve2d(unsigned int index, unsigned int width, sf::Vector2u& vect)
{
    if (width == 0)
    {
        return 1;
    }
    else
    {
        vect.x = index % width;
        vect.y = index / width;
    }
    return 0;
}

// This assumes that srand() has already been called
float randRangef(float min, float max)
{
    if (min >= max)
        return 0.f;

    return min + static_cast<float>(std::rand() / static_cast<float>(RAND_MAX / (max - min)));
}
