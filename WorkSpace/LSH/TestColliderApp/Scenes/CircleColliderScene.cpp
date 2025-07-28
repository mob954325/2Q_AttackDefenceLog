#include "CircleColliderScene.h"
#include "TestColliderApp/Scripts/TestCircleCollider.h"

void TestCollider::CircleColliderScene::OnEnterImpl()
{
	testCircle = new GameObject();
	testCircle->SetName("Cirlce");
	AddGameObject(testCircle);

	testCircle->AddComponent<TestCircleCollider>();
}

void TestCollider::CircleColliderScene::OnExitImpl()
{
}

void TestCollider::CircleColliderScene::UpdateImpl()
{
}
