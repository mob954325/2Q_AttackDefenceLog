#include "LogicTestApplication.h"
#include "Utils/Singleton.h"
#include "Scene/SceneManager.h"
#include "../GameLogicTestScene/GameLogicTestScene.h"

void LogicTestApplication::LogicTestApplication::Initialize()
{
	// 1. SceneManager에 Scene 추가하기
	GameLogicTestScene = new GameLogicTestScene();	// MainMenu 씬 객체 생성
	Singleton<SceneManager>::GetInstance().AddScene(GameLogicTestScene); // 씬 추가
	Singleton<SceneManager>::GetInstance().Init();	// SceneManager 초기화 -> currentScene 초기화 및 RenderSystem의 RenderLayer 초기화
}

void LogicTestApplication::LogicTestApplication::Render()
{
	__super::Render();
}

void LogicTestApplication::LogicTestApplication::Uninitialize()
{
	__super::Uninitialize();
}

void LogicTestApplication::LogicTestApplication::Update()
{
	__super::Update();
}