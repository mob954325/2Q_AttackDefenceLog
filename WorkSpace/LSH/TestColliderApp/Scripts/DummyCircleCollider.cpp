#include "DummyCircleCollider.h"
#include "Components/Base/GameObject.h"
#include "Platform/Input.h"
#include "TestCircleCollider.h"

#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"

void DummyCircleCollider::OnCreate()
{
	owner->GetTransform().SetUnityCoords(false);
	owner->GetTransform().SetPosition(400,400);

	circle = owner->AddComponent<CircleCollider>();

	input = owner->AddComponent<InputSystem>();

	particle = owner->AddComponent<ParticleRenderer>();

	anime = owner->AddComponent<AnimationRenderer>();
	anime->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Dance\\Dance.png");
	anime->SetSpriteSheet(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Dance\\Dance_sprites.json");
	anime->SetAnimationClip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Dance\\Dance_Dance_anim.json");
	anime->GetAnimationPlayer()->SetLoop(true);
	owner->GetTransform().SetRotation(45);
}

void DummyCircleCollider::OnStart()
{
	target = owner->GetQuery()->FindByName("Test Cirlce");

	circle->SetRadius(20.0f);

	particle->SetBitmap(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Particles\\Test\\Arrow.png");
	particle->SetMinSpeed(0.3f);
	particle->SetMaxSpeed(0.7f);
	particle->SetDuration(0.8f);
	particle->SetFadeOutTime(0.7f);
	particle->SetAmount(25);
	particle->SetAnimPlayer(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Particles\\SparkSheet.png",
		Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Json\\SparkSheet\\SparkSheet_sprites.json",
		Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Json\\SparkSheet\\Red_Spark_anim.json");
	particle->SetShowType(ParticleShowType::RandomSingle);
	particle->SetGravity(false);
	particle->SetSeeDirection(true);
	particle->SetDecreasing(true);
	particle->Reset();
	particle->Play();
}

void DummyCircleCollider::OnFixedUpdate()
{
	rot += 0.1f;
	owner->GetTransform().SetRotation(rot);
}

void DummyCircleCollider::OnUpdate()
{
	HandleInput();

	// owner->GetTransform().SetPosition(-EngineData::SceenWidth / 2 + Input::MouseX, EngineData::SceenHeight / 2 - Input::MouseY);
	// std::cout << owner->GetTransform().GetPosition() << std::endl;

	if (input->IsKeyPressed('Q'))
	{
		particle->Play();
	}
	if (input->IsKeyPressed('W'))
	{
		particle->Pause();
	}
	if (input->IsKeyPressed('E'))
	{
		particle->Reset();
	}
	if (input->IsKeyPressed('R'))
	{
		particle->SetLoop(true);
	}
	if (input->IsKeyPressed('T'))
	{
		particle->SetLoop(false);
	}

	// change Scene -> SliceObjectScene
	if (input->IsKeyPressed('1'))
	{
		Singleton<SceneManager>::GetInstance().LoadScene(1);
	}

	if (input->IsKeyDown('J'))
	{
		owner->GetTransform().Translate({ -1,0 });
	}
	if (input->IsKeyDown('L'))
	{
		owner->GetTransform().Translate({ 1,0 });
	}
	if (input->IsKeyDown('I'))
	{
		owner->GetTransform().Translate({ 0,1 });
	}
	if (input->IsKeyDown('K'))
	{
		owner->GetTransform().Translate({ 0,-1 });
	}
}

void DummyCircleCollider::OnDestroy()
{
}

void DummyCircleCollider::OnColliderEnter(GameObject* collider)
{
	// std::cout << ">>> Dummy 충돌시작 >>>" << std::endl;
	//if (*collider == *target)
	//{
	//	std::cout << "찾음" << std::endl;
	//}
	//else
	//{
	//	std::cout << "target 오브젝트가 아님" << std::endl;
	//}
}

void DummyCircleCollider::OnColliderStay(GameObject* collider)
{
	//std::cout << ">>> Dummy 충돌 중 >>>" << " [ " << collider->GetName() << " ] " << std::endl;
}

void DummyCircleCollider::OnColliderExit(GameObject* collider)
{
	// std::cout << ">>> Dummy 충돌 종료 >>>" << std::endl;
}

void DummyCircleCollider::HandleInput()
{
	// if (input->IsKeyDown('W')) owner->GetTransform().Translate({ 0, 1 });
	// if (input->IsKeyDown('A')) owner->GetTransform().Translate({ -1, 0 });
	// if (input->IsKeyDown('S')) owner->GetTransform().Translate({ 0, -1 });
	// if (input->IsKeyDown('D')) owner->GetTransform().Translate({ 1, 0 });
}