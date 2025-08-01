#include "TestCircleCollider.h"
#include "Components/Base/GameObject.h"
#include "Utils/GameTime.h"

void TestCircleCollider::OnCreate()
{
	
}

void TestCircleCollider::OnStart()
{
	// info text
	infoText = owner->AddComponent<TextRenderer>();
	infoText->SetViewportPosition(0.5f, 0.5f);

	// infoText->SetText(L"- 콜라이더 테스트 씬 - ");
	infoText->SetWorldObject(true);

	// circle
	circle = owner->AddComponent<CircleCollider>();
	circle->SetRadius(10.0f);

	bitmap = owner->AddComponent<BitmapRenderer>();
	bitmap->CreateBitmapResource(L"../../Resource/Particles/circle_outer.png");
	owner->GetTransform().SetOffset(-94.5f, 94.5f);
}

void TestCircleCollider::OnFixedUpdate()
{
}

void TestCircleCollider::OnUpdate()
{
	if (timer > maxTimer)
	{
		owner->GetTransform().SetScale(0.0f, 0.0f);
		timer = 0.0f;
	}
	else
	{
		float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();
		float scaleValue = 3.0f;
		timer += delta;
		Vector2 scale = owner->GetTransform().GetScale();
		owner->GetTransform().SetScale(scale.x + delta * scaleValue, scale.y + delta * scaleValue);
	}

	std::cout << "timer : " << timer << std::endl;
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
