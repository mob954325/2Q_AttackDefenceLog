#include "EndBackground.h"
#include "Components/Base/GameObject.h"
#include "Application/AppPaths.h"

void EndBackground::OnCreate()
{
	owner->GetTransform().SetUnityCoords(false);
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\BackGround\\ending_background.png"); // Oh
}

void EndBackground::OnStart()
{
}

void EndBackground::OnUpdate()
{
}

void EndBackground::OnDestroy()
{
}
