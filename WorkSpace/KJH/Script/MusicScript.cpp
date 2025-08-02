#include "MusicScript.h"
#include "Components/Base/GameObject.h"
#include "Components/Fmod/FModComponent.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/UI/Slider.h"
#include "Components/Camera/CameraManager.h"
#include "Math/Vector2.h" 


void MusicScript::MusicScript::OnUpdate()
{
	CheckInput();
}

void MusicScript::MusicScript::OnCreate()
{
	input = owner->AddComponent<InputSystem>();
	owner->AddComponent<FModComponent>();

	owner->AddComponent<Slider>();

	Came = owner->AddComponent<Camera>();

	Singleton<CameraManager>::GetInstance().Register(new CameraInfo(Came->GetPriority(), Came));
	
	
	/*owner->GetTransform().SetPosition(-100.0f, -100.0f);*/
	owner->GetTransform().SetUnityCoords(false);


	TestImage3 = owner->AddComponent<BitmapRenderer>();
	TestImage3->CreateBitmapResource(L"../../Resource/UI/TestImage/test3.png");

	/*owner->GetTransform().SetOffset(-TestImage3->GetResource()->GetBitmap()->GetSize().width / 2, TestImage->GetResource()->GetBitmap()->GetSize().height / 2);*/
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

	Vector2 Vector1{};
	/*A = 0.0f;*/

	//if (input->IsKeyPressed(VK_LEFT))
	//{
	//	/*Vector1.x -= 1.0f;*/
	//	A -= 15.0f;
	//}
	//if (input->IsKeyPressed(VK_RIGHT))
	//{
	//	/*Vector1.x += 1.0f;*/
	//	A += 15.0f;
	//}

	if (input->IsKeyDown(VK_LEFT))
	{
		/*Vector1.x -= 1.0f;*/
			A -= 45.0f;
	}
	if (input->IsKeyDown(VK_RIGHT))
	{
		/*Vector1.x += 1.0f;*/
			A += 45.0f; 
	}
	if (input->IsKeyDown(VK_UP))
	{
		Vector1.y += 1.0f;
	}
	if (input->IsKeyDown(VK_DOWN))
	{
		Vector1.y -= 1.0f;
	}

	

	owner->GetTransform().SetRotation(A);
	owner->GetTransform().Translate(Vector1);
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
