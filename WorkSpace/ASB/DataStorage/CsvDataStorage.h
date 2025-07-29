#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>

#include <fcntl.h> // 콘솔창에 wstring을 출력하기 위한 헤더
#include <io.h>

/*25.07.29 - 안성빈
	역할 : CsvDataStorage 클래스는 CSV 파일을 읽어와서 데이터를 저장하는 클래스
		  CSV 파일의 첫 번째 셀을 키로 사용하고, 데이터 클래스의 포인터를 값으로 맵에 저장함

	주의 : baseData에 있는 벡터를 자료구조로 저장하는 함수(SetData)를 호출함으로 해당 클래스를 사용시 baseData를 상속받는것이 좋음

*/



template<typename T >
class CsvDataStorage {
public:
	CsvDataStorage() {};
	~CsvDataStorage() {};

	std::unordered_map<std::wstring, T*> DataMap; // 키와 값의 쌍을 저장할 맵, 키는 주로 ID



	// 매개변수  : CSV 파일의 경로, 파일 내부 스킵할 라인의 수
	// CSV 파일을 읽어와서 std::unordered_map에 저장하는 함수
	// map의 키 : 첫 번째 셀의 값(ID), 
	//		 값 : 해당 행의 데이터를 저장하는 클래스의 포인터
	void SetCSV(const std::string& filePath, int skipLine) {

		std::wifstream file(filePath); // 파일 스트림 생성

		
		if (!file.is_open()) {  // 파일 열기 실패 시 에러 메시지 출력
			//std::cout << "파일을 열 수 없습니다: " << file << std::endl;
		}


		std::wstring line;	 // 현재 줄을 저장할 변수
		int countLine = 1;	 // 시작 라인 번호 (1부터 시작)
		

		while (std::getline(file, line)) {
			T* tmpData = new T(); // 데이터 클래스의 객체 생성
			if (countLine++ <= skipLine) continue; // 헤더 건너뛰기

			std::wstringstream ss(line);   // 문자열 스트림 생성
			std::wstring cell;			  // 각 셀을 저장할 변수
			std::vector<std::wstring> row; // 현재 행의 셀들을 저장할 벡터
			std::wstring key;	          // 키로 사용할 첫 번째 셀의 값
			bool isFirst = true;          // 첫 번째 셀인지 여부를 확인하는 플래그

			while (std::getline(ss, cell, L',')) {
				if (isFirst) {		 // 첫 번째 셀을 키로 사용
					key = cell;
					isFirst = false;
				}
				row.push_back(cell); // 나머지 셀은 벡터에 추가
			}

			// 데이터 클래스 객체에 데이터를 넣음
			// T는 BaseData를 상속받는 클래스의 객체로, SetData 함수가 정의되어 있어야 함
			tmpData->SetData(row);


			// 예외처리
			// key가 비어있으면 저장하지 않음 (보호 로직)
			if (!key.empty()) {
				DataMap[key] = tmpData; // 키와 값(데이터의 포인터)의 쌍을 맵에 저장
			}
		}

		file.close();
	}



	// 콘솔용
	// 전체를 콘솔창에 띄우는 함수, 키와 값의 쌍을 출력하는 함수,
	void PrintMap() {
		for (auto it = DataMap.begin(); it != DataMap.end(); ++it) {
			
			it->second->PrintMap(); // BaseData 클래스의 PrintMap 함수 호출
		}
	}
};

