#include "HSKApp.h"
#include "Utils/Singleton.h"
#include "Scene/SceneManager.h"
#include "HSKScene.h"

using namespace HSK;

void HSKApp::Initialize()
{
	testScene = new HSKScene();
	Singleton<SceneManager>::GetInstance().AddScene(testScene);
	Singleton<SceneManager>::GetInstance().Init();

	__super::Initialize();
}

void HSKApp::Uninitialize()
{
	__super::Uninitialize();
}