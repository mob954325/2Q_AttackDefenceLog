#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/UI/Slider.h"

class HpGauge : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void ChangeGaugeBar();

	void SetHpUiPosition(Vector2 player , Vector2 Enemy);

	void SetPlayerMaxGague(float MaxGague);
	void SetEnemyMaxGague(float MaxGague);

	void CalculatePlayerValue(float endvalue);
	void CalculateEnemyValue(float endvalue);

private:
	GameObject* PlayerHP{};
	GameObject* EnemyHP{};

	Slider* Playerslider{};
	Slider* Enemyslider{};

	float x_width = 0.0f;
	float y_height = 0.0f;

	float x_pic = 0.0f;

	float maxgague = 0.0f;
	float ImageMaxwidth = 0.0f;
	float movegague = 0.0f;
	//게이지 속도
	float speed = 5.0f;

	//게이지와 이미지의 max수치를 맞추기 위한 변수
	float PlayergaugeToPixel = 0.0f;
	float EnemygaugeToPixel = 0.0f;

	//변화율
	float PlayerValue = 0.0f;
	float EnemyValue = 0.0f;
};