#pragma once

#include "Vector2.h"

namespace Aggrotech
{
    enum
    {
        kCollisionGroups_Nothing = -1,
        kCollisionGroups_Everything = 0
    };
    
    enum DeathTypes
    {
        kDeathTypes_Normal,
        kDeathTypes_SpawnTwoChildren
    };

    class GameObject
    {
    public:

        int Id;

        int Health;

        DeathTypes DeathType;


        // Kinematics

        int KinematicsRefId;

        Vector2 Position;

        float Rotation;

        float RotationalSpeed;

        Vector2 Velocity;

        Vector2 Acceleration;


        // Collision

        int CollisionDamage;

        int CollisionGroup;

        
        // Mesh

        int MeshRefId;

        float MeshScale;
    };
}
