#pragma once

#include "GameObject.h"
#include "GameStats.h"
#include "GoBuilder.h"

#include <vector>

namespace Aggrotech
{
    class GameInstance
    {
    public:

        void Initialize();

        void Update(float dt);

    private:

        void UpdateMovement(float dt);
        
        void DetectResolveCollisions(float dt);

        std::vector< GameObject* > objects;

        GoBuilder objectBuilder;

        GameStats gameStats;
    };
}
