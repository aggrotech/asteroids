#pragma once

#include "MeshReference.h"
#include "KinematicsReference.h"

#include <vector>

namespace Aggrotech
{
    class ReferenceDataArchive
    {
    public:

        const MeshReference GetMeshRefById(int id);

        const KinematicsReference GetKinematicsRefById(int id);

    private:

        std::vector< MeshReference > meshes;

        std::vector< KinematicsReference > kinematics;
    };
}
