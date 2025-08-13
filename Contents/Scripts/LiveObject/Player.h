#pragma once
#include "LiveObject.h"
#include "../CsvData/DataClass/PlayerData.h"
#include "../Component/StateController.h"
#include "../CsvData/DataClass/AllNodePattenClass.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "../Engine/Utils/EventDelegate.h"
#include "../Engine/Math/GameRandom.h"
#include "Scripts/Effect/EffectMonoB.h"
#include "Scripts/Effect/EnemyAttackEffect.h"
/* 25.08.01
	 플레이어의 데이터 불러오기 -> 일관성 없음?
		- 스탯 : hp 같은 스탯들은 변해야 함으로 저장공간을 만들어 데이터를 인가하는 형태로 진행
		- 패턴 : 패턴은 게임 진행상에 변하지 않음으로 포인터로 가리키게 만들어 사용할 예정
*/






class LiveObject;
class Player : public LiveObject
{
public:
	Player() = default;
	~Player() = default;
	void OnStart() override;
	void OnUpdate() override;

private:
	//플레이어 고정 공격패턴
	std::string attackPlayerPatternIDFix = "";  //안쓰면 PI 붙이기 말기!!,  ex) "PI_040"

	//기세가 0이 되었을때 그 시간이 유지되는 시간
	float totalGroggyTime = 3.0f;

public:
	// 플레이어의 상태를 초기화하는 함수
	void SetStatData(std::string tmp); // 스탯 데이터를 데이터에서 불러와 저장함
	void SetSpiritData(float enemy_SpiritAmount); // 배틀매니저에서 적을 불러와서 생성함!!
	void SetAttackPattenData(std::string PattID); //  패턴ID에 맞는 가이드라인 데이터를 불러옴
	void ResetSpiritAmount();

	// 배틀 매니저에서 사용될 함수
	void SelectPattern() override;   //플레이어가 사용할 패턴을 고름
	void SetNowPattern() override;   //플레이어의 현재 패턴의 노드를 반환함


	//업데이트에 들어갈 시간에 따라 변하는 함수들
	void CalSpiritTime() override;  // 초당 기세 : -0.3
	void SetCoolTime() override;	// 쿨타임이 0이 되었을 때, 플레이어의 쿨타임 설정
	void StateAct();				// 각 state 별로 실행하는 함수
	void DiffState();				// 이전 상태 저장하고 groggy 업데이트 관련 내용 포함

	//스테이트 설정하는 함수
	void SetState(std::string setStateName) override;	// 현재 상태를 설정하는 함수
	void OnCreateState() override;						// 해당 객체에 상태를 정의하는 함수
	void SetEndAttack() { isAttackingPattern = true; }

	void RestoreGroggy();

	//플래그를 체크할 함수
	void AddPattenLoop() override;

	StateController* m_State;  //오브젝트 들은 State 내부에서 받을 수 있도록 포인터 생성
	AttackPatternManager* m_PattenManager = nullptr; // 패턴 매니저를  참조로 받아  사용할 변수
	AllNodePattenClass* tmpNode = nullptr;  // 출력용 변수
	AllNodePattenClass* tmpNode2 = nullptr;  // 출력용 변수


	bool isOtherGroggyEnd = false; // 아군의 연격이  끝났다는 불변수
	bool IsOtherGroggy = false;
	bool restoredThisCycle = false; // 복구 되었는가를 체크하는 플래그
	bool OtherGroggyTimeStop = false; // 연격 타이밍 때, 플레이어의 이미지가 연속해서 출력되도록 시간을 잠시 멈춤
	void AttackAniSelect(int count); // 애니메이션 출력용 함수

	float enemyGroggyTime = 0.0f;		// 그로기 시간?
	EventDelegate<> onTimeOut; // 8.12추가, 그로기 타이머가 플레이어에 있어서 델리게이트 연결함

	//피격모션 호출 함수
	void CallPlayerHit(int num , Vector2 position , float rotate);
	void callPlayerDefence();

private:
	void AttackStateSelect(bool AttackActive); // 공격 패턴 3가지 중 랜덤으로 1개 선택해서 설정함
	void ResetPlayer(); // 플레이어의 상태 재설정
	void SetBitmap();	// 처음 비트맵을 설정할 함수

	std::vector<std::string> PatternID;
	PlayerData* nowPlayerData = nullptr; // 받아올 데이터를 가리키는 포인터
	PlayerAtkPetternData* nowPlayerPattenData = nullptr; //사용할 패턴 데이터를 가리키는 포인터
	PlayerAtkPetternData* prePlayerPattenData = nullptr;

	std::string PrePattenID;			// 이전 패턴의 ID
	std::string preStateName;			// 이전 상태를 저장하는 변수
	std::string oneLoopPreStateName;	// 한 루프 이전 상태를 저장하는 변수
	std::string nowStateName;			// 현재 상태

	// 플레이어 이미지 비트맵들
	std::shared_ptr<BitmapResource> PlayerBitmap = nullptr;
	BitmapRenderer* player_Idle = nullptr;
	BitmapRenderer* player_Attack1 = nullptr;
	BitmapRenderer* player_Attack2 = nullptr;
	BitmapRenderer* player_Attack3 = nullptr;
	BitmapRenderer* player_Guard = nullptr;
	BitmapRenderer* player_Damaged = nullptr;

	bool isAttackingPattern = false;	// ??
	
	bool isFirstGroggyLoop = false;		// 첫 그로기 루프인지 확인?
    
	// Debug
	void SetCursorPosition(int x, int y);         // 플레이어 출력함수
	void PrintConsole();

	float timer = 0.0f;
	float maxTimer = 2.0f;
	bool isCreatedResult = false;
	void ChecKChnageScene();	// 씬 교체를 해야하는지 확인하는 함수

	//맞는 이펙트 변수들
	EffectMonoB* PlayerHit{};

	EnemyAttackEffect* GuardEff{};

	//패리변수
	float TimeDelta = 0.0f;
	bool CheckPlayPerry = false;
	int currentStep = 0;
	float delays[3] = { 0.0f, 0.1f, 0.1f };
	
	std::vector<Vector2> ParryPosition{};
	
public:
	void CallGuardEffect(int num, Vector2 vector);
	void CallPerryEffect(const std::vector<Vector2>& list);
};
