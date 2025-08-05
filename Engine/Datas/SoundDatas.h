#pragma once
#include <string>
#include <vector>
#include "External/FMod/fmod.hpp"

/* 25.08.05 | 작성자 : 김정현
csv로 읽어올 데이터를 struct로 미리구현
그리고 읽어올 데이터가 wstring이 아닐경우 SetData에 멤버변수에 맞게 들어가도록 변환함수 작성이 필요함
if (row.size() < 3) return; 는 컬럼 수가 3개 미만이면 데이터를 무시하고 다음 줄로 넘어간다는 뜻
즉 struct에서 읽을 컬럼 수를 정하고 읽어서 넣도록함 ( 읽을 수의 책임은 struct에 )
FMOD_MODE ParseFmodMode(const std::wstring& str); 는 FMOD 내용을 FMOD로 치환하기 위한 함수
std::wstring StripQuotes(const std::wstring& input); 는 \"\" 같은 불필요한 값을 없애는 함수
*/

FMOD_MODE ParseFmodMode(const std::wstring& str);
std::wstring StripQuotes(const std::wstring& input);

struct SoundResource
{
	std::wstring id;
	std::wstring path;
	FMOD_MODE mode;

	void SetData(const std::vector<std::wstring>& row) {
		if (row.size() < 3) return;
		id = row[0];
		path = StripQuotes(row[1]);
		mode = ParseFmodMode(row[2]);  // 문자열을 열거형으로 파싱
	}
};

struct SoundInfo
{
	std::wstring name;
	std::wstring id;
};