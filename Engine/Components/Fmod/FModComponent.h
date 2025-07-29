#pragma once
#include "Components/Base/Component.h"
#include "External/FMod/fmod.hpp"
#include "External/FMod/fmod_errors.h"
#include <iostream>
#include <unordered_map>


/*
설명

생성시
반복 재생 효과음	FMOD_DEFAULT | FMOD_LOOP_NORMAL
루프 없는 효과음	FMOD_DEFAULT | FMOD_LOOP_OFF (또는 그냥 FMOD_DEFAULT)
루프 재생 BGM		FMOD_CREATESTREAM | FMOD_LOOP_NORMAL

*/

class FModComponent : public Component
{
public:

	/*void OnCreate() override;*/
	void OnStart() override;
	void OnDestroy() override;
	void PlaySound(const std::wstring& id);


private:
	std::unordered_map<std::wstring, std::wstring> soundsID;
};