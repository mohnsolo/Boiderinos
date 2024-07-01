#include "GameUtil.h"

// This assumes that srand() has already been called
float randRangef(float min, float max)
{
    if (min >= max)
        return 0.f;

    return min + static_cast<float>(std::rand() / static_cast<float>(RAND_MAX / (max - min)));
}
