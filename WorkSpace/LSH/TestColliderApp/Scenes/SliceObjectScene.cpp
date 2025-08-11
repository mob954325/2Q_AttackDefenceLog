#include "SliceObjectScene.h"
#include "TestColliderApp/Scripts/SliceObject/TestSliceCursor.h"
#include "Utils/StringConvert.h"
#include "TestColliderApp/Scripts/SliceObject/SliceObject.h"
#include "TestColliderApp/Scripts/ContentObject/EscMenubar.h"
#include "Application/AppPaths.h"

void SliceObjectScene::OnEnterImpl()
{	
	GameObject* menu = new GameObject();
	menu->AddComponent<EscMenuBar>();
	menu->SetName("MenuBar");
	AddGameObject(menu);
}

void SliceObjectScene::OnExitImpl()
{
}

void SliceObjectScene::UpdateImpl()
{
}