#include "EffectManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include <iostream>

void EffectManager::OnUpdate()
{

}

void EffectManager::OnCreate()
{

}

void EffectManager::OnStart()
{

}

void EffectManager::OnDestroy()
{

}


void EffectManager::SetEffectPosition(float x, float y)
{
	for (auto it : effectList)
	{
		it->GetTransform().SetPosition(x, y);
	}
	particleObj->GetTransform().SetPosition(x, y);
}

void EffectManager::SetEffectImage(size_t value, std::wstring path)
{
	GameObject* tempobj = effectList[value];
	EffectObject* tempeffect = tempobj->GetComponent<EffectObject>();
	tempeffect->SetImage(path);
}

void EffectManager::SetEffectValue(size_t value, float width, float height, float capacityvalue, bool checkend)
{
	GameObject* tempobj = effectList[value];
	EffectObject* tempeffect = tempobj->GetComponent<EffectObject>();
	tempeffect->SetEffectValue(width, height, capacityvalue, checkend);
}

void EffectManager::CreateEffectObject(size_t value)
{
	for (size_t i = 0; i < value; i++)
	{
		GameObject* obj = new GameObject();
		obj->AddComponent<EffectObject>();
		obj->SetName(std::string("Effect")+ std::to_string(i));
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		effectList.push_back(obj);
	}
}

void EffectManager::CreateParticleObject()
{
	if (particleObj != nullptr) return;
	GameObject* obj = new GameObject();
	obj->AddComponent<ParticleRenderer>();
	obj->SetName("ParticleObject");
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	particleObj = obj;
}

void EffectManager::SetOffEffect()
{
	for (auto it : effectList)
	{
		it->GetComponent<EffectObject>()->SetEffectValue(0, 0, 0, false);
	}
}

ParticleRenderer* EffectManager::GetParticleComponent()
{
	return particleObj->GetComponent<ParticleRenderer>();
}


