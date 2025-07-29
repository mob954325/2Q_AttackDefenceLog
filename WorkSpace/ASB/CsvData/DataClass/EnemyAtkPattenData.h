#pragma once
#include "../BaseData.h"
#include <vector>

/*25.07.29 - 안성빈
 * 역할 :적의 공격 패턴 데이터를 저장하는 클래스
 * 맴버 : 공격 패턴을 저장하는 벡터
 * int는 null을 저장할 수 없음으로 0으로 대신함!


*/

class EnemyAtkPattenData : public BaseData
{


	void SetData(std::vector<std::wstring> tmp)override; // 데이터 설정 함수
	void PrintMap()override; // 맵을 콘솔창에 출력 함수, 상속받는 데이터에서 오버라이드 하여 사용
};

