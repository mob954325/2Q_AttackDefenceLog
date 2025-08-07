#pragma once
#include <string>
#include "BaseData.h"


/*25.07.29 - 안성빈
	역할 : AllNodePattenClass 클래스는 노드 패턴 데이터를 저장하는 클래스
	맴버 : ID와 노드 숫자를 저장하는 벡터
	int는 null을 저장할 수 없음으로 0으로 대신함!
*/

class AllNodePattenClass : public BaseData 
{
public:
	AllNodePattenClass() {};
	~AllNodePattenClass() {};
	std::string Node_pattern_ID;  // 노드 패턴의 ID를 저장
	std::vector<int> Node_Number; // 노드 패턴을 저장하는 벡터, 최대 9개 노드가 들어갈 수 있음



	void SetData(std::vector<std::wstring> tmp) override; // 데이터 설정 함수
	void PrintMap() override; //콘솔창에 데이터 출력 

};

