#pragma once
#include <functional>
#include <unordered_map>

/*

25.07.31 | 작성자 : 김정현
사용법은 EasingList[InBounce](5.0f);
key값은 enum 리스트인 EasingEffect에서 골라서 사용
https://easings.net/ 그래프 참고 사이트
Lnear는 일차함수

*/


enum EasingEffect
{
	// Linear
	Linear,

	// Sine
	InSine,
	OutSine,
	InOutSine,

	// Quad
	InQuad,
	OutQuad,
	InOutQuad,

	// Cubic
	InCubic,
	OutCubic,
	InOutCubic,

	// Quart
	InQuart,
	OutQuart,
	InOutQuart,

	// Quint
	InQuint,
	OutQuint,
	InOutQuint,

	// Expo
	InExpo,
	OutExpo,
	InOutExpo,

	// InCirc
	InCirc,
	OutCirc,
	InOutCirc,

	// Back
	InBack,
	OutBack,
	InOutBack,

	// Elastic
	InElastic,
	OutElastic,
	InOutElastic,

	// Bounce
	InBounce,
	OutBounce,
	InOutBounce,

	EasingEffectEnd
};

#pragma region _EasingFunction

// Linear
float easeLinear(float x);

// Sine
float easeInSine(float x);
float easeOutSine(float x);
float easeInOutSine(float x);

// Quad
float easeInQuad(float x);
float easeOutQuad(float x);
float easeInOutQuad(float x);

// Cubic
float easeInCubic(float x);
float easeOutCubic(float x);
float easeInOutCubic(float x);

// Quart
float easeInQuart(float x);
float easeOutQuart(float x);
float easeInOutQuart(float x);

// Quint
float easeInQuint(float x);
float easeOutQuint(float x);
float easeInOutQuint(float x);

// Expo
float easeInExpo(float x);
float easeOutExpo(float x);
float easeInOutExpo(float x);

// InCirc
float easeInCirc(float x);
float easeOutCirc(float x);
float easeInOutCirc(float x);

// Back
float easeInBack(float x);
float easeOutBack(float x);
float easeInOutBack(float x);

// Elastic
float easeInElastic(float x);
float easeOutElastic(float x);
float easeInOutElastic(float x);

// Bounce
float easeInBounce(float x);
float easeOutBounce(float x);
float easeInOutBounce(float x);


#pragma endregion

//static map으로 묶음
static std::unordered_map<EasingEffect, std::function<float(float)>> EasingList
{
	{Linear, easeLinear},
	{InSine, easeInSine},
	{OutSine, easeOutSine},
	{InOutSine, easeInOutSine},

	// Quad
	{InQuad,  easeInQuad },
	{OutQuad, easeOutQuad},
	{InOutQuad, easeInOutQuad},

	// Cubic
	{InCubic, easeInCubic},
	{OutCubic, easeOutCubic},
	{InOutCubic, easeInOutCubic},

	// Quart
	{InQuart, easeInQuart},
	{OutQuart, easeOutQuart},
	{InOutQuart, easeInOutQuart},

	// Quint
	{InQuint, easeInQuint},
	{OutQuint, easeOutQuint},
	{InOutQuint, easeInOutQuint},

	// Expo
	{InExpo, easeInExpo},
	{OutExpo, easeOutExpo},
	{InOutExpo, easeInOutExpo},

	// InCirc
	{InCirc, easeInCirc},
	{OutCirc, easeOutCirc},
	{InOutCirc, easeInOutCirc},

	// Back
	{InBack, easeInBack},
	{OutBack, easeOutBack},
	{InOutBack, easeInOutBack},

	// Elastic
	{InElastic, easeInElastic},
	{OutElastic, easeOutElastic},
	{InOutElastic, easeInOutElastic},

	// Bounce
	{InBounce, easeInBounce},
	{OutBounce, easeOutBounce},
	{InOutBounce, easeInOutBounce},
};
