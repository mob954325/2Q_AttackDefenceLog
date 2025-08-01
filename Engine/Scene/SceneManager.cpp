#include "SceneManager.h"
#include "Systems/ScriptSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/TransformSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/PhysicSystem.h"
#include "Systems/MonoBehaviorSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Systems/UISystem.h"

SceneManager::~SceneManager()
{
}

void SceneManager::Init()
{
	assert(!scenes.empty() && "SceneManager has no scene, please add scene at application initialize.");

	currentScene = scenes[0];

	Singleton<RenderSystem>::GetInstance().InitializeRenderLayers();
	currentScene->OnEnter();
}

void SceneManager::LoadScene(int sceneIndex)
{
	if (sceneIndex < 0 || sceneIndex >= sceneCount)
	{
		// sceneIndex를 키로 가지는 Scene*이 scenes에 존재하지 않음 
		return;
	}

	currentScene->state = SceneState::ReadyToChange;
	targetSceneIndex = sceneIndex;
}

void SceneManager::CheckSceneLoad()
{
	if (currentScene->state == SceneState::ReadyToChange)
	{
		// 현재 씬 종료
		if (currentScene != nullptr)
		{
			currentScene->OnExit();
			Singleton<ScriptSystem>::GetInstance().ClearAll();
			Singleton<CollisionSystem>::GetInstance().ClearAll();
			Singleton<PhysicSystem>::GetInstance().ClearAll();
			Singleton<TransformSystem>::GetInstance().ClearAll();
			Singleton<CameraManager>::GetInstance().ClearAll();
			Singleton<RenderSystem>::GetInstance().ClearAll();
			Singleton<MonoBehaviorSystem>::GetInstance().ClearAll();
			Singleton<UISystem>::GetInstance().ClearAll();
		}

		// 씬 교체
		std::map<int, Scene*>::iterator it = scenes.find(targetSceneIndex);

		int nextSceneIndex = it->first;
		Scene* nextScene = it->second;

		currentScene = nextScene;
		currentSceneIndex = nextSceneIndex;

		Singleton<RenderSystem>::GetInstance().InitializeRenderLayers();
		currentScene->OnEnter();

		targetSceneIndex = -1;
	}
}

void SceneManager::AddScene(Scene* pScene)
{
	scenes.emplace(sceneCount, pScene);
	sceneCount++;
}

Scene* SceneManager::GetCurrentScene()
{
	return currentScene;
}