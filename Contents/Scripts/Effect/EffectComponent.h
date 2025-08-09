#pragma once
#include "Components/Logic/ScriptComponent.h"
#include "Datas/SpriteDatas.h"
#include "Resources/BitmapResource.h"
#include "Components/Rendering/BitmapRenderer.h"

/*
25.08.06 | 작성자 : 김정현
이펙트용 component
이펙트 3개의 중점을 셋팅해뒀기 때문에 owner의 좌표만 옮기면 위치가 한번에 다 옮겨짐
사용자가 addcomponent에 등록한후
if (eventvalue && counttime < maxtime)
	{
		counttime += mydeltatime;
		TestEffect->Setcircleoutervalue(50 + counttime, 1- counttime);
		TestEffect->Setcircleinnervalue(50 + counttime , 1- counttime);
		TestEffect->Setlinehorizonvalue(0, 0);
	}
	else if (eventvalue && counttime >= maxtime)
	{
		TestEffect->Setcircleoutervalue(0.0f, 0.0f);
		TestEffect->Setcircleinnervalue(0.0f , 0.0f);
		TestEffect->Setlinehorizonvalue(0.0f, 0.0f);
		eventvalue = false;
	}
위와같이 Setcircleoutervalue 등 3개의 함수를 update문에서 원하는 변화 수치를 주고 트리거를 발생하면 이펙트 원하는 수치로 조절 및 발생
scale의 크기를 destrect로 조절 ( owner의 transform의 scale조절하는게 아님 )
*/

class EffectComponent : public ScriptComponent
{
public :
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void Update() override;

	void Setcircleoutervalue(float scalevalue , float capacityvalue);
	void Setcircleinnervalue(float scalevalue, float capacityvalue);
	void Setlinehorizonvalue(float width, float height);


private:
	//그림 3개
	BitmapRenderer* circleouter{};
	BitmapRenderer* circleinner{};
	BitmapRenderer* linehorizon{};

	//각 그림의 destrect , srcrect
	D2D1_RECT_F circleouterDestRect{};
	D2D1_RECT_F circleouterSrcRect{};

	D2D1_RECT_F circleinnerSrcRect{};
	D2D1_RECT_F circleinnerDestRect{};

	D2D1_RECT_F linehorizonSrcRect{};
	D2D1_RECT_F linehorizonDestRect{};

	//bitmap의 원본 사이즈
	D2D1_SIZE_F circleoutersize;
	D2D1_SIZE_F circleinnersize;
	D2D1_SIZE_F linehorizonsize;


};