#pragma once
#include "LiveObject.h"
#include "../CsvData/DataClass/PlayerData.h"
#include "../Component/StateController.h"


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
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnFixedUpdate() override {};
	void OnDestroy() override {};
	

	// 플레이어의 상태를 초기화하는 함수
	void SetStatData(std::string tmp); // 스탯 데이터를 데이터에서 불러와 저장함
	void SetSpiritData(float enemy_SpiritAmount); // 배틀매니저에서 적을 불러와서 생성함!!
	void SetAttackPattenData(std::string PattID); //  패턴ID에 맞는 가이드라인 데이터를 불러옴
	void ResetSpiritAmount();

	// 배틀 매니저에서 사용될 함수
	void SelectPatten() override;   //플레이어가 사용할 패턴을 고름
	void SetNowPatten() override;   //플레이어의 현재 패턴의 노드를 반환함


	//업데이트에 들어갈 시간에 따라 변하는 함수들
	void CalSpiritTime() override;  //초당 기세 : -0.3
	void SetCoolTime() override;	//쿨타임이 0이 되었을 때, 플레이어의 쿨타임 설정

	
	//스테이트 설정하는 함수
	void SetState(std::string setStateName) override;
	void OnCreateState() override;

	//플래그를 체크할 함수
	void AddPattenLoop() override;
	StateController* m_State;  //오브젝트 들은 State 내부에서 받을 수 있도록 포인터 생성
private:
	std::vector<std::string> PattenID;    
	PlayerData* nowPlayerData = nullptr; // 받아올 데이터를 가리키는 포인터
	PlayerAtkPetternData* nowPlayerPattenData = nullptr; //사용할 패턴 데이터를 가리키는 포인터
	PlayerAtkPetternData* prePlayerPattenData = nullptr;
	
	std::string PrePattenID;		  // 이전 패턴의 ID
};

