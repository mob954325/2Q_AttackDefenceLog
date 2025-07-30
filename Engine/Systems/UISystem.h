#pragma once
#include "Utils/Singleton.h"
#include "Components/UI/UIComponent.h"

/// 25.07.29 | 작성자 : 이성호
/// UI 컴포넌트가 상속받을 클래스

class UISystem : public Singleton<UISystem>
{
public:
	friend class Singleton<UISystem>;

	void Register(UIComponent* pUIComponent);
	void UnRegister(UIComponent* pUIComponent);
	void Update();
	void ClearAll();
private:
	UISystem() = default;
	~UISystem();

	std::vector<UIComponent*> components;
};

