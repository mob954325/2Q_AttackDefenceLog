#pragma once
#include <string>
#include <unordered_map>
#include "../DataClass/AllNodePattenClass.h"
#include "../DataClass/EnemyAtkPattenData.h"
#include "../DataClass/EnemyData.h"
#include "../DataClass/PlayerAtkPetternData.h"
#include "../DataClass/PlayerData.h"

class CsvDataStorage
{ // CSV 데이터 저장 클래스
  // 맵 :   키 : 각 엑셀의 첫 번째 값    값 : 해당 행의 데이터를 저장하는 클래스의 포인터
	 
	std::unordered_map<std::string, AllNodePattenClass* > allNodePatternMap;
	std::unordered_map<std::string, EnemyAtkPattenData* > enemyAtkPatternDataMap;
	std::unordered_map<std::string, EnemyData* > enemyDataMap;
	std::unordered_map<std::string, PlayerAtkPetternData* > playerAtkPetternDataMap;
	std::unordered_map<std::string, PlayerData* > playerDataMap;
};

