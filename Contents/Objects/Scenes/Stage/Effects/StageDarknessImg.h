#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

class StageDarknessImg : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;

private:
	BitmapRenderer* darkness{};
};

