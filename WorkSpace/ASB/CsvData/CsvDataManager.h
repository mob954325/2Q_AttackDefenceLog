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
#include "Utils/StringConvert.h"
#include <fcntl.h> // 콘솔창에 wstring을 출력하기 위한 헤더
#include <io.h>

// 필요한 클래스들의 전방 선언
// 이 클래스들의 실제 정의가 담긴 헤더 파일들이 포함되어야 합니다.
class AllNodePattenClass;
class EnemyAtkPattenData;
class EnemyData;
class PlayerAtkPetternData;
class PlayerData;
class BaseData; // BaseData가 정의된 헤더가 포함되어 있는지 확인하세요.

// 패치노트
/*25.07.29 - 안성빈
	역할 : CsvDataManager 클래스는 CSV 파일을 읽어와서 데이터를 저장하는 클래스
		   CSV 파일의 첫 번째 셀을 키로 사용하고, 데이터 클래스의 포인터를 값으로 맵에 저장함

	주의 : baseData에 있는 데이터를 자료구조로 저장하는 함수(SetData)를 호출함으로 해당 클래스를 사용시 baseData를 상속받는것이 좋음

*/

/*25.07.30 - 안성빈
	수정 : 원래 기능함수와 저장 객체가 같이 있었으나 저장 하는 객체를 따로 분리하여 매니저에서 관리하는 형태로 변환
		   버전 c++14를 사용하여 if constexpr를 사용하지 못함으로, 디스패치 헬퍼 함수를 사용하여 타입에 맞는 함수를 호출함
		   매니저를 데이터를 처리하는 중앙관리자로 만들고, 싱들톤을 상속받아 사라지지 않게 함
		   각 데이터와 매니저는 CsvDataStorage 클래스를 상속받아 사용함
		   디스패치 헬퍼 함수: 템플릿 인스턴스가 각 타입에 맞게 정적 바인딩되도록 설계된 도우미
		   -> 그냥 함수를 오버로드하여 매개변수에 맞는 함수를 호출하는 방식인듯?
*/

/*25.07.31 - 안성빈
	수정 : 템플릿의 명시적 구체화를 이용해서 명시적으로 매개변수 타입에 맞는 함수 명시적으로 지정해주고 컴파일러가 그에 맞추어 함수를 실행
		   하도록 수정
		   오류 수정
		   skipLine을 외부에서 입력하는 것이 아니라 미리 배열로 저장해놓는 형태로 변경
*/

/* 현재 함수
   역할 : 매니저를 템플릿으로 만들지 않고, 함수를 탬플릿으로 만들어서 여러가지 데이터를 관리하는 데이터 중앙관리자로 설계

   함수 : 
         void SetCSV :  데이터 시트에서 값을 읽고 각 데이터 저장소에 데이터를 저장
		 void PrintMap(T* Tag) : 데이터 전부를 콘솔창에 띄움
		 int GetSkipLine(T* tag) : 각 데이터시트마다 건너띌 줄의 수를 받아오는 함수
*/


class CsvDataManager : public Singleton<CsvDataManager>
{
public:
	friend class Singleton<CsvDataManager>;

public:
	template<typename T>
	void SetCSV(std::string filePath);

	// PrintMap 헬퍼 함수 선언 (클래스 내에는 선언만)
	template<typename T>
	void PrintMap(T* Tag);


	template<typename T>
	int GetSkipLine(T* tag);

	// GetData 헬퍼 함수 선언 (클래스 내에는 선언만)
	template<typename T>
	T* getDataImpl(T* tag, std::string ID);

	
private:
	// CSV 데이터 저장 클래스 인스턴스
	CsvDataStorage<AllNodePattenClass> allNodePattenStorage;
	CsvDataStorage<EnemyAtkPattenData> enemyAtkPattenStorage;
	CsvDataStorage<EnemyData> enemyDataStorage;
	CsvDataStorage<PlayerAtkPetternData> playerAtkPetternStorage;
	CsvDataStorage<PlayerData> playerDataStorage;

	// CreateDataImpl 헬퍼 함수 선언 (클래스 내에는 선언만)
	template<typename T>
	T* CreateDataImpl(T* tag);


	// DispatchSaveData 헬퍼 함수 선언 (클래스 내에는 선언만)
	template<typename T>
	void DispatchSaveData(const std::string& key, T* ptr);



	// 스킵라인을 저장하는 데이터
	// 데이터에 윗 줄이 추가되면 추가로 조정필요!!!!
	//0 : AllNodePattenClass, EnemyAtkPattenData, EnemyData, PlayerAtkPetternData, PlayerData
	int SkipLineData[5] = { 5,5,5,11,5 };

};


// SetCSV 템플릿 멤버 함수 정의
template<typename T>
void CsvDataManager::SetCSV(std::string filePath) {
	static_assert(std::is_base_of_v<BaseData, T>, "T는 BaseData를 상속받아야 합니다.");

	

	std::wifstream file(filePath);
	file.imbue(std::locale(".UTF-8"));
	if (!file.is_open()) {
		std::cout << L"파일을 열 수 없습니다: " << filePath << std::endl;
		return;
	}

	std::wstring line;
	int countLine = 1;
	int skipLineNum = GetSkipLine(static_cast<T*>(nullptr));

	while (std::getline(file, line)) {
		if (countLine++ <= skipLineNum) continue;
		T* tmpData = CreateDataImpl(static_cast<T*>(nullptr));
		std::wstringstream ss(line);
		std::vector<std::wstring> row;
		std::wstring cell;
		std::string key;
		bool isFirst = true;

		while (std::getline(ss, cell, L',')) {
			if (isFirst) {
				key = StringConvert::WstringToString(cell.c_str());
				isFirst = false;
			}
			row.push_back(cell);
		}

		if (tmpData) {
			tmpData->SetData(row);
		}
		else {
			std::wcerr << L"CreateDataImpl이 nullptr을 반환했습니다. 데이터 생성을 건너뜁니다." << std::endl;
			continue;
		}

		if (!key.empty()) {
			// DispatchSaveData 함수를 호출하여 데이터를 저장 (태그 디스패치)
			DispatchSaveData<T>(key, tmpData);
		}
	}
	file.close();
}


// 각 데이터의 스킵라인을 저장하는 구조체
