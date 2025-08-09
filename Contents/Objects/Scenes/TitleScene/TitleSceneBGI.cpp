#include "TitleSceneBGI.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"

void TitleSceneBGI::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(true);

	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(L"../Resource/ContentsResource/start_background.png");
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


