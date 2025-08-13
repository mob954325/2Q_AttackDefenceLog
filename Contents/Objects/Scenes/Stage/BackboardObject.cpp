#include "BackboardObject.h"
#include "Components/Base/GameObject.h"
#include "Components/Collision/CircleCollider.h"
#include "Platform/Input.h"
#include "Application/AppPaths.h"

void BackboardObject::OnCreate() {
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(true); // 이건 유니티좌표계 하면 안댐

	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\node_panel3.png");
	bitmapRenderer->SetOrderInLayer(-8); //뒷배경이 -10이던데

	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);		

}

void BackboardObject::OnStart()
{	
		
}

void BackboardObject::OnUpdate()
{

}

void BackboardObject::OnDestroy()
{
}



