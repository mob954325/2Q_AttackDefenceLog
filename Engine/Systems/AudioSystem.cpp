#include "AudioSystem.h"

#include "Utils/StringConvert.h"
#include "Application/AppPaths.h"

bool AudioSystem::FileExists(const std::wstring& path)
{
	DWORD attrib = GetFileAttributesW(path.c_str());
	return (attrib != INVALID_FILE_ATTRIBUTES && !(attrib & FILE_ATTRIBUTE_DIRECTORY));
}


void AudioSystem::Setvolume(float volume)
{
	if (masterGroup)
		masterGroup->setVolume(volume);
}

void AudioSystem::Getvolume(float& volume)
{
	if (masterGroup)
		masterGroup->getVolume(&volume);
	else
		volume = 0.0f;
}

// 채널풀 체크함수
bool AudioSystem::IsSFXChannelFull(int maxCount)
{
	if (!sfxGroup) return false;

	int numChannels = 0;
	sfxGroup->getNumChannels(&numChannels);

	return numChannels >= maxCount;
}

//채널 초기화 함수
void AudioSystem::ClearSFXChannels()
{
	if (!sfxGroup) return;

	int numChannels = 0;
	sfxGroup->getNumChannels(&numChannels);

	for (int i = numChannels - 1; i >= 0; --i)  // 뒤에서부터 제거
	{
		FMOD::Channel* channel = nullptr;
		sfxGroup->getChannel(i, &channel);
		if (channel)
		{
			bool isPlaying = false;
			channel->isPlaying(&isPlaying);

			// 재생 중인 SFX만 정리, 반복 BGM은 건드리지 않음
			if (isPlaying)
				channel->stop();
		}
	}
}

void AudioSystem::PauseSound()
{
	if (masterGroup)
		masterGroup->setPaused(true);
}

void AudioSystem::AgainstSound()
{
	if (masterGroup)
		masterGroup->setPaused(false);
}


void AudioSystem::Initialize(int num)
{
	CheckError(FMOD::System_Create(&fmodSystem));
	CheckError(fmodSystem->init(num, FMOD_INIT_NORMAL, nullptr));

	// 마스터 그룹 가져오기
	fmodSystem->getMasterChannelGroup(&masterGroup);

	// BGM/SFX 그룹 생성
	fmodSystem->createChannelGroup("BGM_Group", &bgmGroup);
	fmodSystem->createChannelGroup("SFX_Group", &sfxGroup);

	// 마스터 그룹에 붙이기
	masterGroup->addGroup(bgmGroup);
	masterGroup->addGroup(sfxGroup);
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
		//25.08.12 | 경로 절대값으로 변경에 따라 코드수정
		fmodSystem->createSound((StringConvert::WStringToUTF8(Singleton<AppPaths>::GetInstance().GetWorkingPath() + it.path)).c_str(), it.mode, nullptr, &sound);
		
		bool isLoop = (it.mode & FMOD_LOOP_NORMAL) || (it.mode & FMOD_LOOP_BIDI);
		sounds[it.id] = { sound, isLoop };

		/*sounds[it.id] = sound;*/
	}
}


void AudioSystem::PlaySound2(const std::wstring& id)
{
	if (!sounds.count(id)) return;

	CheckError(fmodSystem->playSound(sounds[id].sound, masterGroup, false, &channel));

	// loop 아닌 사운드면 SFX 채널 벡터에 추가
	if (!sounds[id].isLoop && channel) {
		activeSFXChannels.push_back(channel);
	}
}


void AudioSystem::UnRegister()
{
	for (auto& it : sounds) {
		if (it.second.sound) {
			it.second.sound->release();
			it.second.sound = nullptr;
		}
	}
	sounds.clear();
}

void AudioSystem::ReSetChannel()
{
	if (!masterGroup) return;

	int numChannels = 0;
	masterGroup->getNumChannels(&numChannels);

	for (int i = numChannels - 1; i >= 0; --i)
	{
		FMOD::Channel* channel = nullptr;
		masterGroup->getChannel(i, &channel);
		if (channel)
		{
			channel->stop();  // 채널 재생 종료
			channel = nullptr; // 포인터 끊기
		}
	}

	// masterGroup 하위 그룹 처리
	int numSubGroups = 0;
	masterGroup->getNumGroups(&numSubGroups);

	for (int i = numSubGroups - 1; i >= 0; --i)
	{
		FMOD::ChannelGroup* subGroup = nullptr;
		masterGroup->getGroup(i, &subGroup);
		if (subGroup)
		{
			int subNumChannels = 0;
			subGroup->getNumChannels(&subNumChannels);
			for (int j = subNumChannels - 1; j >= 0; --j)
			{
				FMOD::Channel* subChannel = nullptr;
				subGroup->getChannel(j, &subChannel);
				if (subChannel)
					subChannel->stop();
			}
		}
	}

	fmodSystem->update(); // 상태 갱신
}
