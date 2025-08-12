#pragma once
#include "LiveObject.h"
#include "../CsvData/DataClass/EnemyData.h"
#include "../CsvData/DataClass/EnemyAtkPattenData.h"
#include "../Component/StateController.h"
#include "../CsvData/DataClass/AllNodePattenClass.h"
#include "Components/Rendering/BitmapRenderer.h"


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

	//패턴 ID에 맞는 데이터를 포인터로 가리킴
	void SetAttackPattenData(std::string PattID); //  패턴ID에 맞는 가이드라인 데이터를 불러옴

	void ResetSpiritAmount();

	// 배틀 매니저에서 사용될 함수
	void SelectPatten() override;   //플레이어가 사용할 패턴을 고름
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
	bool isFirstSpiriteDown = false;
	bool isEnemyGroggyAttack = false;    // 플레이어가 그로기 상태일 때 Enemy 공격 상태 여부

	void RestoreGroggy();  // 초기화 겸, 외부에서도 호출해주는 함수임

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
	void ReserEnemy();
	
	
private:
	std::string Difficulty;					// 적의 난이도 k
	EnemyData* nowEnemyData = nullptr;		// 현재 적의 데이터 클래스를 담을 변수
	AllNodePattenClass* tmpNode = nullptr;
	
	std::string nowStateName;
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

	void SetBitmap();  // 비트맵 설정하는 함수	
};



	


	

