#pragma once
#include "Utils/Singleton.h"
#include <unordered_map>
#include "External/FMod/fmod.hpp"
#include "External/FMod/fmod_errors.h"
#include <string>
#include <iostream>
#include "Datas/SoundDatas.h"

/*
FMOD_RESULT playSound(
	FMOD::Sound *sound,         // [1] 재생할 사운드 객체
	FMOD::ChannelGroup *group,  // [2] 속할 채널 그룹 (nullptr이면 기본 그룹), 모두음소거 같은 기능을 넣을때 한개의 그룹에 묶으면됨
	bool paused,                // [3] 일시정지 상태로 시작할지 여부
	FMOD::Channel **channel     // [4] 사운드를 제어할 수 있는 채널 포인터 (출력용)
);

AudioSystem에 모든 bgm을 한번에 등록가능
등록할때는 struct 객체를 만들어서 그 객체를 등록 ( Datas에서 SoundDatas사용)
모든 사운드는 muteGroup으로 등록하기때문에 Setvolume 함수를 통해 전체 사운드 크기 조절 가능
*/


class AudioSystem : public Singleton<AudioSystem>
{
public:
	
	void Initialize();
	void Register(const std::vector<SoundInfo>& sounds);
	void PlaySound(const std::wstring& id);
	void UnRegister();

	void Setvolume(float state);

	static void CheckError(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			std::cerr << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
			exit(-1);
		}
	}

private:
	FMOD::System* fmodSystem = nullptr;
	FMOD::Channel* channel = nullptr;
	std::unordered_map<std::wstring, FMOD::Sound*> sounds;
	FMOD::ChannelGroup* muteGroup;

};

