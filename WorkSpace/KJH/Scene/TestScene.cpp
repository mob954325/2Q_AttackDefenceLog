#include "TestScene.h"
#include "Script/MusicScript.h"

void TestScene::TestScene::OnEnterImpl()
{
	MusicBox = new GameObject();
	MusicBox->SetName("Test Music");
	MusicBox->AddComponent<MusicScript::MusicScript>();
	AddGameObject(MusicBox);
}

void TestScene::TestScene::OnExitImpl()
{
	
}

void TestScene::TestScene::UpdateImpl()
{

}
