#pragma once
#include "Components/Base/MonoBehavior.h"
#include "../Engine/Components/Base/GameObject.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "../Engine/Components/UI/Button.h"

/*8.29. 한승규
* 튜토리얼 진입 질문 + 버튼
* 처음 메뉴씬에 오게되면 뜸.
*/

class TutorialEnterObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

	void Show();
	void Hide();

protected:
	BitmapRenderer* panel;

	Button* yesBtn;
	Button* noBtn;

};