#include "GoBuilder.h"

Aggrotech::GoBuilder::GoBuilder()
    : objectId(0)
{
}

Aggrotech::GameObject Aggrotech::GoBuilder::CreateShip()
{
    GameObject obj;

    obj.Id = GenerateObjectId();

    return obj;
}

int Aggrotech::GoBuilder::GenerateObjectId()
{
    return ++objectId;
}
