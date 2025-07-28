#pragma once
#include "pch.h"
#include "Utils/Singleton.h"

/// <summary>
/// 각종 경로 저장용 싱글톤
/// </summary>
class AppPaths : public Singleton<AppPaths>
{
private:
	std::wstring ModulePath{};
	std::wstring WorkingPath{};

	AppPaths() = default;
	~AppPaths() = default;

public:
	friend class Singleton<AppPaths>;

	void InitPaths(); // Application::Initialize에서 초기화
	const std::wstring GetModulePath() { return ModulePath; }
	const std::wstring GetWorkingPath() { return WorkingPath; }
};