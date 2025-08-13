#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Components/Rendering/AnimationRenderer.h"

class EndBackground : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;


protected:
	BitmapRenderer* bitmapRenderer{};
};

