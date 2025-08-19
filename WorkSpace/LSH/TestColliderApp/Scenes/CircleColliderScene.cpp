#include "CircleColliderScene.h"
#include "TestColliderApp/Scripts/TestCircleCollider.h"
#include "TestColliderApp/Scripts/DummyCircleCollider.h"
#include "TestColliderApp/Scripts/DummyButton.h"
#include "TestColliderApp/Scripts/DummyEffectAnimation.h"
#include "TestColliderApp/Scripts/TestVignetteObject.h"
#include "Utils/DebugUtility.h"

void TestCollider::CircleColliderScene::OnEnterImpl()
{
	// GameObject* vignetteObject = new GameObject();
	// vignetteObject->SetName("vignette effect");
	// vignetteObject->AddComponent<TestVignetteObject>();
	// AddGameObject(vignetteObject);

	GameObject* dummyCircle = new GameObject();
	dummyCircle->SetName("DummyCircleCollider");
	dummyCircle->AddComponent<DummyEffectAnimation>();
	AddGameObject(dummyCircle);
}

void TestCollider::CircleColliderScene::OnExitImpl()
{
}

void TestCollider::CircleColliderScene::UpdateImpl()
{
	// DebugUtility::DebugLog("Scene Udpate Log");
}
