#include "NodeObject.h"
#include "Components/Base/GameObject.h"
#include "Components/Collision/CircleCollider.h"

void NodeObject::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::GameObject);
	owner->GetTransform().SetUnityCoords(false);

	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(L"../WorkSpace/HSK/Test/ui03.png");

	bitmapRenderer->SetOrderInLayer(-1); // 이거 그럼 나중에 밖으로 빼야할 수 있음 잘 적용되는지 몰루임

	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();			
	auto c = owner->AddComponent<CircleCollider>();
	
}

void NodeObject::OnUpdate()
{

}

void NodeObject::OnDestroy()
{
}


