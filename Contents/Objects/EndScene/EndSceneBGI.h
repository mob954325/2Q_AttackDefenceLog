#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"


class EndSceneBGI : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;
	D2D1_SIZE_F GetSize() { return size; };

protected:
	D2D1_SIZE_F size;
	BitmapRenderer* bitmapRenderer{};	
};

