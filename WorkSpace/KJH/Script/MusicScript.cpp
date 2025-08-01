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
	
	
	/*owner->GetTransform().SetPosition(-100.0f, -100.0f);*/
	owner->GetTransform().SetUnityCoords(false);
	

}

void MusicScript::MusicScript::OnStart()
{
	owner->GetComponent<FModComponent>()->AddSound(componentList);
	owner->GetComponent<Slider>()->ButtonShow(false);
	owner->GetComponent<Slider>()->SetGaugeBackgroundImage(L"../../Resource/UI/TestGauge/hp_ui_01.png");
	owner->GetComponent<Slider>()->SetGaugeBarImage(L"../../Resource/UI/TestGauge/hp_ui_02.png");
	//owner->GetComponent<Slider>()->SetGaugeBackgroundImage(L"../../Resource/UI/TestGauge/hp_ui_01.png");
	//owner->GetComponent<Slider>()->SetGaugeBarImage(L"../../Resource/UI/TestGauge/hp_ui_01.png");
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
		std::cout << "w 입력됨" << std::endl;
	}
	if (input->IsKeyDown('S'))
	{
		owner->GetComponent<Slider>()->ChangeGauge(1);
		owner->GetComponent<Slider>()->ChangeButtonPosition(1);
		std::cout << "s 입력됨" << std::endl;
	}

	//if (input->IsKeyPressed('A'))
	//{
	//	owner->GetComponent<FModComponent>()->PlaySound(L"Attack02");
	//	std::cout << "a 입력됨" << std::endl;
	//}
	//if (input->IsKeyPressed('S'))
	//{
	//	owner->GetComponent<FModComponent>()->PlaySound(L"Attack03");
	//	std::cout << "s 입력됨" << std::endl;
	//}
	//if (input->IsKeyPressed('D'))
	//{
	//	owner->GetComponent<FModComponent>()->PlaySound(L"Bgm01");
	//	std::cout << "d 입력됨" << std::endl;
	//}
	//if (input->IsKeyPressed('P'))
	//{
	//	owner->GetComponent<FModComponent>()->PlaySound(L"Bgm02");
	//	std::cout << "p 입력됨" << std::endl;
	//}
	//if (input->IsKeyPressed('N')) AudioSystem::GetInstance().PauseSound();
	//if (input->IsKeyPressed('M')) AudioSystem::GetInstance().AgainstSound();

}
