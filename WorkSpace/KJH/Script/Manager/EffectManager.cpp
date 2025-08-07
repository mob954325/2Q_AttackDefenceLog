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

	for (auto it : particleList)
	{
		it->GetTransform().SetPosition(x, y);
	}
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

void EffectManager::CreateParticleObject(size_t value)
{
	for(size_t i = 0; i < value; i++)
	{
	GameObject* obj = new GameObject();
	obj->AddComponent<ParticleRenderer>();
	obj->SetName(std::string("ParticleObject") + std::to_string(i));
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	particleList.push_back(obj);
	}
}

void EffectManager::SetOffEffect()
{
	for (auto it : effectList)
	{
		it->GetComponent<EffectObject>()->SetEffectValue(0, 0, 0, false);
	}
}

void EffectManager::SetLayer(int index , int value)
{
	effectList[index]->GetComponent<EffectObject>()->SetLayer(value);
}

ParticleRenderer* EffectManager::GetParticleComponent(size_t index)
{
	return particleList[index]->GetComponent<ParticleRenderer>();
}


