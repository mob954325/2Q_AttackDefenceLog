#include "TitleSceneBGI.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"

void TitleSceneBGI::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(true);

	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\start_background.png");
	bitmapRenderer->SetOrderInLayer(-10);	 		
	
	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);
}

void TitleSceneBGI::OnUpdate()
{

}

void TitleSceneBGI::OnDestroy()
{
}


