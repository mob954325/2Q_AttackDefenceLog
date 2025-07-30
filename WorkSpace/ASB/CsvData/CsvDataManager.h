#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include "Utils/Singleton.h"
#include "DataStorage/CsvDataStorage.h"
#include <fcntl.h> // 콘솔창에 wstring을 출력하기 위한 헤더
#include <io.h>
/*25.07.29 - 안성빈.
	역할 : CsvDataManager 클래스는 CSV 파일을 읽어와서 데이터를 저장하는 클래스
		   CSV 파일의 첫 번째 셀을 키로 사용하고, 데이터 클래스의 포인터를 값으로 맵에 저장함

	주의 : baseData에 있는 데이터를 자료구조로 저장하는 함수(SetData)를 호출함으로 해당 클래스를 사용시 baseData를 상속받는것이 좋음
*/
/*25.07.30 - 안성빈
	 수정 : 원래 기능함수와 저장 객체가 같이 있었으나 저장 하는 객체를 따로 분리하여 매니저에서 관리하는 형태로 변환
			버전 c++14를 사용하여 if constexpr를 사용하지 못함으로, 디스패치 헬퍼 함수를 사용하여 타입에 맞는 함수를 호출함
			매니저를 데이터를 처리하는 중앙관리자로 만들고, 싱들톤을 상속받아 사라지지 않게 함
			각 데이터와	매니저는 CsvDataStorage 클래스를 상속받아 사용함
			디스패치 헬퍼 함수: 템플릿 인스턴스가 각 타입에 맞게 정적 바인딩되도록 설계된 도우미
								-> 그냥 함수를 오버로드하여 매개변수에 맞는 함수를 호출하는 방식인듯?
*/


class CsvDataManager : public Singleton<CsvDataManager>
{
public:
	CsvDataManager() = default; // 생성자
	~CsvDataManager() override; // 소멸자
	friend class Singleton<CsvDataManager>; // 싱글톤 패턴을 사용하기 위한 친구 클래스 선언
public:
	// 매개변수  : CSV 파일의 경로, 파일 내부 스킵할 라인의 수
	// CSV 파일을 읽어와서 std::unordered_map에 저장하는 함수

	template<typename T>
	void SetCSV(const std::string filePath, int skipLine);
	
	// 데이터 타입을 바탕으로 맵을 찾고, ID에 해당하는 데이터의 포인터를 반환함 
	template<typename T>
	T* GetCSV(const std::string DataID);


	// 콘솔용
	// 전체를 콘솔창에 띄우는 함수, 키와 값의 쌍을 출력하는 함수
	void PrintMap();

	
private:
	// CSV 데이터 저장 클래스
	CsvDataStorage<AllNodePattenClass> allNodePattenStorage;
	CsvDataStorage<EnemyAtkPattenData> enemyAtkPattenStorage;
	CsvDataStorage<EnemyData> enemyDataStorage;
	CsvDataStorage<PlayerAtkPetternData> playerAtkPetternStorage;
	CsvDataStorage<PlayerData> playerDataStorage;
	

	//CreateDate 헬퍼 함수
	template<typename T>
	T* CreateDataImpl(T* tag) {  return nullptr; } // 기본 정의 (에러 처리)
	AllNodePattenClass* CreateDataImpl(AllNodePattenClass* tag) { return allNodePattenStorage.CreateData(); }
	EnemyAtkPattenData* CreateDataImpl(EnemyAtkPattenData* tag) { return enemyAtkPattenStorage.CreateData(); }
	EnemyData* CreateDataImpl(EnemyData* tag) { return enemyDataStorage.CreateData(); }
	PlayerAtkPetternData* CreateDataImpl(PlayerAtkPetternData* tag) { return playerAtkPetternStorage.CreateData(); }
	PlayerData* CreateDataImpl(PlayerData* tag) { return playerDataStorage.CreateData(); }

	//SaveDataImpl 헬퍼 힘수
	void SaveDataImpl(const std::string& key, AllNodePattenClass* data) { allNodePattenStorage.SetData(key, data); }
	void SaveDataImpl(const std::string& key, EnemyAtkPattenData* data) { enemyAtkPattenStorage.SetData(key, data); }
	void SaveDataImpl(const std::string& key, EnemyData* data) { enemyDataStorage.SetData(key, data); }
	void SaveDataImpl(const std::string& key, PlayerAtkPetternData* data) { playerAtkPetternStorage.SetData(key, data); }
	void SaveDataImpl(const std::string& key, PlayerData* data) { playerDataStorage.SetData(key, data); }

	//
	template<typename T>
	void DispatchSaveData(const std::string& key, T* ptr) {
		static_assert(sizeof(T) == 0, "지원되지 않는 타입입니다");
	}
	template<>
	void DispatchSaveData<AllNodePattenClass>(const std::string& key, AllNodePattenClass* ptr) {
		allNodePattenStorage.SetData(key, ptr);
	}
	template<>
	void DispatchSaveData<EnemyData>(const std::string& key, EnemyData* ptr) {
		enemyDataStorage.SetData(key, ptr);
	}
	template<>
	void DispatchSaveData<PlayerAtkPetternData>(const std::string& key, PlayerAtkPetternData* ptr) {
		playerAtkPetternStorage.SetData(key, ptr);
	}
	template<>
	void DispatchSaveData<PlayerData>(const std::string& key, PlayerData* ptr) {
		playerDataStorage.SetData(key, ptr);
	}

	//GetData 헬퍼
	AllNodePattenClass* getDataImpl(AllNodePattenClass* tag, std::string ID) 
		{ return allNodePattenStorage.GetData(ID); }
	EnemyAtkPattenData* getDataImpl(EnemyAtkPattenData* tag, std::string ID)
		{return enemyAtkPattenStorage.GetData(ID);}
	EnemyData* getDataImpl(EnemyData* tag, std::string ID)
		{return enemyDataStorage.GetData(ID);}
	PlayerAtkPetternData* getDataImpl(PlayerAtkPetternData* tag, std::string ID)
		{return playerAtkPetternStorage.GetData(ID);}
	PlayerData* getDataImpl(PlayerData* tag, std::string ID)
		{return playerDataStorage.GetData(ID);}
};


//if constexpr :  조건에 맞는 분기는 아예 컴파일되고 조건이 맞지 않는 분기는 컴파일되지 않음



template<typename T>
void CsvDataManager::SetCSV(const std::string filePath, int skipLine) {
	static_assert(std::is_base_of_v<BaseData, T>); // T가 BaseData를 상속받는지 확인하는 문장


	//데이터 클래스 T의 타입을 검사해서 같다면 데이터 저장소에서 데이터 클레스 생성함수 호출
	T* tmpData = CreateDataImpl(static_cast<T*>(nullptr));

	std::wifstream file(filePath); // 파일 스트림 생성
	if (!file.is_open()) {  // 파일 열기 실패 시 에러 메시지 출력
		//std::cout << "파일을 열 수 없습니다: " << file << std::endl;
	}

	// 각 데이터 타입에 따라서 생성되는 변수가 다름


	std::wstring line;	 // 현재 줄을 저장할 변수
	int countLine = 1;	 // 시작 라인 번호 (1부터 시작)


	while (std::getline(file, line)) {
		if (countLine++ <= skipLine) continue; // 헤더 건너뛰기


		std::wstringstream ss(line);   // 문자열 스트림 생성
		std::wstring cell;			   // 각 셀을 저장할 변수
		std::vector<std::wstring> row; // 현재 행의 셀들을 저장할 벡터
		std::wstring key;	           // 키로 사용할 첫 번째 셀의 값
		bool isFirst = true;           // 첫 번째 셀인지 여부를 확인하는 플래그

		while (std::getline(ss, cell, L',')) {
			if (isFirst) {		 // 첫 번째 셀을 키로 사용
				key = cell;
				isFirst = false;
			}
			row.push_back(cell); // 나머지 셀은 벡터에 추가
		}

		//데이터 클래스 객체에 한 행의 데이터를 vector<wstring>로 값을 넣어줌
		tmpData->SetData(row); // SetData 함수를 호출하여 데이터를 설정




		// 예외처리
		// key가 비어있으면 저장하지 않음 (보호 로직)
		//
		if (!key.empty()) {
			//SaveDataImpl(key, tmpData); // SaveDataImpl 함수를 호출하여 데이터를 저장
			this->DispatchSaveData(key, tmpData); // DispatchSaveData 함수를 호출하여 데이터를 저장
		}
	}
	// 데이터를 저장하는 함수 필요함!!!
	file.close();
}



template<typename T>
T* CsvDataManager::GetCSV(const std::string DataID) {
	return getDataImpl(static_cast<T*>(nullptr), DataID);
}
