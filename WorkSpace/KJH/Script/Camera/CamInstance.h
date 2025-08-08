#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Camera/Camera.h"
#include "Utils/GameTime.h"

/*
25.08.08 | 작성자 : 김정현
사용자가 바로 추가해서 사용할수 있는 카메라 흔들림 기능
사용자는 Component로 등록하고 SetWaveValue로 한번에 값을 변경 가능
처음 등록한 후, SetSlowToFast,SetFastToSlow, SetSlowFastSlow이 3개 중 하나로 셋팅
그리고 호출할때 CallCamShake(type)으로 호출하면됨, 이때 type은 흔들릴 축 ( 아래에 있는 타입으로 출력)
*/

enum class ShakeType
{
	None,
	X,
	Y,
	XY,
	X_Y
};

class CamInstance : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	//수치 설정및 type 설정
	void SetWaveValue(float MaxTime, float Period, float Amplitude, float MaxX , float MaxY);
	void CallCamShake(ShakeType type);
	

	void SetReset();

	//카메라 흔들리는 종류 셋팅 함수 3개
	void SetSlowToFast();
	void SetFastToSlow();
	void SetSlowFastSlow();



private:
	Camera* Came{};

	float counttime = 0.0f;

	float maxtimer = 0.5f;

	ShakeType shakeType = ShakeType::None;

	ShakeCalcu shakecalcutype = ShakeCalcu::None;

};

