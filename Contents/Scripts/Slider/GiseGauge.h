#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/UI/Slider.h"

class GiseGauge : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void SetAnimePosition();

	void ChangeGaugeBar();

	void SetMaxGague(float MaxGague);

	void CalculateValue(float endvalue);


	inline void BlinkBlack() { blackAlpha = 1.0f; }  // 외부에서 호출해주면 깜빡스
	inline void BlinkWhite() { whiteAlpha = 1.0f; }

private:
	GameObject* ButtonAnime{};
	Slider* sliderobj{};

	float x_width = 0.0f;
	float y_height = 0.0f;

	float x_pic = 0.0f;

	float maxgague = 0.0f;
	float currentgague = 0.0f;
	float movegague = 0.0f;
	//게이지 속도
	float speed = 5.0f;

	//게이지와 이미지의 max수치를 맞추기 위한 변수
	float gaugeToPixel = 0.0f;

	//변화율
	float X_Value = 0.0f;

	//
	float coverX = 0.0f;
	GameObject* ButtonCover{};

	BitmapRenderer* whiteEffect; //기세 게이지바 위에 반짝할려고 만듬
	BitmapRenderer* blackEffect;
	float blackAlpha = 0.0f; // 응애
	float whiteAlpha = 0.0f; // 알파값임
};

