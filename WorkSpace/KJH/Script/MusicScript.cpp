#include "MusicScript.h"
#include "Components/Base/GameObject.h"
#include "Components/Fmod/FModComponent.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/UI/Slider.h"


void MusicScript::MusicScript::OnUpdate()
{
	CheckInput();
}

void MusicScript::MusicScript::OnCreate()
{
	input = owner->AddComponent<InputSystem>();
	owner->AddComponent<FModComponent>();

	owner->AddComponent<Slider>();
	owner->GetTransform().SetPosition(-100.0f, -100.0f);

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
	if (input->IsKeyDown('W'))
	{
		owner->GetComponent<Slider>()->ChangeGauge(-1);
		owner->GetComponent<Slider>()->ChangeButtonPosition(-1);
		std::cout << "w ÀÔ·ÂµÊ" << std::endl;
	}
	if (input->IsKeyDown('S'))
	{
		owner->GetComponent<Slider>()->ChangeGauge(1);
		owner->GetComponent<Slider>()->ChangeButtonPosition(1);
		std::cout << "s ÀÔ·ÂµÊ" << std::endl;
	}

	//if (input->IsKeyPressed('A'))
	//{
	//	owner->GetComponent<FModComponent>()->PlaySound(L"Attack02");
	//	std::cout << "a ÀÔ·ÂµÊ" << std::endl;
	//}
	//if (input->IsKeyPressed('S'))
	//{
	//	owner->GetComponent<FModComponent>()->PlaySound(L"Attack03");
	//	std::cout << "s ÀÔ·ÂµÊ" << std::endl;
	//}
	//if (input->IsKeyPressed('D'))
	//{
	//	owner->GetComponent<FModComponent>()->PlaySound(L"Bgm01");
	//	std::cout << "d ÀÔ·ÂµÊ" << std::endl;
	//}
	//if (input->IsKeyPressed('P'))
	//{
	//	owner->GetComponent<FModComponent>()->PlaySound(L"Bgm02");
	//	std::cout << "p ÀÔ·ÂµÊ" << std::endl;
	//}
	//if (input->IsKeyPressed('N')) AudioSystem::GetInstance().PauseSound();
	//if (input->IsKeyPressed('M')) AudioSystem::GetInstance().AgainstSound();

}
