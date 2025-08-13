#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

class SelectSeal : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

private:
	BitmapRenderer* left;
	BitmapRenderer* right;

	float timer = 0.0f;
	float maxTimer = 0.8f;
	
	bool isRighDone = false;
};

