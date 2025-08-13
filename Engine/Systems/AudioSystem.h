#pragma once
#include "Utils/Singleton.h"
#include <unordered_map>
#include "External/FMod/fmod.hpp"
#include "External/FMod/fmod_errors.h"
#include <string>
#include <iostream>
#include "Datas/SoundDatas.h"
#include <Windows.h>
#include <assert.h>

// $(SolutionDir)Engine\External\FMOD\api\core\lib\x64
// "../../Engine/External/FMOD/api/core/lib/x64/fmod_vc.lib"
#pragma comment(lib, "../Engine/External/Fmod/fmod_vc.lib")

/* 25.07.28 | 작성자 : 김정현
FMOD_RESULT playSound(
	FMOD::Sound *sound,         // [1] 재생할 사운드 객체
	FMOD::ChannelGroup *group,  // [2] 속할 채널 그룹 (nullptr이면 기본 그룹), 모두음소거 같은 기능을 넣을때 한개의 그룹에 묶으면됨
	bool paused,                // [3] 일시정지 상태로 시작할지 여부
	FMOD::Channel **channel     // [4] 사운드를 제어할 수 있는 채널 포인터 (출력용)
);

AudioSystem에 모든 bgm을 한번에 등록가능
등록할때는 struct 객체를 만들어서 그 객체를 등록 ( Datas에서 SoundDatas사용)
모든 사운드는 muteGroup으로 등록하기때문에 Setvolume 함수를 통해 전체 사운드 크기 조절 가능


채널 관리가 필요할때
동일 사운드 중복 재생을 안할때 -> (isPlaying 확인 후 재생중이면 stop 실행)
동일 사운드 여러 번 재생 허용할때 -> (unique key , static int 변수를 이용해 특별한 key 설정)
사운드를 그룹별로 관리할때 -> 벡터안에 벡터, channelGroup 사용 , std::unordered_map<std::wstring, std::vector<FMOD::Channel*>> channels; 사용

모든 사운드 멈출때는 PauseSound() ,  재시작할때는 AgainstSound() 호출
Scene넘어갈때 chanel 다 리셋용도로 ReSetChannel() 호출

Fmod 초기화시 채널 갯수를 Init에 전달하여 채널 수를 정할 수 있음
*/


class AudioSystem : public Singleton<AudioSystem>
{
public:
	
	void Initialize(int num);
	void Register(const std::vector<SoundResource>& sounds);
	void PlaySound2(const std::wstring& id);
	void UnRegister();

	void UpdateSFXChannels();



	void ReSetChannel();

	//채널 개별 사운드 조절은 함수 추가하면됨


	static void CheckError(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			std::cerr << "FMOD Error: " << FMOD_ErrorString(result) << std::endl;
			assert(result == FMOD_OK && "FMOD init failed");
				exit(-1);
		}
	}

	bool FileExists(const std::wstring& path);



	//전체 사운드 제어
	void PauseSound();

	void AgainstSound();

	void Setvolume(float state);

	void Getvolume(float& num);

	//채널 갯수체크
	bool IsSFXChannelFull(int maxCount);

	// SFX 채널 초기화 (비우기)
	void ClearSFXChannels();

	void Update();

private:
	struct SoundData {
		FMOD::Sound* sound;
		bool isLoop;
	};

	FMOD::System* fmodSystem = nullptr;
	FMOD::Channel* channel = nullptr;
	/*std::unordered_map<std::wstring, FMOD::Sound*> sounds;*/
	std::unordered_map<std::wstring, SoundData> sounds;
	std::unordered_map<std::wstring, FMOD::Channel*> Channels;
	
	FMOD::ChannelGroup* bgmGroup = nullptr;
	FMOD::ChannelGroup* sfxGroup = nullptr;
	FMOD::ChannelGroup* masterGroup = nullptr;

	std::vector<FMOD::Channel*> activeSFXChannels;

	/*FMOD::ChannelGroup* muteGroup;*/

};

