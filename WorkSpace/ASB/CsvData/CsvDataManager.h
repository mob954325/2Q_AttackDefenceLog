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
	역할 : CsvDataManager 클래스는 CSV 파일을 읽어와서 데이터를 저장하는 클래스
		  CSV 파일의 첫 번째 셀을 키로 사용하고, 데이터 클래스의 포인터를 값으로 맵에 저장함

	주의 : baseData에 있는 벡터를 자료구조로 저장하는 함수(SetData)를 호출함으로 해당 클래스를 사용시 baseData를 상속받는것이 좋음

*/

//싱글톤으로 적기
//       데이터,     맵
template<typename T, typename U>
class CsvDataManager {
public:
	CsvDataManager() {};
	~CsvDataManager() {};


	// map의 키 : 첫 번째 셀의 값(ID), 
	//		 값 : 해당 행의 데이터를 저장하는 클래스의 포인터
	std::unordered_map<std::wstring, T*> DataMap; 

	// 매개변수  : CSV 파일의 경로, 파일 내부 스킵할 라인의 수
	// CSV 파일을 읽어와서 std::unordered_map에 저장하는 함수
	U SetCSV(const std::string& filePath, int skipLine);

	// 콘솔용
	// 전체를 콘솔창에 띄우는 함수, 키와 값의 쌍을 출력하는 함수
	void PrintMap();
};

