#include "Systems/CollisionSystem.h"
#include "Components/Base/GameObject.h"
#include "set"
#include <algorithm>

void CollisionSystem::Register(CollisionComponent* comp)
{
	components.push_back(comp);
}

void CollisionSystem::UnRegister(CollisionComponent* comp)
{
	auto it = components.begin();

	for (; it != components.end(); it++)
	{
		if (*it == comp)
		{
			components.erase(it);
			break;
		}
	}
}

void CollisionSystem::ClearAll()
{
	components.clear();
}

void CollisionSystem::FixedUpdate(std::vector<CollisionInfo>& outInfos)
{
	for (CollisionComponent* comp : components)
	{
		if (!comp->IsStarted()) continue;

		comp->FixedUpdate(components, outInfos);
	}

	EventUpdate(outInfos);
}

void CollisionSystem::CheckPrevPairRemoval()
{
	for (auto it = prevPairs.begin(); it != prevPairs.end();)
	{
		if (it->pair.first->owner->IsMarkedForRemoval() || it->pair.second->owner->IsMarkedForRemoval())
		{
			it = prevPairs.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void CollisionSystem::EventUpdate(std::vector<CollisionInfo>& infos)
{	
	std::set<CollisionPair> currPairs;

	// 충돌 쌍 정규화 -> 이벤트 중복호출 방지용
	auto MakeKey = [](CollisionComponent* a, CollisionComponent* b) -> Pair
		{
			return (a < b) ? Pair(a, b) : Pair(b, a);
		};

	// 현재 충돌 쌍 저장
	for (auto it = infos.begin(); it != infos.end(); it++)
	{
		currPairs.insert(CollisionPair(MakeKey(it->a, it->b), *it));
	}

	// enter/stay
	for (const auto& collisionPair : currPairs)
	{
		bool wasInPrev = prevPairs.find(collisionPair) != prevPairs.end();
		auto* a = collisionPair.pair.first;
		auto* b = collisionPair.pair.second;

		if (wasInPrev)
		{
			CallEvent(a, b, "Stay");
		}
		else
		{
			if (collisionPair.info.penetrationDepth > 0.1f)
			{
				CallEvent(a, b, "Enter");
			}
		}
	}

	// exit
	for (const auto& prev : prevPairs)
	{
		auto it = currPairs.find(prev);
		if (it == currPairs.end())
		{
			if (prev.info.penetrationDepth > 0.1f)
			{
				CallEvent(prev.pair.first, prev.pair.second, "Exit");
			}
		}
	}

	// prevPairs 갱신
	prevPairs = std::move(currPairs);
}

void CollisionSystem::CallEvent(CollisionComponent* a, CollisionComponent* b, const std::string& type)
{
	bool aTrigger = a && a->IsTrigger();
	bool bTrigger = b && b->IsTrigger();

	auto DoCall = [&](GameObject* caller, GameObject* target, bool trigger)
		{
			int size = caller->monoBehaviors.size();
			if (trigger)
			{
				if (type == "Enter") // NOTE: 현재 monobehaivior중 하나만 호출됨, 모두 호출되게 수정하기
				{
					std::for_each(caller->monoBehaviors.begin(), caller->monoBehaviors.end(),[&]
					(MonoBehavior* mono)
						{ 
							mono->OnTriggerEnter(target);
						});
				}
				else if (type == "Stay")
				{
					std::for_each(caller->monoBehaviors.begin(), caller->monoBehaviors.end(), [&]
					(MonoBehavior* mono)
						{
							mono->OnTriggerStay(target);
						});
				}
				else if (type == "Exit")
				{
					std::for_each(caller->monoBehaviors.begin(), caller->monoBehaviors.end(), [&]
					(MonoBehavior* mono)
						{
							mono->OnTriggerExit(target);
						});
				}
			}
			else
			{
				if (type == "Enter")
				{
					std::for_each(caller->monoBehaviors.begin(), caller->monoBehaviors.end(), [&]
					(MonoBehavior* mono)
						{
							mono->OnColliderEnter(target);
						});
				}
				else if (type == "Stay")
				{
					std::for_each(caller->monoBehaviors.begin(), caller->monoBehaviors.end(), [&]
					(MonoBehavior* mono)
						{
							mono->OnColliderStay(target);
						});
				}
				else if (type == "Exit")
				{
					std::for_each(caller->monoBehaviors.begin(), caller->monoBehaviors.end(), [&]
					(MonoBehavior* mono)
						{
							mono->OnColliderExit(target);
						});
				}
			}
		};

	DoCall(a->owner, b->owner, aTrigger);
	DoCall(b->owner, a->owner, bTrigger);
}

CollisionSystem::~CollisionSystem()
{
	if (!components.empty())
	{
		components.clear();
	}
}
