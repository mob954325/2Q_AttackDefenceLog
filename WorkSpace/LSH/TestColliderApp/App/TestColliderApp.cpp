#include "TestColliderApp.h"
#include "Utils/Singleton.h"
#include "Scene/SceneManager.h"
#include "../Scenes/CircleColliderScene.h"
#include "TestColliderApp/Scenes/SliceObjectScene.h"

void TestCollider::TestColliderApp::Initialize()
{
	__super::Initialize();

	testColliderScene = new CircleColliderScene();
	Singleton<SceneManager>::GetInstance().AddScene(testColliderScene);
	testSliceScene = new SliceObjectScene();
	Singleton<SceneManager>::GetInstance().AddScene(testSliceScene);
	Singleton<SceneManager>::GetInstance().Init();
}

void TestCollider::TestColliderApp::Uninitialize()
{
	__super::Uninitialize();
}