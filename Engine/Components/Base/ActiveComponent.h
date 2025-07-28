#pragma once
#include "Components/Base/Component.h"

/// <summary>
/// 활성화, 비활성화 기능이 있는 컴포넌트가 상속받은 클래스 ( 유니티에서의 Behavior를 담당함 )
/// </summary>
class ActiveComponent : public Component
{
private:
	bool enabled = true;

public:
	bool IsActiveSelf() { return enabled; }
	void SetActive(bool value) { enabled = value; }
};