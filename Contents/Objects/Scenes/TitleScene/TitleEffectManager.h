#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"


class TitleEffectManager : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;
	D2D1_SIZE_F GetSize() { return size; };

	void Start();

protected:
	D2D1_SIZE_F size;
	BitmapRenderer* bitmapRenderer;

	std::vector<BitmapRenderer*> bitmaps;
	float alpha = 0.0f;
	bool isPlay = false;

};

