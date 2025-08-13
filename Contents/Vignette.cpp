#include "Vignette.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"

void Vignette::OnCreate()
{
    owner->SetRenderLayer(EngineData::RenderLayer::None);
    owner->GetTransform().SetUnityCoords(true);
    owner->GetTransform().SetScale(0.85f, 0.85f);
    bitmapRenderer = owner->AddComponent<BitmapRenderer>();
    bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Stage\\side_darkness.png");
}

void Vignette::OnStart()
{
    bitmapRenderer->SetOrderInLayer(1200);

    size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
    owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);

    End();
}

void Vignette::OnUpdate()
{
    if (!isPlay) return;

    float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();

    if (isGoingFillUp) { // 차오름
        progress += 0.5f * delta;
        if (progress >= 1.0f) isPlay = false;
    }
    else // 감소함
    {
        progress -= 0.7f * delta;
        if (progress <= 0.0f) isPlay = false;
    }

    progress = clampf(progress, 0.0f, 1.0f);

    bitmapRenderer->SetCapacity(progress);
}

D2D1_SIZE_F Vignette::GetSize()
{
    return size;
}

void Vignette::Start()
{
    isGoingFillUp = true;
    progress = 0.0f;
    isPlay = true;
}

void Vignette::End()
{
    if (!isGoingFillUp) return;

    isGoingFillUp = false;
    progress = 1.0f;
    isPlay = true;
}