#pragma once
#include "LiveObject.h"
#include <functional>
#include "../CsvData/DataClass/EnemyData.h"
#include "../CsvData/DataClass/EnemyAtkPattenData.h"
#include "../Component/StateController.h"
#include "../CsvData/DataClass/AllNodePattenClass.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Scripts/Effect/HitEffect.h"
#include "Scripts/Effect/EnemyAttackEffect.h"
#include "Utils/GameTime.h"


class LiveObject;
class Enemy : public LiveObject
{
public:
	Enemy() = default;
	~Enemy() = default;

	void OnStart();
	void OnUpdate();


private:
	// 적 공격 패턴 고정
	std::string  enemyAttackPatternFix = " ";   //<=== 해당 ID의 적 공격 ID, 안쓰면  " " 안에 EP쓰지말기  
	//ex) "EP_013"

public:
	// 플레이어의 상태를 초기화하는 함수
	void ResetPlayerState() {};
	void SetStatData(std::string tmp); // 스탯 데이터를 데이터에서 불러와 저장함
	float eSpriteDamage_Second = 0.0f; //  초당 줄어들 기세데미지
	//패턴 ID에 맞는 데이터를 포인터로 가리킴
	void SetAttackPattenData(std::string PattID); //  패턴ID에 맞는 가이드라인 데이터를 불러옴

	void ResetSpiritAmount();

	// 배틀 매니저에서 사용될 함수
	void SelectPattern() override;   //플레이어가 사용할 패턴을 고름
	void SetNowPattern() override;  

	//업데이트에 들어갈 시간에 따라 변하는 함수들
	void CalSpiritTime() override;  //초당 기세 : -0.3
	void SetCoolTime() override;	//쿨타임이 0이 되었을 때, 플레이어의 쿨타임 설정
	void StateAct();				// 상태에 따른 행동 호출 함수
	void DiffState();				// 상태 변환과 그로기 관련 업데이트 함수 포함되어있음
	
	//스테이트 설정하는 함수
	void SetState(std::string setStateName) override;
	void OnCreateState() override;

	//플래그를 체크할 함수
	void AddPattenLoop() override;

	StateController* m_State = nullptr;  // 오브젝트 들은 State 내부에서 받을 수 있도록 포인터 생성
	
	
	bool isPatternLive = false;

	void RestoreGroggy();  // 초기화 겸, 외부에서도 호출해주는 함수임


	float OtherGroggyTime = 0.0f; // 플레이어의 그로기 타임
	bool IsOtherEndGroggy = false;
	bool IsOtherGroggy = false;
	bool restoredThisCycle = false; // 복구 되었는가를 체크하는 플래그


	void SetNameDiff(std::string name, std::string difficulty); // 밖에서 추가할 때 ID를 미리 생성할 수 있게 함
private:
	// 적이 가지고 있는 공격의 ID
	std::vector<std::string> PattenID;

	// 위의 벡터에 해당하는 값을 밑의 맵과 매핑하는 맵 
	std::unordered_map<std::string, int> PattenMap;

	//적이 가지고 있는 전체 공격 시트의 ID
	std::vector<std::string> TotalPatternID;
	
	EnemyAtkPattenData* nowEnemyPattenData = nullptr; //사용할 패턴 데이터를 가리키는 포인터
	EnemyAtkPattenData* preEnemyPattenData = nullptr;

	// 패턴을 찾는 방식
	// 
	// 1. 적의 연격의 처음 패턴을 저장할 vector1    2. 적의 전체 공격 패턴을 저장할 vector2
	// 3. vector1에서 nowRandomValue를 활용하여 패턴을 결정
	// 4. 연격이라면, 
	// 5. 2 vector에서 연격 패턴이 끝날때까지 patternCount를 증가시키며 패턴을 찾음

	//이전 패턴의 변수를 저장 할 함수!
	int nowRandomValue = 0;  // 적이 가지고 있는 연속 공격 패턴을 정하는 변수
	int preRandomValue = 0;
	int patternCount = 0;	 // 연격일 경우 다음 패턴을 정하는 변수


	std::string PrePattenID;  // 이전 패턴의 ID
	float enermyTimePercent; // 패링 퍼센트 계산
	void PrintConsole();
	void SetCursorPosition(int x, int y);
	AttackPatternManager* m_PattenManager = nullptr; // 패턴 매니저를  참조로 받아  사용할 변수
	void ResetEnemy();
	
public:
	//이펙트호출함수
	void CallPlayerHit(int num, Vector2 position, float rotate);

	// 적의 state 
	//"Enemy_Idle"							// 평소 상태 - Default State  
	//"Enemy_AttackSuccess"					// 공격 성공
	//"Enemy_AttackFail"					// 공격 실패 
	//"Enemy_Hit"							// 패턴 파회 X, 맞음
	//"Enemy_Defence"						// 패턴 파회 X, 막음
	//"Enemy_Groggy"						// 패턴 파회 X, 막음
	//"Enemy_Dead"					        // 죽음
	std::string nowStateName; //현재 상태의 이름, 이걸로 알아낼 수 있음!!

private:
	std::string Difficulty;					// 적의 난이도 k
	EnemyData* nowEnemyData = nullptr;		// 현재 적의 데이터 클래스를 담을 변수
	AllNodePattenClass* tmpNode = nullptr;
	

	std::string preStateName;
	float groggyTime = 0.0f;
	
	// 이미지 관련 ==================================================
	std::shared_ptr<BitmapResource> EnemyBitmap = nullptr;
	BitmapRenderer* enemy_Idle = nullptr;
	BitmapRenderer* enemy_Attack = nullptr;
	BitmapRenderer* enemy_Guard = nullptr;
	BitmapRenderer* enemy_Damaged = nullptr;


	// 이미지 이름을 받아올 변수
	std::wstring enemy_IdlePath;
	std::wstring enemy_AttackPath;
	std::wstring enemy_GuardPath;
	std::wstring enemy_DamagedPath;
	//  이미지의 공통된 위치
	std::wstring enemy_CommonPath;

	std::string  Enemy_ID; // 적 ID를 받을 변수 


	void SetBitmap();  // 비트맵 설정하는 함수	

	float deadTimer = 0.0f;
	float deadMaxTimer = 1.5f;
	bool isDeadAnimationEnd = false;
	void UpdateDeadAnimation();

	float sceneExittimer = 0.0f;
	float sceneExitMaxTimer = 3.0f;
	bool isCreatedResult = false;
	void CheckChangeScene();	// 씬 교체를 해야하는지 확인하는 함수

	//적 히트 이펙트
	HitEffect* Hiteff{};

	EnemyAttackEffect* GuardEff{};

	// 적 state에 따른 enter, exit 함수들
	void AtkSucEnter();
	void DefEnter();
	void HitEnter();

	void AtkSucExit();
	void DefExit();
	void HitExit();

	// 둘다 Exit에 초기화 하기!!!
	float limitStateMoveTimer = 0.0f; // 각 상태에 따라 움직일 시간
	float nowStateMoveTimer = 0.0f;   // 각 상태에 따라 움직이는 현재 시간
	float StateProgress = 0.0f;		  // 각 상태에 따라 전체 transform시간을 정규화 하여 입력

	Vector2 toPosX   = { 0.0f, 0.0f };
	Vector2 toPosY  = { 0.0f, 0.0f };
	Vector2	fromPos = { 0.0f, 0.0f };
	Vector2 IdlePos = { 0.0f, 0.0f };

public:
	void CallGuardEffect(int num , Vector2 vector);
	// stage 구별용
	int nameIndex = -1; // 0 : 1스테이지, 1 : 2스테이지, 2 : 3스테이지
};



	


	

