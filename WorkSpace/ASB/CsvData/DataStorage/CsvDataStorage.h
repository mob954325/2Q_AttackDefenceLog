#pragma once
#include <string>
#include <unordered_map>
#include <typeinfo>
#include "Utils/Singleton.h"
#include "../DataClass/AllNodePattenClass.h"
#include "../DataClass/EnemyAtkPattenData.h"
#include "../DataClass/EnemyData.h"
#include "../DataClass/PlayerData.h"

/*2025.07.30 - 안성빈
   역할 : CsvDataStorage 클래스는 CSV 파일에서 읽어온 데이터를 unordered_map에 저장하는 클래스 
	
*/



class CsvDataManager;


// 스토리지들이 상속 받을 베이스 스토리지 클래스
template<typename T>
class CsvDataStorage
{ // CSV 데이터 저장 클래스
  // 맵 :   키 : 각 엑셀의 첫 번째 값    값 : 해당 행의 데이터를 저장하는 클래스의 포인터
public:
	CsvDataStorage() {};
	virtual ~CsvDataStorage() {};
	friend class Singleton<CsvDataManager>; // 싱글톤 패턴을 사용하기 위한 친구 클래스 선언

private:
	std::unordered_map<std::string, T* > DataMap;

public:

	// 데이터 클래스의 객체 생성
	T* CreateData() {
		T* tmpData = new T();
		return tmpData;
	}


	// 키와 값(데이터의 포인터)의 쌍을 맵에 저장
	void SetData(const std::string DataID, T* tmpData) {
		DataMap[DataID] = tmpData;
	}

	// 데이터를 가지는 함수
	T* GetData(const std::string DataID) {
		auto it = DataMap.find(DataID);
		if (it != DataMap.end()) {
			return it->second;
		}
	}

	void PrintData() {
		for (const auto& pair : DataMap) {
			pair.second->PrintMap(); // BaseData 클래스의 PrintMap 함수 호출
		}
	}
};