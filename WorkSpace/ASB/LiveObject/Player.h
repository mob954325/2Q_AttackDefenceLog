#pragma once
#include "LiveObject.h"

/* 25.08.01
     플레이어의 데이터 불러오기 -> 일관성 없음?
		- 스탯 : hp 같은 스탯들은 변해야 함으로 저장공간을 만들어 데이터를 인가하는 형태로 진행
		- 패턴 : 패턴은 게임 진행상에 변하지 않음으로 포인터로 가리키게 만들어 사용할 예정
*/

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
private:
	std::vector<std::string> PattenID;
	PlayerData* nowPlayerData = nullptr; // 받아올 데이터를 가리키는 포인터
	PlayerAtkPetternData* nowPlayerPattenData = nullptr; //사용할 패턴 데이터를 가리키는 포인터
	float Object_BaseSpiritAmount = 0.0f;
};

