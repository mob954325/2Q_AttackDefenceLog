#include "TestCircleCollider.h"
#include "Components/Base/GameObject.h"

void TestCircleCollider::OnCreate()
{
	
}

void TestCircleCollider::OnStart()
{
	infoText = owner->AddComponent<TextRenderer>();
	infoText->SetViewportPosition(0.5f, 0.5f);

	infoText->SetText(L"- 콜라이더 테스트 씬 - ");
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
