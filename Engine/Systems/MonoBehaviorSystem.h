#pragma once
#include "Utils/Singleton.h"
#include "Components/Base/MonoBehavior.h"

class MonoBehaviorSystem : public Singleton<MonoBehaviorSystem>
{
public:
	friend class Singleton<MonoBehaviorSystem>;

	void Register(MonoBehavior* comp);
	void UnRegister(MonoBehavior* comp);
	void ClearAll();

	// MonoBehaiovr 이벤트 호출 함수들
	void Update();
	void FixedUpdate();

	void ProcessPendingComponents();
private:
	MonoBehaviorSystem() = default;
	~MonoBehaviorSystem();

	std::vector<MonoBehavior*> components;
	std::vector<MonoBehavior*> pendingComponents;
};

