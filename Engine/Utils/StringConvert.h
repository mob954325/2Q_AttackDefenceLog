#pragma once
#include "pch.h"
#include <locale>
#include <codecvt>

/// <summary>
/// string <-> wstring 변환 클래스
/// </summary>
/// 
/// 25.08.05 | 작성자 : 김정현
/// c++18 이후부터는 convert를 사용할 수 없기 때문에 Windows API 기반 std::string (UTF-8)변환방법 WStringToUTF8, UTF8ToWString 2가지
class StringConvert
{
public:
	static std::wstring StringToWstring(const std::string& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(str);
	}

	static std::string WstringToString(const std::wstring& str)
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		return converter.to_bytes(str);
	}

	static std::string WstringToMultibyte(const std::wstring& wstr) {
		if (wstr.empty()) return {};

		int size = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
		std::string result(size, 0);
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, &result[0], size, nullptr, nullptr);
		return result;
	}

	static std::string WStringToUTF8(const std::wstring& wstr) {
		if (wstr.empty()) return {};

		int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
		std::string strTo(size_needed, 0);
		WideCharToMultiByte(CP_UTF8, 0, wstr.data(), (int)wstr.size(), &strTo[0], size_needed, nullptr, nullptr);
		return strTo;
	}

	static std::wstring UTF8ToWString(const std::string& str) {
		if (str.empty()) return {};

		int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), nullptr, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, str.data(), (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}
};