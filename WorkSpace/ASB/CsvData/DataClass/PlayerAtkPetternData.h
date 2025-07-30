#pragma once
#include "BaseData.h"

class PlayerAtkPetternData : public BaseData
{
public:
	PlayerAtkPetternData() {};
	~PlayerAtkPetternData() {};

	void SetData(std::vector<std::wstring> tmp)override; // 데이터 설정 함수
	void PrintMap()override; // 맵을 콘솔창에 출력 함수, 상속받는 데이터에서 오버라이드 하여 사용
};

