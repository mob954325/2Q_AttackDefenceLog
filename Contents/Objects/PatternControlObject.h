#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "../Objects/Manager/PatternManager.h"
#include "../Engine/Scene/SceneManager.h"

class PatternControlObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	PatternManager PM;

protected:
	std::array<GameObject*, 9> m_nodes;
	GameObject* trail;	
	GameObject* playerGuidelineA;
	GameObject* playerGuidelineB;

	std::queue<GameObject*> readyQueue;
	std::vector<GameObject*> enemyGuidelines;

	GameObject* attackPattenManager;
	GameObject* enemy;
	GameObject* AddGameObject;
	GameObject* bettleManager;
	GameObject* player;
};

