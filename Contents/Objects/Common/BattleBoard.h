#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Objects/Scenes/TitleScene/EffectProgress.h" // calmpf
//#include "Components/Rendering/ParticleRenderer.h"
#include "../Contents/Scripts/Effect/EffectInstance2.h"

/* 8.22. 한승규
* 플레이어와 적의 상호작용을 시각화 해서 보여주는 기능
* 플레이어의 공격과, 적의 대응 + 적의 공격과 플레이어의 대응을
* 마치 작은 인형극처럼, 노드 패널 위에서 표시해주는 기능임
* 파티클 + 트랜스폼 + 알파값 + 선형보간 등으로 연출해줄 생각
*
* 사운드 자체는 없어도 될듯, 이미 이펙트(피격 - 공격)에 할당된 사운드가 있어서
* 겹쳐 들릴꺼임
*/

class BattleBoard : public MonoBehavior
{
public:
	enum SignType { // Vector 인덱스랑 동일하게 사용함
		HighAttackSign = 0,
		MiddleAttackSign = 1,
		LowAttackSign = 2,
		GuardSign = 3,
		ParrySign = 4,
		HitSign = 5,
		EvasionSign = 6,
		EnemyAttackSign = 7
	};

	// 연출에 대한 값, switch 돌릴꺼임
	enum CurveType {
		HitCurve = 0,
		GuardCurve = 1,
		EvasionCurve = 2,
		ParryCurve = 3
	};

	void OnStart() override;
	void OnCreate() override;
	void OnUpdate() override;

	//공용
	void Hit(SignType attackType); // 맞는쪽은 피격 고정
	void Guard(SignType attackType); // 맞는쪽은 방어 고정		
	void Evasion(); //적 전용, 방향 <- 고정, 회피 고정	
	void Parry(); //플레이어 전용, 방향 -> 고정 + 공격&반격 고정

	void Curve(); //Update 길어져서 빼놓은거임

	void ClearAll();
	//void OnDestroy() override;

protected:
	float progress = 0.0f;

	bool isPlay = false;
	bool wasPlayedOnce = false; 

	std::vector<BitmapRenderer*> battleSignBitmaps;	

	SignType from = EnemyAttackSign;
	SignType to = GuardSign;

	CurveType curve = HitCurve;

	//ParticleRenderer* particle;
	EffectInstance2* eff;

	Vector2 leftPoint;
	Vector2 rightPoint;
	Vector2 halfPoint;
};



