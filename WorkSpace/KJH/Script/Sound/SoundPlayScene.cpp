#include "SoundPlayScene.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"

void SoundPlayScene::OnUpdate()
{

}

void SoundPlayScene::OnCreate()
{
	GameObject* obj = new GameObject();
	obj->AddComponent<FModComponent>();
	obj->SetName("PlaySound");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	PlaySoundObj = obj;
}

void SoundPlayScene::OnStart()
{

}

void SoundPlayScene::OnDestroy()
{

}

GameObject* SoundPlayScene::GetEndObject()
{
	if (PlaySoundObj) return nullptr;
	return PlaySoundObj;
}

std::vector<SoundInfo>* SoundPlayScene::GetVector()
{
	return &componentList;
}

void SoundPlayScene::SetKeyHandle(std::wstring Key)
{
	KeyHandle = Key;
}

void SoundPlayScene::PlaySound()
{
	auto it = PlaySoundObj->GetComponent<FModComponent>();
	it->PlaySound(KeyHandle);
}

void SoundPlayScene::StopSound()
{
	auto it = PlaySoundObj->GetComponent<FModComponent>();
	it->StopSound();
}

void SoundPlayScene::PlayAgain()
{
	auto it = PlaySoundObj->GetComponent<FModComponent>();
	it->PlayAgain();
}
