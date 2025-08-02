#include "TestCircleCollider.h"
#include "Components/Base/GameObject.h"

void TestCircleCollider::OnCreate()
{
	slider = owner->AddComponent<Slider>();
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

	bitmap = owner->AddComponent<BitmapRenderer>();
	bitmap->CreateBitmapResource(L"../../Resource/Particles/circle_outer.png");
	owner->GetTransform().SetOffset(-94.5f, 94.5f);

	//slider
	owner->GetComponent<Slider>()->ButtonShow(false);
	owner->GetComponent<Slider>()->SetGaugeBackgroundImage(L"../../Resource/UI/TestGauge/hp_ui_01.png");
	owner->GetComponent<Slider>()->SetGaugeBarImage(L"../../Resource/UI/TestGauge/hp_ui_02.png");
}

void TestCircleCollider::OnFixedUpdate()
{
}

void TestCircleCollider::OnUpdate()
{
	// std::cout << "timer : " << timer << std::endl;
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
