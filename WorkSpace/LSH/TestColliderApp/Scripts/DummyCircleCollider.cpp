#include "DummyCircleCollider.h"
#include "Components/Base/GameObject.h"
#include "Platform/Input.h"

#include "TestCircleCollider.h"

void DummyCircleCollider::OnCreate()
{
	owner->GetTransform().SetUnityCoords(true);

	circle = owner->AddComponent<CircleCollider>();
	circle->SetRadius(20.0f);

	input = owner->AddComponent<InputSystem>();

	particle = owner->AddComponent<ParticleRenderer>();
}

void DummyCircleCollider::OnStart()
{
	target = owner->GetQuery()->FindByName("Test Cirlce");
	particle->SetBitmap(L"../../Resource/Mushroom.png");
}

void DummyCircleCollider::OnFixedUpdate()
{
}

void DummyCircleCollider::OnUpdate()
{
	HandleInput();

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