#include "FModComponent.h"
#include "Systems/AudioSystem.h"

void FModComponent::OnDestroy()
{
	soundsID.clear();
}

void FModComponent::AddSound(const std::vector<SoundInfo>& list)
{
	for (const auto& it : list)
	{
		if (soundsID.count(it.name)) continue;

		soundsID[it.name] = it.id;
	}
}


void FModComponent::PlaySound(const std::wstring& id)
{
	AudioSystem::GetInstance().PlaySound2(soundsID[id]);
}

void FModComponent::StopSound()
{
	AudioSystem::GetInstance().PauseSound();
}

void FModComponent::PlayAgain()
{
	AudioSystem::GetInstance().AgainstSound();
}
