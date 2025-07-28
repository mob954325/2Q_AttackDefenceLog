#include "HSKScene.h"

using namespace HSK;
void HSKScene::OnEnterImpl()
{
	obj = new GameObject();
	obj->SetName("test");
	AddGameObject(obj);
}

void HSKScene::OnExitImpl()
{
}

void HSKScene::UpdateImpl()
{
}
