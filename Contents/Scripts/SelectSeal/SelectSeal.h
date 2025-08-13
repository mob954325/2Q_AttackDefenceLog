#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

class SelectSeal : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
private:
	BitmapRenderer* left;
	BitmapRenderer* right;
};

