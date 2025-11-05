#include "EndBackground.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"

void EndBackground::OnStart()
{
    owner->SetRenderLayer(EngineData::RenderLayer::None);
    owner->GetTransform().SetUnityCoords(true);

    bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\BackGround\\ending_background.png"); // Oh
    bitmapRenderer->SetOrderInLayer(-200);

    size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
    owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);
}

void EndBackground::OnUpdate()
{
}

void EndBackground::OnDestroy()
{
}
