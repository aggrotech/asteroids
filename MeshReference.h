#pragma once

#include "Vector2.h"

#include <vector>

namespace Aggrotech
{
    class MeshReference
    {
    public:

        int Id;

        std::vector< Vector2 > vertices;
    };
}
