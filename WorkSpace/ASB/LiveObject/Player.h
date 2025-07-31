#pragma once
#include "LiveObject.h"
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
	void SetAllData(std::string tmp, float Object_SpiritAmount);
private:
	PlayerData* nowPlayerData = nullptr;

};

