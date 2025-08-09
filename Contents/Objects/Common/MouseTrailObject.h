#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

class MouseTrailObject : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;		

protected:
	D2D1_SIZE_F size;
	BitmapRenderer* bitmapRenderer{};	
};

