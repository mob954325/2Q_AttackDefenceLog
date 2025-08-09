#include "SelectScene.h"
#include "Components/Logic/InputSystem.h"
#include "Objects/Common/InputObject.h"
#include "Objects/Common/TestObject.h"
#include "Objects/Common/MouseTrailObject.h"

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

	trail = new GameObject();
	trail->AddComponent<MouseTrailObject>();
	AddGameObject(trail, "MouseTrail");
	
	testObj->GetComponent<BitmapRenderer>()->CreateBitmapResource(L"../WorkSpace/HSK/Test/test2.png");

}

bool start = true;

void SelectScene::OnExitImpl()
{
	std::cout << "선택씬 이탈" << std::endl;
	start = true;
}

void SelectScene::UpdateImpl()
{
	if (start) {
		//testObj->GetComponent<BitmapRenderer>()->CreateBitmapResource(L"../WorkSpace/HSK/Test/test2.png");
		start = false;
	}

	auto t = testObj->GetComponent<TestObject>();

	auto input = inputObj->GetComponent<InputSystem>();	

	if (input->IsKeyPressed('1')) {
		Singleton<SceneManager>::GetInstance().LoadScene(STAGE1);
	}
	// 	if (input->IsKeyPressed('3')) {
	// 		Singleton<SceneManager>::GetInstance().LoadScene(STAGE2);
	// 	}
	// 	if (input->IsKeyPressed('4')) {
	// 		Singleton<SceneManager>::GetInstance().LoadScene(STAGE3);
	// 	}
}
