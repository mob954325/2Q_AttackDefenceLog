#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Objects/Manager/PatternManager.h"
#include "Scene/SceneManager.h"
#include "Utils/EventDelegate.h"
#include "Objects/Manager/ChargedSlashManager.h"
#include "Objects/Common/SignBoard.h"
#include "Scripts/LiveObject/Enemy.h"
#include "Objects/Common/BattleBoard.h" // 보드 위에서 뚜씨뚜씨 하는거임

#include "Objects/Manager/ThinkingPatternManager.h"
#include "Objects/Common/BlinkNodeObject.h"


#include "../Engine/Components/Rendering/AnimatedChainEffect.h" 
#include "Scripts/Effect/EffectInstance.h" // 이펙트 정현씨꺼

/* 8.28. 한승규
* PatternControlObejct를 그대로 복붙한거긴 한데
* 연결 방식을 변경하고, 조건을 추가함
* 튜토리얼에서 사용하기 위해 개조함
*/


/// <summary>
/// Stage에서 사용하는 적 패링 패턴과, 플레이어 공격 패턴 관리 클래스
/// </summary>
class TutorialControlObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	PatternManager PM;					// 패턴 매니저
	Enemy* GetEnemy();

protected:
	ListenerID lid_OnPatternCancel = 0;

	std::array<GameObject*, 9> m_nodes;	// 노드 오브젝트 9개

	GameObject* trail;					// 마우스 트레일
	//GameObject* playerGuidelineA;		// 플레이어 공격 가이드 A
	//GameObject* playerGuidelineB;		// 플레이어 공격 가이드 B

	std::queue<GameObject*> readyQueueForEnemyGuide;	// 준비 된 적 공격 가이드 -> 패링 이미지
	std::vector<GameObject*> enemyGuidelines;			// 셋업된 공격 가이드 라인

	std::queue<GameObject*> readyQueueForAttackLine;	// 준비된 플레이어 공격 가이드 -> 점선 화살표 이미지 2개
	std::vector<GameObject*> attackLineEffects;			// 공격 라인 이펙트 오브젝트들


	std::queue<AnimatedChainEffect*> enemyAttackChain; // 적 공격을 노드위에 표기하기 위한 뭐시깽임

	GameObject* attackPattenManager;					// 공격 패턴 매니저
	GameObject* bettleManager;							// 배틀 매니저
	GameObject* enemy;									// 적군 오브젝트
	GameObject* player;									// 플레이어

	ChargedSlashManager* chargedSlashManager;			// 차지 공격 매니저

	EffectInstance* effInstance;						// 단일 이펙트 -> 이 오브젝트가 소유하고 있음
	std::vector<EffectInstance*> effectInstances;		// 이펙트 여러개 -> 이 오브젝트와 개별 오브젝트

	SignBoard* signBoard;
	//BattleBoard* battleBoard;	
	std::queue<BattleBoard*> battleBoards;

	BlinkNodeObject* blinkNodeObject;

private:
	bool isSkipped = false; // 이거 켜지면, 노드 관련 행동 스킵함

	//===============================
	// 연격에서, 적의 공격을 다단히트 느낌으로 연출하기 위한 요소
	bool playEnemyChainEffect = false;
	float chainEffectDuration = 0.0f;
	float chainEffectTimer = 0.0f;
	//std::vector<int> chainVec; // 2자리 수 -> 공격, 1자리 수 -> 가드, 전부 가드시 패링으로 변경

	std::deque<int> chainQueue;

	void chainPlayHelper() { // 쓰기 편하라고, 핼퍼함수 만듬		
		chainEffectDuration = 0.5f / static_cast<float>(chainQueue.size());;
		playEnemyChainEffect = true;
		chainEffectTimer = chainEffectDuration; // 한번 바로 재생해야함				
	}

	//===============================

	bool waitOneSecond = false; // 이거 키면, 특정 시간동안 노드를 비활성화하고 다시 켜줌



	float waitTimer = 0.0f;

	std::vector<int> cachedVec;

	std::vector<Vector2> nodePositions;
};


