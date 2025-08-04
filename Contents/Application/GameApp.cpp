#include "GameApp.h"
#include "Scene/SceneManager.h"
#include "Scenes/MenuScene.h"

void GameApp::Initialize()
{
	__super::Initialize();

	// 여기에 씬 추가 및 Init 함수 추가
	menuScene = new MenuScene();
	Singleton<SceneManager>::GetInstance().AddScene(menuScene);



	Singleton<SceneManager>::GetInstance().Init();
}

void GameApp::Uninitialize()
{
	__super::Uninitialize();
}