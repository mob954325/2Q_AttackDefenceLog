#include "TestCircleCollider.h"
#include "Components/Base/GameObject.h"

void TestCircleCollider::OnCreate()
{
	
}

void TestCircleCollider::OnStart()
{
	// info text
	infoText = owner->AddComponent<TextRenderer>();
	infoText->SetViewportPosition(0.5f, 0.5f);

	infoText->SetText(L"- 콜라이더 테스트 씬 - ");
	infoText->SetWorldObject(true);

	// circle
	circle = owner->AddComponent<CircleCollider>();
	circle->SetRadius(10.0f);
}

void TestCircleCollider::OnFixedUpdate()
{
}

void TestCircleCollider::OnUpdate()
{
}

void TestCircleCollider::OnDestroy()
{
}

void TestCircleCollider::OnColliderEnter(GameObject* collider)
{
	// std::cout << "--- Test Circle 충돌시작 ---"<< std::endl;
}

void TestCircleCollider::OnColliderStay(GameObject* collider)
{
	// std::cout << "--- Test Circle 충돌 중 ---"<< std::endl;
}

void TestCircleCollider::OnColliderExit(GameObject* collider)
{
	// std::cout << "--- Test Circle 충돌 종료---"<< std::endl;
}
