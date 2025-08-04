#include "SelectScene.h"
#include "../Engine/Components/Logic/InputSystem.h"
#include "../Objects/InputObject.h"
#include "../Objects/TestObject.h"

void SelectScene::OnEnterImpl()
{
	std::cout << "선택씬 진입" << std::endl;
	testObj = new GameObject();

	auto t = testObj->AddComponent<TestObject>();

	// 	auto r = testObj->AddComponent<BitmapRenderer>();
	// 	r->CreateBitmapResource(L"../WorkSpace/HSK/Test/test2.png");
		
	AddGameObject(testObj);

	inputObj = new GameObject();
	inputObj->AddComponent<InputObject>();
	AddGameObject(inputObj);
	
}

void SelectScene::OnExitImpl()
{
	std::cout << "선택씬 이탈" << std::endl;
}

int num = 0;

void SelectScene::UpdateImpl()
{
	auto t = testObj->GetComponent<TestObject>();	

	auto input = inputObj->GetComponent<InputSystem>();

	if (input->IsKeyPressed('2')) {		
		testObj->GetComponent<BitmapRenderer>()->CreateBitmapResource(L"../WorkSpace/HSK/Test/test2.png");
	}

	if (input->IsKeyPressed('1')) {
		Singleton<SceneManager>::GetInstance().LoadScene(STAGE1);
	}
	if (input->IsKeyPressed('4')) {
		Singleton<SceneManager>::GetInstance().LoadScene(STAGE2);
	}
	if (input->IsKeyPressed('5')) {
		Singleton<SceneManager>::GetInstance().LoadScene(STAGE3);
	}
}
