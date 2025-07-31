#include "DummyCircleCollider.h"
#include "Components/Base/GameObject.h"
#include "Platform/Input.h"

#include "TestCircleCollider.h"

void DummyCircleCollider::OnCreate()
{
	owner->GetTransform().SetUnityCoords(true);

	circle = owner->AddComponent<CircleCollider>();

	input = owner->AddComponent<InputSystem>();

	particle = owner->AddComponent<ParticleRenderer>();

	owner->GetTransform().SetRotation(180);
}

void DummyCircleCollider::OnStart()
{
	target = owner->GetQuery()->FindByName("Test Cirlce");

	circle->SetRadius(20.0f);

	particle->SetBitmap(L"../../Resource/Particles/spark_1.png");
	particle->SetLoop(true);
	particle->SetMinSpeed(0.5f);
	particle->SetMaxSpeed(2.0f);
	particle->SetDuration(0.8f);
	particle->SetFadeOutTime(0.7f);
	particle->SetAmount(20);
	particle->SetAnimPlayer(L"../../Resource/Particles/Test/FireEffectSheet.png",
		L"../../Resource/Json/Test_Paticles/FireEffectSheet.json",
		L"../../Resource/Json/Test_Paticles/Fire_Boom_anim.json");
	particle->SetShowType(ParticleShowType::Single);
	particle->SetGravity(true);
	particle->SetSeeDirection(true);
}

void DummyCircleCollider::OnFixedUpdate()
{
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
}

void DummyCircleCollider::OnDestroy()
{
}

void DummyCircleCollider::OnColliderEnter(GameObject* collider)
{
	// std::cout << ">>> Dummy 충돌시작 >>>" << std::endl;
	if (*collider == *target)
	{
		std::cout << "찾음" << std::endl;
	}
	else
	{
		std::cout << "target 오브젝트가 아님" << std::endl;
	}
}

void DummyCircleCollider::OnColliderStay(GameObject* collider)
{
	std::cout << ">>> Dummy 충돌 중 >>>" << " [ " << collider->GetName() << " ] " << std::endl;
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