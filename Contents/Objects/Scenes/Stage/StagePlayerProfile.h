#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"


class StagePlayerProfile : public MonoBehavior
{
public:
	void OnCreate() override;

private:
	BitmapRenderer* playerProfile{};
};