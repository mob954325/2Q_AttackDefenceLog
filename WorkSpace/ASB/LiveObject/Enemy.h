#pragma once
#include "LiveObject.h"
#include "../CsvData/DataClass/EnemyData.h"


class LiveObject;
class Enemy : public LiveObject
{
public:
	Enemy() = default;
	~Enemy() = default;
	void OnCreate();
	void OnStart();
	void OnUpdate();
	void OnFixedUpdate();
	void OnDestroy();


	// 플레이어의 상태를 초기화하는 함수
	void ResetPlayerState();
	void SetStatData(std::string tmp); // 스탯 데이터를 데이터에서 불러와 저장함

	//패턴 ID에 맞는 데이터를 포인터로 가리킴
	void SetAttackPattenData(std::string PattID) //  패턴ID에 맞는 가이드라인 데이터를 불러옴
	{
		nowPlayerPattenData = CsvDataManager::GetInstance().getDataImpl(nowPlayerPattenData, PattID);
	}

	void ResetSpiritAmount();

	// 배틀 매니저에서 사용될 함수
	void SelectPatten() override;   //플레이어가 사용할 패턴을 고름
	std::vector<int> GetNowPatten() override;   //플레이어의 현재 패턴의 노드를 반환함

	void DeciedState(const std::queue<int> tmpqueue) override;  //큐와 현재 패턴을 비교
	void CalStat() override;        //여기서 계산



	//업데이트에 들어갈 시간에 따라 변하는 함수들
	void CalSpiritTime() override;  //초당 기세 : -0.3
	void CalCooTime() override;     //플레이어의 쿨타임을 계산
	void SetCoolTime() override;	//쿨타임이 0이 되었을 때, 플레이어의 쿨타임 설정

	//스테이트 설정하는 함수
	void SetState(std::string setStateName) override;
	void OnCreateState() override;

	//플래그를 체크할 함수
	void ChangePatten() override;

	//패링 타이밍 계산 함수
	void CalAttackTimePercent();

	//반환하는 함수
	float GetAttackTimePercent() { return enermyTimePercent; }
	
private:
	std::vector<std::string> PattenID;
	PlayerData* nowPlayerData = nullptr; // 받아올 데이터를 가리키는 포인터
	PlayerAtkPetternData* nowPlayerPattenData = nullptr; //사용할 패턴 데이터를 가리키는 포인터
	PlayerAtkPetternData* prePlayerPattenData = nullptr;
	StateController<Enemy> m_State;  //오브젝트 들은 State 내부에서 받을 수 있도록 포인터 생성
	std::string PrePattenID;  // 이전 패턴의 ID
	float enermyTimePercent; // 패링 퍼센트 계산
private:
	std::string Difficulty;			   // 적의 난이도 
	EnemyData* nowEnemyData = nullptr; // 현재 적의 데이터 클래스를 담을 변수
};

