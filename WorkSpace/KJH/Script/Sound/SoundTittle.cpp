#include "SoundTittle.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"

void SoundTittle::OnUpdate()
{

}

void SoundTittle::OnCreate()
{
	GameObject* obj = new GameObject();
	obj->AddComponent<FModComponent>();
	obj->SetName("TittleSound");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	TittleSoundObj = obj;
}

void SoundTittle::OnStart()
{

}

void SoundTittle::OnDestroy()
{

}

GameObject* SoundTittle::GetEndObject()
{
	if (TittleSoundObj) return nullptr;
	return TittleSoundObj;
}

std::vector<SoundInfo>* SoundTittle::GetVector()
{
	return &componentList;
}

void SoundTittle::SetKeyHandle(std::wstring Key)
{
	KeyHandle = Key;
}

void SoundTittle::PlaySound()
{
	auto it = TittleSoundObj->GetComponent<FModComponent>();
	it->PlaySound(KeyHandle);
}

void SoundTittle::StopSound()
{
	auto it = TittleSoundObj->GetComponent<FModComponent>();
	it->StopSound();
}

void SoundTittle::PlayAgain()
{
	auto it = TittleSoundObj->GetComponent<FModComponent>();
	it->PlayAgain();
}
