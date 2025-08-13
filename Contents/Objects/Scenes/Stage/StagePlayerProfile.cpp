#include "StagePlayerProfile.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"

void StagePlayerProfile::OnCreate()
{
	owner->SetRenderLayer(EngineData::UI);
	owner->GetTransform().SetUnityCoords(false);
	playerProfile = owner->AddComponent<BitmapRenderer>();
	playerProfile->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\ProfileUI\\player_ui.png"); 
	playerProfile->SetOrderInLayer(20);
}