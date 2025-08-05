#include "TestScene.h"
#include "Script/MusicScript.h"
#include "Script/TestObject.h"
#include "Script/TestObject2.h"
#include "Script/MainCam.h"


void TestScene::TestScene::OnEnterImpl()
{
	MusicBox = new GameObject();
	MusicBox->SetName("Test Music");
	MusicBox->AddComponent<MusicScript::MusicScript>();
	AddGameObject(MusicBox);

	CameTest = new GameObject();
	CameTest->SetName("Test Came");
	CameTest->AddComponent<TestObject>();
	AddGameObject(CameTest);

	CameTest2 = new GameObject();
	CameTest2->SetName("Test Came2");
	CameTest2->AddComponent<TestObject2>();
	AddGameObject(CameTest2);

	MainCamera = new GameObject();
	MainCamera->SetName("MainCam");
	MainCamera->AddComponent<MainCam>();
	AddGameObject(MainCamera);

}

void TestScene::TestScene::OnExitImpl()
{
	
}

void TestScene::TestScene::UpdateImpl()
{

}

