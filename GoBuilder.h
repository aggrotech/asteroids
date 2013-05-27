#pragma once

#include "GameObject.h"

namespace Aggrotech
{
    class GoBuilder
    {
    public:
        GoBuilder();

        GameObject CreateShip();

    private:

        int GenerateObjectId();

        int objectId;
    };
}
