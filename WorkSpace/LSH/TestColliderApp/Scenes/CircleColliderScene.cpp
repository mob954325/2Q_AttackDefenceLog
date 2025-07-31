#include "CircleColliderScene.h"
#include "TestColliderApp/Scripts/TestCircleCollider.h"
#include "TestColliderApp/Scripts/DummyCircleCollider.h"
#include "TestColliderApp/Scripts/DummyButton.h"
#include "TestColliderApp/Scripts/DummyEffectAnimation.h"

void TestCollider::CircleColliderScene::OnEnterImpl()
{
	// testCircle = new GameObject();
	// testCircle->SetName("Test Cirlce");
	// testCircle->AddComponent<TestCircleCollider>();
	// AddGameObject(testCircle);

	//testCircle2 = new GameObject();
	//testCircle2->SetName("Test Cirlce2");
	//testCircle2->AddComponent<TestCircleCollider>();
	//AddGameObject(testCircle2);
	//testCircle2->GetTransform().SetPosition(100, 100);

	dummyCircle = new GameObject();
	dummyCircle->SetName("Dummy Cirlce");
	dummyCircle->AddComponent<DummyCircleCollider>();
	AddGameObject(dummyCircle);

	dummyButton = new GameObject();
	dummyButton->SetName("Dummy Button");
	dummyButton->AddComponent<DummyButton>();
	AddGameObject(dummyButton);

	dummyEffectAnimation = new GameObject();
	dummyEffectAnimation->SetName("Dummy Effect Animation");
	dummyEffectAnimation->AddComponent<DummyEffectAnimation>();
	AddGameObject(dummyEffectAnimation);
	dummyEffectAnimation->GetTransform().SetPosition(-200, 200);
}

void TestCollider::CircleColliderScene::OnExitImpl()
{
}

void TestCollider::CircleColliderScene::UpdateImpl()
{
}
