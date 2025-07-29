#include "MusicScript.h"
#include "Components/Base/GameObject.h"
#include "Components/Fmod/FModComponent.h"
#include <iostream>
#include "Systems/AudioSystem.h"


void MusicScript::MusicScript::OnUpdate()
{
	CheckInput();
}

void MusicScript::MusicScript::OnCreate()
{
	input = owner->AddComponent<InputSystem>();
	owner->AddComponent<FModComponent>();
	

}

void MusicScript::MusicScript::OnStart()
{
	owner->GetComponent<FModComponent>()->AddSound(componentList);
}

void MusicScript::MusicScript::OnDestroy()
{
	componentList.clear();
}

void MusicScript::MusicScript::CheckInput()
{
	if (input->IsKeyPressed('W'))
	{
		owner->GetComponent<FModComponent>()->PlaySound(L"Attack01");
		std::cout << "w ÀÔ·ÂµÊ" << std::endl;
	}
	if (input->IsKeyPressed('A'))
	{
		owner->GetComponent<FModComponent>()->PlaySound(L"Attack02");
		std::cout << "a ÀÔ·ÂµÊ" << std::endl;
	}
	if (input->IsKeyPressed('S'))
	{
		owner->GetComponent<FModComponent>()->PlaySound(L"Attack03");
		std::cout << "s ÀÔ·ÂµÊ" << std::endl;
	}
	if (input->IsKeyPressed('D'))
	{
		owner->GetComponent<FModComponent>()->PlaySound(L"Bgm01");
		std::cout << "d ÀÔ·ÂµÊ" << std::endl;
	}
	if (input->IsKeyPressed('P'))
	{
		owner->GetComponent<FModComponent>()->PlaySound(L"Bgm02");
		std::cout << "p ÀÔ·ÂµÊ" << std::endl;
	}
	if (input->IsKeyPressed('N')) AudioSystem::GetInstance().PauseSound();
	if (input->IsKeyPressed('M')) AudioSystem::GetInstance().AgainstSound();

}
