#include "StageBGI2.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"

void StageBGI2::OnCreate()
{
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	backGround = owner->AddComponent<BitmapRenderer>();
	backGround->SetOrderInLayer(-200);
	backGround->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\stage2_background.png");

}

void StageBGI2::OnStart()
{
	D2D1_SIZE_F size = backGround->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);
}
