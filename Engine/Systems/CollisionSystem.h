#pragma once
#include "Utils/Singleton.h"
#include "Components/Collision/CollisionComponent.h"
#include "Components/Physics/PhysicComponent.h"
#include "Datas/CollisionInfo.h"
#include "unordered_map"
#include "set"

using Pair = std::pair<CollisionComponent*, CollisionComponent*>;

struct CollisionPair
{
	Pair pair;
	CollisionInfo info;

	CollisionPair(Pair pair, CollisionInfo info) : pair(pair), info(info) {}

	bool operator<(const CollisionPair& other) const 
	{
		return pair < other.pair; // std::set 사용 위해 필요
	}
};

class CollisionSystem : public Singleton<CollisionSystem>
{
public:
	friend class Singleton<CollisionSystem>;

	void Register(CollisionComponent* comp);
	void UnRegister(CollisionComponent* comp);
	void ClearAll();

	void FixedUpdate(std::vector<CollisionInfo>& outInfos);
	void CheckPrevPairRemoval();
private:
	CollisionSystem() = default;
	~CollisionSystem();

	void EventUpdate(std::vector<CollisionInfo>& infos);
	void CallEvent(CollisionComponent* a, CollisionComponent* b, const std::string& type);

	std::set<CollisionPair> prevPairs;
	std::vector<CollisionComponent*> components;
};

