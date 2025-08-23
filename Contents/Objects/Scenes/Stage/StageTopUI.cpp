#include "StageTopUI.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"
#include "Datas/EngineData.h"

void StageTopUI::OnCreate()
{
	owner->SetRenderLayer(EngineData::UI);
	owner->GetTransform().SetUnityCoords(false);
	topUI = owner->AddComponent<BitmapRenderer>();
	topUI->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\UI\\StageTop\\ui_frame.png");
}

void StageTopUI::OnStart()
{
}
