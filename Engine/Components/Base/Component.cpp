#include "Component.h"

bool Component::IsCreated()
{
    return isCreated;
}

void Component::SetCreated()
{
    isCreated = true;
}

bool Component::IsStarted()
{
    return isStarted;
}

void Component::SetStarted()
{
    isStarted = true;
}
