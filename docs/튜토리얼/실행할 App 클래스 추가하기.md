# 실행할 App추가하기

---

## 설명

Initialize에 사용할 씬을 SceneManager에 추가하고 마지막 줄에 Init()함수를 호출하면 됩니다.

씬의 인덱스는 등록한 순서대로 저장됩니다.

## 예시코드

### .h

```cpp
#pragma once
#include "Application/Application.h"

namespace TestPlatformerGame
{
	class TestPlatformerGameApp : Application
	{
	public:
		void Initialize() override;
		void Render() override;
		void Uninitialize() override;
		void Update() override;
	};	
}
```

### .cpp

```cpp
#include "TestPlatformerGameApp.h"

#include "Utils/Singleton.h"
#include "Scene/SceneManager.h"
#include "Test_Platformer/Scene/MainMenu.h"

void TestPlatformerGame::TestPlatformerGameApp::Initialize()
{
	// 1. SceneManager에 Scene 추가하기
	menuScene = new MainMenu();	// MainMenu 씬 객체 생성
	Singleton<SceneManager>::GetInstance().AddScene(menuScene); // 씬 추가
	Singleton<SceneManager>::GetInstance().Init();	// SceneManager 초기화 -> currentScene 초기화 및 RenderSystem의 RenderLayer 초기화
}

void TestPlatformerGame::TestPlatformerGameApp::Render()
{
	__super::Render();
}

void TestPlatformerGame::TestPlatformerGameApp::Uninitialize()
{
	__super::Uninitialize();
}

void TestPlatformerGame::TestPlatformerGameApp::Update()
{
	__super::Update();
}

```