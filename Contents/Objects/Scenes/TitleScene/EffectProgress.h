#pragma once;

#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

//그냥 구조체 이곳저곳에서 쓰고싶어서 만듬
// + 클램프 static으로 지원해줌(편함)
// 사실 러프도 만들어도 되긴 하는데 흠.
//응애

constexpr float EPSILON = 1e-6f; // 이건 유명한 엡실론임
//constexpr float PI = 3.141592654f; // 이건 유명한 파이임

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

	static float clamp01(float t) { // 어차피 0 1 많이 넣으니까, 쓰는거
		return t < 0.0f ? 0.0f : (t > 1.0f ? 1.0f : t);
	}

	// 기본 progress를 기준으로 정규화 해주는 함수임
	// 전체 흐름인 0.0 ~ 1.0 중, 0.3 ~ 0.5 구간을 0.0 ~ 1.0 으로 치환해서 반환해주는 기능임
	// 즉, 0.0 0.0 0.2 0.5 0.5 1.0 1.0 1.0 1.0... 이런느낌
	// 그 유명한 부분과 전체라는거임(아님)
	static float NormalizeProgress(float base, float start, float end) {	
		float fromDenom = end - start;

		if (fabsf(fromDenom) < EPSILON)  // float 절대값으로 바꿔서, 엡실론과 비교
			return	 1.0f; // 이동시간이 0, 즉시 이동 완료임
		else
			return clamp01((base - start) * (1.0f / (fromDenom)));
	}

	// [1] 선형 보간
	static Vector2 Lerp(Vector2 start, Vector2 end, float progress) {
		progress = clamp01(progress);
		return  start + (end - start) * progress;
		//(1-t)*A + t*B = A - A*t + B*t = A + (B - A) * t
	}

	// [2] 베지에 커브, 사실산 선형보간을 두번한거랑 같은 개념임
	static Vector2 BezierQuadratic(Vector2 start, Vector2 end, Vector2 control, float progress) {
		progress = clamp01(progress);

		float u = 1.0f - progress; // 1 - t
		float uu = u * u;

		float tt = progress * progress;

		return  (uu * start) + (2.0f * u * progress * control) + (tt * end);

		// A = 시작, B = 끝, C = 제어점
		// (1-t)*((1-t)*A + C*t) + t*((1-t)C + B*t)
		//  = (A - 2C + B)*t*t + (2C - 2A)*t + A
		// 코드로 쓰기 쉽게, t와 u = (1 - t)에 대해 정리하면
		//  = u*u*A + 2C*u*t + t*t*B, 치환은 신이야
	}

	// [3] 선형 보간 3번, 어지럽군
	static Vector2 BezierCubic(Vector2 start, Vector2 end, Vector2 controlA, Vector2 controlB, float progress) {
		progress = clamp01(progress);

		float u = 1.0f - progress; // 1 - t

		float uu = u * u;
		float uuu = uu * u;

		float tt = progress * progress;
		float ttt = tt * progress;

		return (start * uuu) + (3.0f * controlA * progress * uu) + (3.0f * controlB * u * tt) + (end * ttt);

		// 여기서부턴 전계하는거 귀찮아서, 치환으로 처리함
		// u = 1-t, t에 대해 정리하면
		// A = 시작, B = 제어점1, C  = 제어점2, D = 끝
		// A - B, B - C, C - D 에 대해 3개 선형보간하고
		// 그 결과를 각각 보간하고 보간하면 나옴
		// 1. u*u*A + 2*B*t*u + C*t*t
		// 2. u*u*B + 2*C*t*u + D*t*t
		// 1 과 2 를 보간하면
		// A*u*u*u + 3B*t*u*u + 3C*u*t*t + D*t*t*t, 치환은 신이고 난 무적이다
	}

	// [4] 감쇠 사인
	// 선형 보간의 이동 방향와, 수직으로 파동 변주를 주는거임
	// 그 변주를 감쇠하는 형태로 주는게 포인트

	// 그리운 기본 사인파 수식
	// A*sin(2*PI*f*t + p)
	// A -> 진폭, 배율임, 전체 값에다가 곱해버림
	// f -> 진동수, 사인은 -1과 1을 왕복하는데, 그 안에 값이 빠르게 변한다는건, 진동이 빨라진다는거임
	// p -> 위상, 처음 시작지점, 보정값 같은거임, 사인은 값을 더하면 언젠가 다시 돌아와서 가능함
	// 사인에서 2PI 간격으로 1번 진동함, 여기서 f가 곱해져있어서, 그대로 값이 뛰어버림
	// f = 3 이라면, 기존 한주기(2PI)에 한번만 진동할껄, 3번 진동함
	// f = 0.5 라면?, 기존 한주기(2PI)에 0.5번만 진동함, 즉 한번 진동이 4PI가 걸리게 됨

	// 감쇠를 주는 방식은 해당 사인파에서 진폭에다가
	// 특정 값을 곱해서 낮춰주면 됨
	// e^-t 에서, t가 무한대로 수렴할때,
	// e = 0으로 수렴함, 즉 값이 커질수록 0이 되는 공식이 나옴
	// cmath 안에 std::exp(A) 넣어버리면, e^A가 계산됨(개꿀)
	// 수식으로 정리하면
	// A*exp(-a*t)*sin(2*PI*f*t + p), exp(t) = e^t
	// A는 처음 진동폭, a는 감쇠폭, 크면 클 수 록 더 크게 감소함 

	// 위 공식들을 이용해서, 기존 선형보간으로 A B 를 통과할때,
	// 그 경로와 수직인 방향에 사인감쇠를 곱해주면
	// 자연스럽게 위아래로 요동치는 형태가 됨

	// 주의할점은, e^-t는 0으로 수렴하지만, 0으로 만들 수는 없음(되긴 하겠지)

	static Vector2 DampedSine(Vector2 start, Vector2 end, float amplitude, float frequency, float damping, float phase, float progress) {
		progress = clamp01(progress);

		// 선형 보간
		Vector2 base = Lerp(start, end, progress); // 일단 이거 따라서 움직이는데

		float dist = (end - start).SqrMagnitude(); // 거리, 스칼라

		Vector2 perp; // perpendicular = 수직 이라는 뜻

		if (dist < EPSILON * EPSILON) { // 시작과 끝이 같아서, 한 점일경우			
			perp = { 0.0f, 1.0f }; // 대충 Y충 방향벡터로 박아넣음, 점인데 어쩔껀데 수직이 어딧슴 콱씨
		}
		else { // 제대로된 방향이 있다면			
			perp = (end - start).Normalize();
			perp = { -perp.y, perp.x, }; // x y 바꾸고, - 한쪽에 붙여주면 수직임
		}

		// 감쇠 사인
		constexpr float TAU = 6.283185308f; // 6.283185308 = 2PI

		float e = std::exp(-damping * progress); // exp(-a*t)
		float A = TAU * frequency * progress + phase; // 만두 속 만드는거임, phase는 라디안임
		float sinA = std::sin(A); // 만두 속 집어넣음
		float offset = amplitude * e * sinA; // A(진폭) * e(지수감수) * 사인

		return  base + perp * offset;
		//base = 진행(선형)
		//perp = 수직 방향 벡터
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