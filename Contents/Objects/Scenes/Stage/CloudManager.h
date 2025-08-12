#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Objects/Scenes/TitleScene/EffectProgress.h" // 여기에 구조체 있음

class CloudManager : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override {}
	D2D1_SIZE_F GetSize() { return size; };
	
	void Start();
	void Reset();//원래 자리로 돌리는 기능임 << Start내부에서 호출되긴 함
protected:
	D2D1_SIZE_F size;
	BitmapRenderer* bitmapRenderer;

	std::vector<EffectProgress> effectProgress;

	bool isPlay = false;

	float progress = 0.0f; // 0~1 정규화 값, 이거 기반으로 애니메이션 + 연출 돌아감
private:

	inline float clampf(float v, float minVal, float maxVal) { // 나만의 작은 클램프 함수 C++14를 고집하는 자의 의지
		return (v < minVal) ? minVal : (v > maxVal ? maxVal : v);
	}
};

