#include "CsvDataManager.h"
#include "DataStorage/CsvDataStorage.h"
////
#include "DataClass/AllNodePattenClass.h"
#include "DataClass/EnemyAtkPattenData.h"
#include "DataClass/EnemyData.h"
#include "DataClass/PlayerData.h"

// 스킵	라인 수를 반환하는 기본 템플릿 함수 정의
template<typename T>
int CsvDataManager::GetSkipLine(T* tag) {}

template<>
int CsvDataManager::GetSkipLine<AllNodePattenClass>(AllNodePattenClass* tag) {
	return  SkipLineData[0];
}
template<>
int CsvDataManager::GetSkipLine<EnemyAtkPattenData>(EnemyAtkPattenData* tag) {
	return SkipLineData[1];
}
template<>
int CsvDataManager::GetSkipLine<EnemyData>(EnemyData* tag) {
	return SkipLineData[2];
}
template<>
int CsvDataManager::GetSkipLine<PlayerAtkPetternData>(PlayerAtkPetternData* tag) {
	return SkipLineData[3];
}
template<>
int CsvDataManager::GetSkipLine<PlayerData>(PlayerData* tag) {
	return SkipLineData[4];
}





// CreateDataImpl 헬퍼 함수 정의 (기본 템플릿)
template<typename T>
T* CsvDataManager::CreateDataImpl(T* tag) {
	return nullptr; // 기본 정의 (에러 처리 또는 nullptr 반환)
}

// CreateDataImpl 명시적 특수화 정의
template<>
AllNodePattenClass* CsvDataManager::CreateDataImpl<AllNodePattenClass>(AllNodePattenClass* tag) {
	return allNodePattenStorage.CreateData();
}
template<>
EnemyAtkPattenData* CsvDataManager::CreateDataImpl<EnemyAtkPattenData>(EnemyAtkPattenData* tag) {
	return enemyAtkPattenStorage.CreateData();
}
template<>
EnemyData* CsvDataManager::CreateDataImpl<EnemyData>(EnemyData* tag) {
	return enemyDataStorage.CreateData();
}
template<>
PlayerAtkPetternData* CsvDataManager::CreateDataImpl<PlayerAtkPetternData>(PlayerAtkPetternData* tag) {
	return playerAtkPetternStorage.CreateData();
}
template<>
PlayerData* CsvDataManager::CreateDataImpl<PlayerData>(PlayerData* tag) {
	return playerDataStorage.CreateData();
}



// DispatchSaveData 헬퍼 함수 정의 (기본 템플릿)
template<typename T>
void CsvDataManager::DispatchSaveData(const std::string& key, T* ptr) {
	static_assert(sizeof(T) == 0, "지원되지 않는 타입입니다 (기본 DispatchSaveData 템플릿)");
}

// DispatchSaveData 명시적 특수화 정의
template<>
void CsvDataManager::DispatchSaveData<AllNodePattenClass>(const std::string& key, AllNodePattenClass* ptr) {
	allNodePattenStorage.SetData(key, ptr);
}
template<>
void CsvDataManager::DispatchSaveData<EnemyAtkPattenData>(const std::string& key, EnemyAtkPattenData* ptr) {
	enemyAtkPattenStorage.SetData(key, ptr);
}
template<>
void CsvDataManager::DispatchSaveData<EnemyData>(const std::string& key, EnemyData* ptr) {
	enemyDataStorage.SetData(key, ptr);
}
template<>
void CsvDataManager::DispatchSaveData<PlayerAtkPetternData>(const std::string& key, PlayerAtkPetternData* ptr) {
	playerAtkPetternStorage.SetData(key, ptr);
}
template<>
void CsvDataManager::DispatchSaveData<PlayerData>(const std::string& key, PlayerData* ptr) {
	playerDataStorage.SetData(key, ptr);
}


//IDData를 반환하는 헬퍼 함수 정의 (기본 템플릿)
template<typename T>
std::vector<std::string> CsvDataManager::GetIDData(T* tag) {}

template<>
std::vector<std::string> CsvDataManager::GetIDData(AllNodePattenClass* tag) {
	return allNodePattenStorage.GetIDVect();
}
template<>
std::vector<std::string> CsvDataManager::GetIDData(EnemyAtkPattenData* tag) {
	return enemyAtkPattenStorage.GetIDVect();
}
template<>
std::vector<std::string> CsvDataManager::GetIDData(EnemyData* tag) {
	return enemyDataStorage.GetIDVect();
}
template<>
std::vector<std::string> CsvDataManager::GetIDData(PlayerAtkPetternData* tag) {
	return playerAtkPetternStorage.GetIDVect();
}
template<>
std::vector<std::string> CsvDataManager::GetIDData(PlayerData* tag) {
	return playerDataStorage.GetIDVect();
}



// getDataImpl 헬퍼 함수 정의 (기본 템플릿)
template<typename T>
T* CsvDataManager::getDataImpl(T* tag, std::string ID) {
	return nullptr; // 기본 정의 (에러 처리 또는 nullptr 반환)
}

// getDataImpl 명시적 특수화 정의
template<>
AllNodePattenClass* CsvDataManager::getDataImpl<AllNodePattenClass>(AllNodePattenClass* tag, std::string ID) {
	return allNodePattenStorage.GetData(ID);
}
template<>
EnemyAtkPattenData* CsvDataManager::getDataImpl<EnemyAtkPattenData>(EnemyAtkPattenData* tag, std::string ID) {
	return enemyAtkPattenStorage.GetData(ID);
}
template<>
EnemyData* CsvDataManager::getDataImpl<EnemyData>(EnemyData* tag, std::string ID) {
	return enemyDataStorage.GetData(ID);
}
template<>
PlayerAtkPetternData* CsvDataManager::getDataImpl<PlayerAtkPetternData>(PlayerAtkPetternData* tag, std::string ID) {
	return playerAtkPetternStorage.GetData(ID);
}
template<>
PlayerData* CsvDataManager::getDataImpl<PlayerData>(PlayerData* tag, std::string ID) {
	return playerDataStorage.GetData(ID);
}



template<typename T>
void CsvDataManager::PrintMap(T* tag) {
	std::cout << "PrintMap called for type: null" << std::endl;
}

// CreateDataImpl 명시적 특수화 정의
template<>
void CsvDataManager::PrintMap<AllNodePattenClass>(AllNodePattenClass* tag) {
	allNodePattenStorage.PrintData();
}
template<>
void CsvDataManager::PrintMap<EnemyAtkPattenData>(EnemyAtkPattenData* tag) {
	enemyAtkPattenStorage.PrintData();
}
template<>
void CsvDataManager::PrintMap<EnemyData>(EnemyData* tag) {
	enemyDataStorage.PrintData();
}
template<>
void CsvDataManager::PrintMap<PlayerAtkPetternData>(PlayerAtkPetternData* tag) {
	playerAtkPetternStorage.PrintData();
}
template<>
void CsvDataManager::PrintMap<PlayerData>(PlayerData* tag) {
	playerDataStorage.PrintData();
}