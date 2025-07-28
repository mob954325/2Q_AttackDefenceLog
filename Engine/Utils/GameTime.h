#pragma once
#include <iostream>
#include <windows.h>
#include "Utils/Singleton.h"

/// <summary>
/// 게임 시간관련 클래스
/// </summary>
class GameTime : public Singleton<GameTime>
{
public:
	friend class Singleton<GameTime>;

	void InitTime();
	void UpdateTime();
	float GetDeltaTime();
	float GetFixedDeltaTime();
	float GetElapsedTime();

private:
	GameTime() = default;
	~GameTime() = default;

	LARGE_INTEGER freq = {}, curr = {}, prev = {}, start = {}, end = {};
	float deltaTime{};
	float timeElapsed{};
};
