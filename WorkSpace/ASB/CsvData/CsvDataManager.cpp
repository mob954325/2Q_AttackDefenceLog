#include "CsvDataManager.h"

template<typename T, typename U>
U CsvDataManager<T,U>::SetCSV(const std::string& filePath, int skipLine) {
	std::wifstream file(filePath); // 파일 스트림 생성

	U tmpMap; // 임시 맵 생성
	if (!file.is_open()) {  // 파일 열기 실패 시 에러 메시지 출력
		//std::cout << "파일을 열 수 없습니다: " << file << std::endl;
	}


	std::wstring line;	 // 현재 줄을 저장할 변수
	int countLine = 1;	 // 시작 라인 번호 (1부터 시작)


	while (std::getline(file, line)) {
		T* tmpData = new T(); // 데이터 클래스의 객체 생성
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

		// 데이터 클래스 객체에 데이터를 넣음
		// T는 BaseData를 상속받는 클래스의 객체로, SetData 함수가 정의되어 있어야 함
		tmpData->SetData(row);


		// 예외처리
		// key가 비어있으면 저장하지 않음 (보호 로직)
		if (!key.empty()) {
			tmpMap[key] = tmpData; // 키와 값(데이터의 포인터)의 쌍을 맵에 저장
		}
	}

	file.close();
	return tmpMap; // 임시 맵 반환, 반환에서 = 통해서 값 복사
}


// 콘솔용
// 전체를 콘솔창에 띄우는 함수, 키와 값의 쌍을 출력하는 함수,
template<typename T, typename U>
void CsvDataManager<T, U>::PrintMap() {
	for (auto it = DataMap.begin(); it != DataMap.end(); ++it) {

		it->second->PrintMap(); // BaseData 클래스의 PrintMap 함수 호출
	}
}