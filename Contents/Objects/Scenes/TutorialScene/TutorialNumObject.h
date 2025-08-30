#pragma once
#include "Components/Base/MonoBehavior.h"
#include "../Engine/Components/Base/GameObject.h"
#include "Components/Rendering/BitmapRenderer.h"


/*8.31. 한승규
* 숫자 표시해주는 오브젝트
* 0 ~ 3 / 3 이런식으로
* 숫자 표기해줌
*/

class TutorialNumObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

	void Show();
	void Hide();

protected:
	BitmapRenderer* panel;
};