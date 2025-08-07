#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Datas/SoundDatas.h"
#include "Components/Rendering/BitmapRenderer.h"

class EffectObject : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void SetEffectValue(float width, float height , float capacityvalue, bool checkend);

	void SetOwnerPosition(float x, float y);

	void SetImage(std::wstring path);

private:
	BitmapRenderer* Effect{};

	D2D1_RECT_F EffectDestRect{};
	D2D1_RECT_F EffectSrcRect{};

	D2D1_SIZE_F Effectsize;

};


