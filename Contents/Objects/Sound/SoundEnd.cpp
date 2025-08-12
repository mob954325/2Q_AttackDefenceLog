#include "SoundEnd.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"

void SoundEnd::OnUpdate()
{

}

void SoundEnd::OnCreate()
{
	EndSceneFModComponent = owner->AddComponent<FModComponent>();
	EndSceneFModComponent->AddSound(componentList);
	//GameObject* obj = new GameObject();
	//obj->AddComponent<FModComponent>();
	//obj->SetName("EndSound");
	//Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	//EndSoundObj = obj;
}

void SoundEnd::OnStart()
{

}

void SoundEnd::OnDestroy()
{

}

//GameObject* SoundEnd::GetEndObject()
//{
//	if (EndSoundObj) return nullptr;
//	return EndSoundObj;
//}

std::vector<SoundInfo>* SoundEnd::GetVector()
{
	return &componentList;
}

void SoundEnd::SetKeyHandle(std::wstring Key)
{
	KeyHandle = Key;
}

void SoundEnd::PlaySound()
{
	//auto it = EndSoundObj->GetComponent<FModComponent>();
	//it->PlaySound(KeyHandle);
	EndSceneFModComponent->PlaySound(KeyHandle);
}

void SoundEnd::StopSound()
{
	//auto it = EndSoundObj->GetComponent<FModComponent>();
	//it->StopSound();
	EndSceneFModComponent->StopSound();
}

void SoundEnd::PlayAgain()
{
	//auto it = EndSoundObj->GetComponent<FModComponent>();
	//it->PlayAgain();
	EndSceneFModComponent->PlayAgain();
}
