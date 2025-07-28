#pragma once
#include "framework.h"
#include "Utils/Singleton.h"
#include "Components/Logic/ScriptComponent.h"

class ScriptSystem : public Singleton<ScriptSystem>
{
public:
	friend class Singleton<ScriptSystem>;

	void Register(ScriptComponent* comp);
	void UnRegister(ScriptComponent* comp);
	void ClearAll();

	void Update();	// 컴포넌트 업데이트 실행함수
private:
	ScriptSystem() = default;
	~ScriptSystem();

	std::vector<ScriptComponent*> components; // 실제로 Update 될 컴포넌트 데이터들
};

