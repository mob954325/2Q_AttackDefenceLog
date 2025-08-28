#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

/* 8.28. 한승규 
* 튜토리얼에서 제공하는 모든 기능을 짜집기할 그런 매니저임
* 튜토리얼 자체는, 기본적으로 슬라이드 쇼 + 연출로 진행되
*/


class TutorialManager : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;
	D2D1_SIZE_F GetSize() { return size; };

protected:
	D2D1_SIZE_F size;
	BitmapRenderer* bitmapRenderer{};	
};

