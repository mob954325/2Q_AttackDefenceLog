#pragma once
#include "pch.h"
#include <locale>
#include <codecvt>

/// <summary>
/// string <-> wstring 변환 클래스
/// </summary>
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
};