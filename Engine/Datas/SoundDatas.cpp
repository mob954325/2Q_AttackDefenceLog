#include "Datas/SoundDatas.h"

//파싱함수( wstring 이외의 자료형이 존재할때 구현 필수 )
FMOD_MODE ParseFmodMode(const std::wstring& str) {
	if (str == L"FMOD_DEFAULT | FMOD_LOOP_OFF")
		return FMOD_DEFAULT | FMOD_LOOP_OFF;
	else if (str == L"FMOD_CREATESTREAM | FMOD_LOOP_NORMAL")
		return FMOD_CREATESTREAM | FMOD_LOOP_NORMAL;
	return FMOD_DEFAULT;
}


//\''\''를 제거하는 함수
std::wstring StripQuotes(const std::wstring& input) {
	std::wstring result = input;
	if (result.size() >= 2 && result.front() == L'"' && result.back() == L'"') {
		result = result.substr(1, result.size() - 2);
	}

	size_t pos = 0;
	while ((pos = result.find(L"\"\"", pos)) != std::wstring::npos) {
		result.replace(pos, 2, L"");
		pos += 1;
	}
	return result;
}