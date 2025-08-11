#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"



struct EffectProgress {
	BitmapRenderer* bitmapRenderer;

	float alpha = 0.0f; // << 이것도 progress 1 시점에서 알파 1이 보장되야함
	// 그러나, 각각의 요소가 알파 1로 진입하는 시점이 달라야함
	// 응애

	float startTimingAlpha = 0.0f;
	float targetTimingAlpha = 1.0f; // progress의 진행도와 일치하는 시점이 1인거임

	//그러면?
	//역수를 곱해주는거임
	//시작하는 지점도 골라줄 수 있겠네
	//만약 특정 지점 A에서 시작하고 싶을 수 있겠네?

	// 0.3에서 시작하고 싶다면
	// (progress - 0.3f) * (1.0f / (1.0f - 0.3f))
	// 정리하면	
	// (progress - startAlpha) * (1.0f / (1.0f - startAlpha))
	// (progress - startAlpha) * (1.0f / (targetAlpha - startAlpha)) << 이러면, progress = StartAlpha ~ targetAlpha가 됨

	Vector2 startPos = { 0,0 }; // 초기화 위치
	Vector2 targetPos = { 0,0 }; // progress 1 일때 위치

	float startTimingPos = 0.0f;
	float targetTimingPos = 1.0f;
	//보간식은, startPos + (targetPos - startPos) * progress
	//이런식으로 사용함

	//날 선형보간의 신이라고 불러라
};


class TitleEffectManager : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;
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

