#include "SelectSceneBGI.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"

void SelectSceneBGI::OnStart()
{	
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(true);

	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\stage3_background.png"); // NOTE : 임시 배경화면
	bitmapRenderer->SetOrderInLayer(-10);

	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);
}

void SelectSceneBGI::OnUpdate()
{

}

void SelectSceneBGI::OnDestroy()
{
}


