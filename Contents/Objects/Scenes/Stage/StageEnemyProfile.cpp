#include "StageEnemyProfile.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"

void StageEnemyProfile::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);
	owner->GetTransform().SetUnityCoords(false);
	enemyProfile = owner->AddComponent<BitmapRenderer>();
	enemyProfile->SetOrderInLayer(20);
}

void StageEnemyProfile::SetProfileImage(std::wstring str)
{
	enemyProfile->CreateBitmapResource(str);
}
