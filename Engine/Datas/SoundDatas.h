#pragma once
#include <string>
#include "External/FMod/fmod.hpp"

struct SoundResource
{
	std::wstring id;
	std::wstring path;
	FMOD_MODE mode;
};

struct SoundInfo
{
	std::wstring name;
	std::wstring id;
};
