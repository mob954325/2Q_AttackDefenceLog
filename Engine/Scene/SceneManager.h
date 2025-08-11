#pragma once
#include "Systems/ScriptSystem.h"
#include "Systems/RenderSystem.h"
#include "Utils/Singleton.h"
#include "Scene/Scene.h"
#include "Components/Camera/Camera.h"
#include <map>
#include <vector>

/// <summary>
/// 모든 씬 관리 클래스
/// </summary>
class SceneManager : public Singleton<SceneManager>
{
public:
	friend class Singleton<SceneManager>;

	void Init();
	void LoadScene(int sceneIndex);
	void CheckSceneLoad();
	void AddScene(Scene* pScene);
	Scene* GetCurrentScene();

private:
	SceneManager() = default;
	~SceneManager();

	std::map<int, Scene*> scenes; // sceneIndex, Scene로 저장된 씬 모음
	Scene* loadingScene;

	Scene* currentScene = nullptr; // 실행되고 있는 현재 씬
	int currentSceneIndex = -1;
	int targetSceneIndex = -1; // 변경할 목표 씬 인덱스
	int sceneCount = 0;
};