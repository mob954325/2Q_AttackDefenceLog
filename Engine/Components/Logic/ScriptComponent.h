#pragma once
#include "Components/Base/Component.h"

class ScriptComponent : public Component
{
public:
	virtual void Update() = 0;
};