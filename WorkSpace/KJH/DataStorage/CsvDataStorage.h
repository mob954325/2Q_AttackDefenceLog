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

/*


*/



template<typename T >
class CsvDataStorage {
public:
	CsvDataStorage() {};

	// 매개변수  : CSV 파일의 경로, 파일 내부 스킵할 라인의 수
	// CSV 파일을 읽어와서 std::unordered_map에 저장하는 함수
	// map의 키 : 첫 번째 셀의 값(ID), 
	//		 값 : 해당 행의 데이터를 저장하는 클래스의 포인터
	static void SetCSV(const std::string& path, std::unordered_map<std::wstring, T>& outMap) {

		std::wifstream file(path); // 파일 스트림 생성

		
		if (!file.is_open()) {  // 파일 열기 실패 시 에러 메시지 출력
			//std::cout << "파일을 열 수 없습니다: " << file << std::endl;
		}

		while (std::getline(file, line)) {
			T tmpData; // 데이터 클래스의 객체 생성
			//if (countLine++ <= skipLine) continue; // 헤더 건너뛰기

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
				else{
					row.push_back(cell);
				} // 나머지 셀은 벡터에 추가
			}

			// 데이터 클래스 객체에 데이터를 넣음
			// T는 BaseData를 상속받는 클래스의 객체로, SetData 함수가 정의되어 있어야 함
			tmpData.SetData(row);


			// 예외처리
			// key가 비어있으면 저장하지 않음 (보호 로직)
			if (!key.empty()) {
				outMap[key] = tmpData; // 키와 값(데이터의 포인터)의 쌍을 맵에 저장
			}
		}

		file.close();
	}
};

