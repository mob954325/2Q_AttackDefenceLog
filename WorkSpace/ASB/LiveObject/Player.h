#pragma once
#include "LiveObject.h"
#include "../CsvData/DataClass/PlayerData.h"

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
	void OnCreate();
	void OnStart();
	void OnUpdate();
	void OnFixedUpdate();
	void OnDestroy();

	// 플레이어의 상태를 초기화하는 함수
	void ResetPlayerState();
	void SetStatData(std::string tmp, float Object_SpiritAmount); // 스탯 데이터를 데이터에서 불러와 저장함
	void SetAttackPattenData(std::string PattID); //  패턴ID에 맞는 가이드라인 데이터를 불러옴
	void ResetSpiritAmount();

	// 배틀 매니저에서 사용될 함수
	void SelectPatten() override;   //플레이어가 사용할 패턴을 고름
	void DeciedState(const std::queue<int> tmpqueue) override;  //큐와 현재 패턴을 비교
	void CalStat() override;        //여기서 계산

	//업데이트에 들어갈 시간에 따라 변하는 함수들
	void CalSpiritTime() override;  //초당 기세 : -0.3
	void CalCooTime() override;     //플레이어의 쿨타임을 계산
	void SetCoolTime() override;	//쿨타임이 0이 되었을 때, 플레이어의 쿨타임 설정


private:
	std::vector<std::string> PattenID;    
	PlayerData* nowPlayerData = nullptr; // 받아올 데이터를 가리키는 포인터
	PlayerAtkPetternData* nowPlayerPattenData = nullptr; //사용할 패턴 데이터를 가리키는 포인터
};

