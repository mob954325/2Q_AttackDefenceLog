#pragma once
#include "Components/Base/Component.h"
#include "Math/Vector2.h"

class UIComponent : public Component
{
public:
	virtual void Update() = 0;
	virtual bool IsMouseOver(const Vector2& mousePos) const = 0;
};

