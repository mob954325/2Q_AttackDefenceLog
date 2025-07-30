#include "SoundApp.h"
#include "Systems/AudioSystem.h"
#include "Components/Logic/InputSystem.h"
#include "Scene/SceneManager.h"
#include "Scene/TestScene.h"

void SoundApp::SoundApp::Initialize()
{
	
	testScene = new TestScene::TestScene();
	Singleton<SceneManager>::GetInstance().AddScene(testScene);
	Singleton<SceneManager>::GetInstance().Init();
	__super::Initialize();
	AudioSystem::GetInstance().Initialize(128);
	AudioSystem::GetInstance().Register(musiclist);
}

void SoundApp::SoundApp::Uninitialize()
{
	AudioSystem::GetInstance().UnRegister();
	__super::Uninitialize();
}
