#pragma once
#include <vector>
#include <string>
/* 2025.07.29 - 안성빈
	BaseData 클래스는 엑셀 파일의 데이터 구조의 기본 클래스

	주의 : 데이터 구조에서 int는 null을 저장할 수 없음으로 0으로 대신함!
*/

class BaseData
{
public :
	BaseData() {};
	virtual ~BaseData() {};

public:
	// 순수 가상 함수 선언
	virtual void SetData(std::vector<std::wstring> tmp)  = 0; // 데이터 설정 함수
	virtual void PrintMap()  = 0; // 맵을 콘솔창에 출력 함수, 상속받는 데이터에서 오버라이드 하여 사용
	
};

