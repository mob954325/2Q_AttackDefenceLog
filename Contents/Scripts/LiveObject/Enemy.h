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
	void OnCreate() {};
	void OnStart();
	void OnUpdate();
	void OnFixedUpdate() {};
	void OnDestroy() {};


	// 플레이어의 상태를 초기화하는 함수
	void ResetPlayerState() {};
	void SetStatData(std::string tmp); // 스탯 데이터를 데이터에서 불러와 저장함

	//패턴 ID에 맞는 데이터를 포인터로 가리킴
	void SetAttackPattenData(std::string PattID); //  패턴ID에 맞는 가이드라인 데이터를 불러옴

	void ResetSpiritAmount();

	// 배틀 매니저에서 사용될 함수
	void SelectPatten() override;   //플레이어가 사용할 패턴을 고름
	void SetNowPatten() override;   //플레이어의 현재 패턴의 노드를 반환함



	//업데이트에 들어갈 시간에 따라 변하는 함수들
	void CalSpiritTime() override;  //초당 기세 : -0.3
	void SetCoolTime() override;	//쿨타임이 0이 되었을 때, 플레이어의 쿨타임 설정
	void StateAct();
	void DiffState();

	//스테이트 설정하는 함수
	void SetState(std::string setStateName) override;
	void OnCreateState() override;

	//플래그를 체크할 함수
	void AddPattenLoop() override;

	//반환하는 함수


	StateController* m_State = nullptr;  //오브젝트 들은 State 내부에서 받을 수 있도록 포인터 생성
private:
	std::vector<std::string> PattenID;
	EnemyAtkPattenData* nowEnemyPattenData = nullptr; //사용할 패턴 데이터를 가리키는 포인터
	EnemyAtkPattenData* preEnemyPattenData = nullptr;

	std::string PrePattenID;  // 이전 패턴의 ID
	float enermyTimePercent; // 패링 퍼센트 계산
	void PrintConsole();
	void SetCursorPosition(int x, int y);
	AttackPatternManager* m_PattenManager = nullptr; // 패턴 매니저를  참조로 받아  사용할 변수
private:
	std::string Difficulty;			   // 적의 난이도 
	EnemyData* nowEnemyData = nullptr; // 현재 적의 데이터 클래스를 담을 변수
	AllNodePattenClass* tmpNode = nullptr;
	
	std::string nowStateName;
	std::string preStateName;
	float groggyTime = 0.0f;

	std::shared_ptr<BitmapResource> PlayerBitmap = nullptr;
	BitmapRenderer* enemy_Idle = nullptr;
	BitmapRenderer* enemy_Attack = nullptr;
	BitmapRenderer* enemy_Guard = nullptr;
	BitmapRenderer* enemy_Damaged = nullptr;
	void SetBitmap();  // 비트맵 설정하는 함수


	std::shared_ptr<BitmapResource> EnemyBitmap = nullptr;
};

