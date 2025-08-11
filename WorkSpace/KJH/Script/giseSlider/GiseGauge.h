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

private:
	GameObject* ButtonAnime{};
	GameObject* ButtonCover{};
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

	//덮개 크기
	float coverX = 0.0f;
};

