#pragma once
#include "Components/UI/UIComponent.h"
#include "Components/Rendering/BitmapRenderer.h"
#include <Utils/EventDelegate.h>
#include <string>
#include <functional>

/* 25.07.29 | 작성자 : 김정현

*/


class Slider : public UIComponent
{
public:
	void OnStart() override;
	void Update() override;
	
	//void SetGaugeBarRect(float width);

	void SetPivotSide( bool isLeft);

	void SetGaugeBackgroundImage(std::wstring path);
	BitmapRenderer* GetGaugeBackgroundImage();
	void SetGaugeBarImage(std::wstring path);
	BitmapRenderer* GetGaugeBarImage();


private:
	BitmapRenderer* GaugeBackground{};
	BitmapRenderer* GaugeBar{};


	D2D1_RECT_F GaugeBarRect{};

	bool pivotIsLeft = true;

};


