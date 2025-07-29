#include "HSKApp.h"
#include "Utils/Singleton.h"
#include "Scene/SceneManager.h"
#include "HSKScene.h"

using namespace HSK;

void HSKApp::Initialize()
{
	__super::Initialize();
	testScene = new HSKScene();
	Singleton<SceneManager>::GetInstance().AddScene(testScene);
	Singleton<SceneManager>::GetInstance().Init();
}

void HSKApp::Uninitialize()
{
	__super::Uninitialize();
}
void HSKApp::Update() {
	__super::Update();
}