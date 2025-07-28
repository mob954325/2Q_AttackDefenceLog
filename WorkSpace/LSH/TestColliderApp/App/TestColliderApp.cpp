#include "TestColliderApp.h"
#include "Utils/Singleton.h"
#include "Scene/SceneManager.h"
#include "../Scenes/CircleColliderScene.h"

void TestCollider::TestColliderApp::Initialize()
{
	testColliderScene = new CircleColliderScene();
	Singleton<SceneManager>::GetInstance().AddScene(testColliderScene);
	Singleton<SceneManager>::GetInstance().Init();

	__super::Initialize();
}

void TestCollider::TestColliderApp::Uninitialize()
{
	__super::Uninitialize();
}