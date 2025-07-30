#include "TestColliderApp.h"
#include "Utils/Singleton.h"
#include "Scene/SceneManager.h"
#include "../Scenes/CircleColliderScene.h"

void TestCollider::TestColliderApp::Initialize()
{
	__super::Initialize();

	testColliderScene = new CircleColliderScene();
	Singleton<SceneManager>::GetInstance().AddScene(testColliderScene);
	Singleton<SceneManager>::GetInstance().Init();
}

void TestCollider::TestColliderApp::Uninitialize()
{
	__super::Uninitialize();
}