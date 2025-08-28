#pragma once
#include "Components/Base/MonoBehavior.h"


/* 8.28. 한승규 
* 기존에는 CSV + 기타 내부 로직으로 노드를 반환해줬지만,
* 튜토리얼에 한정해 단순화 시킨거임
* 딸깍하면 백터가 나옴 << 이 벡터로 노드 번쩍이고 기타 연결 다 하면 됨
*/


class TutorialPatternManager : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	std::vector<int>GetEnemyBlowVec(); // 적의 연격을 반환해줌
	std::vector<int>GetPlayerAttackVec(); // 플레이어의 공격 가이드를 반환해줌
	std::vector<int>GetEnemyAttackVec(); // 적의 공격 가이드를 반환해줌

protected:

};

