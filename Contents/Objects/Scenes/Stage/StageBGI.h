#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "../Engine/Components/Rendering/VignetteEffect.h"

class StageBGI : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;
	D2D1_SIZE_F GetSize() { return size; };

	void Start(); // 0 -> 1
	void End(); // 1 -> 0
	
protected:
	float progress = 0.0f;
	bool isPlay = false;
	bool isGoingFillUp = true;

	D2D1_SIZE_F size;
	BitmapRenderer* bitmapRenderer{};	
	VignetteEffect* vignette;

	inline float clampf(float v, float minVal, float maxVal) { // 나만의 작은 클램프 함수 C++14를 고집하는 자의 의지
		return (v < minVal) ? minVal : (v > maxVal ? maxVal : v);
	}
};

