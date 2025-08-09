#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/UI/Button.h"

/* 25.08.09 | 작성자: 이성호
* esc메뉴 음소거 버튼 오브젝트에 붙일 monobehavior
*/

class EscMuteButton : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;

private:
	Button* muteButton{};
};
