#pragma once

#include "Vector2.h"

namespace Aggrotech
{
    class MeshReference;

    class RenderableMesh
    {
    public:

        MeshReference *MeshRef;

        Vector2 Position;

        float Rotation;

        float Scale;
    };
}
