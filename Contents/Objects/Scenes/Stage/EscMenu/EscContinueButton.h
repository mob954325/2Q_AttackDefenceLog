#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/UI/Button.h"

/* 25.08.09 | 작성자: 이성호
* esc메뉴 계속 버튼 오브젝트에 붙일 monobehavior
	
	Panel 스크립트에서 이벤트 따로 받음
*
*/

class EscContinueButton : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;

private:
	Button* continueButton{};
};

