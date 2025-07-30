#include "AllNodePattenClass.h"
#include "Utils/StringConvert.h"



//BaseData 클래스의 함수에 오버라이드 하여 사용하는 함수
//해당 자료형의 데이터를 저장하는 함수
void AllNodePattenClass::SetData(std::vector<std::wstring> tmp) {
	Node_pattern_ID = StringConvert::WstringToString(tmp[0].c_str());
	for (int i = 1; i < 10; i++) { //후에 이상한 값들이 들어오는 경우도 있음으로 9개로 제한(하드코딩)

		// tmp[i]가 null인 경우는 0으로 저장
		if (tmp[i] == L"null") {
			Node_Number.push_back(0);
		}

		//null이 아니면 wstring을 int 값으로 저장
		else {
			Node_Number.push_back(std::stoi(tmp[i])); //클래스의 벡터에 위에 저장된 벡터를 숫자로 변환하여 저장
		}
	}
}

void AllNodePattenClass::PrintMap() {
	std::cout << "Node_pattern_ID: " << Node_pattern_ID << " ";
	for (const auto& num : Node_Number) {
		std::cout << num << " ";
	}
	std::cout << std::endl;
}