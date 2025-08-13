#include "SelectSeal.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"
#include "Scene/SceneManager.h"

void SelectSeal::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);
	owner->GetTransform().SetUnityCoords(false);

	left = owner->AddComponent<BitmapRenderer>();
	left->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Seal\\seal_breaking_02.png");
	left->SetOrderInLayer(1110);

	right = owner->AddComponent<BitmapRenderer>();
	right->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Seal\\seal_breaking_01.png");
	right->SetOrderInLayer(1110);
}

void SelectSeal::OnStart()
{
}