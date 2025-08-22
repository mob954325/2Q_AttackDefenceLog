#pragma once;

#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

//그냥 구조체 이곳저곳에서 쓰고싶어서 만듬
// + 클램프 static으로 지원해줌(편함)
// 사실 러프도 만들어도 되긴 하는데 흠.
//응애

struct EffectProgress {
	BitmapRenderer* bitmapRenderer = nullptr;

	float alpha = 0.0f;
	float startTimingAlpha = 0.0f;
	float targetTimingAlpha = 1.0f;

	Vector2 startPos = { 0.0f, 0.0f };
	Vector2 targetPos = { 0.0f, 0.0f };

	float startTimingPos = 0.0f;
	float targetTimingPos = 1.0f;

	static float clampf(float v, float minVal, float maxVal) { // 나만의 작은 클램프 함수 C++14를 고집하는 자의 의지
		return (v < minVal) ? minVal : (v > maxVal ? maxVal : v);
	}
};

/*

struct EffectProgress {
	BitmapRenderer* bitmapRenderer = nullptr;

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

	static float clampf(float v, float minVal, float maxVal) { // 나만의 작은 클램프 함수 C++14를 고집하는 자의 의지
		return (v < minVal) ? minVal : (v > maxVal ? maxVal : v);
	}
};*/