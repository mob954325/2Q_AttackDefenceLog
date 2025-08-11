#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Objects/Manager/PatternManager.h"
#include "Scene/SceneManager.h"
#include "Utils/EventDelegate.h"

#include "Scripts/Effect/EffectInstance.h" // 이펙트 정현씨꺼


class PatternControlObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	PatternManager PM;

protected:
	ListenerID lid_OnPatternCancel = 0;

	std::array<GameObject*, 9> m_nodes;

	GameObject* trail;
	GameObject* playerGuidelineA;
	GameObject* playerGuidelineB;

	std::queue<GameObject*> readyQueueForEnemyGuide;
	std::vector<GameObject*> enemyGuidelines;

	std::queue<GameObject*> readyQueueForAttackLine;
	std::vector<GameObject*> attackLineEffects;

	GameObject* attackPattenManager;
	GameObject* enemy;
	GameObject* AddGameObject;
	GameObject* bettleManager;
	GameObject* player;

	EffectInstance* effInstance;
	std::vector<EffectInstance*> effs;

private:
	std::vector<int> cachedVecA;

	std::vector<int> cachedVecB;

	std::vector<Vector2> nodePositions;

};


