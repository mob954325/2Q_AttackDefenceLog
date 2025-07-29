#pragma once
#include <string>
#include "External/FMod/fmod.hpp"

struct SoundInfo
{
	std::wstring id;
	std::wstring path;
	FMOD_MODE mode;
};
