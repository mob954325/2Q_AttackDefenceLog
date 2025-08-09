#include "AudioSystem.h"

#include "Utils/StringConvert.h"
#include "Application/AppPaths.h"

bool AudioSystem::FileExists(const std::wstring& path)
{
	DWORD attrib = GetFileAttributesW(path.c_str());
	return (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY));
}


void AudioSystem::Initialize(int num)
{
	CheckError(FMOD::System_Create(&fmodSystem));
	CheckError(fmodSystem->init(num, FMOD_INIT_NORMAL, nullptr));

	fmodSystem->createChannelGroup("MuteGroup", &muteGroup);
}

void AudioSystem::Register(const std::vector<SoundResource>& soundlist)
{
	//디버깅용 코드
	//if (!FileExists(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/sounds/공격/공격_3.mp3")) {
	//	std::cout << "[오류] 파일이 존재하지 않음!" << std::endl;
	//}
	//else { std::cout << "정상적으로 로딩!" << std::endl; }
	//std::cout << "FileExists 검사 끝\n";
	for (const auto& it : soundlist)
	{
		if (sounds.count(it.id)) continue;

		FMOD::Sound* sound = nullptr;
		fmodSystem->createSound(StringConvert::WStringToUTF8(it.path).c_str(), it.mode, nullptr, &sound);
		sounds[it.id] = sound;
	}
}


void AudioSystem::PlaySound2(const std::wstring& id)
{
	CheckError(fmodSystem->playSound(sounds[id], muteGroup, false, &channel));
}


void AudioSystem::UnRegister()
{
	for (auto& it : sounds) {
		it.second->release();
		it.second = nullptr;
	}
	//Fmod는 release로 해제해야함 , delete 사용시 Fmod 내부 리소스 손상 위험존재
	sounds.clear();
}

void AudioSystem::PauseSound()
{
	std::cout << "멈춤 호출" << std::endl;
	muteGroup->setPaused(true);
}

void AudioSystem::AgainstSound()
{
	std::cout << "재시작 호출" << std::endl;
	muteGroup->setPaused(false);
}

void AudioSystem::ReSetChannel()
{
	std::cout << "채널삭제 호출" << std::endl;
	muteGroup->stop();
}

void AudioSystem::Setvolume(float state)
{
	muteGroup->setVolume(state);
}
