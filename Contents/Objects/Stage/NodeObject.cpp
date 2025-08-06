#include "NodeObject.h"
#include "Components/Base/GameObject.h"
#include "Components/Collision/CircleCollider.h"

/* 8.05. 한승규
* 유니티 좌표계로 쓰고싶은데
* 쓰게되면 패턴 드로우 컴포넌트 내부 기준점을
* 전부 바꿔야해서
* 귀찮앙 UI니까 어떻게든 되지 않을까
*/
void NodeObject::OnCreate() {
	owner->SetRenderLayer(EngineData::RenderLayer::GameObject);
	owner->GetTransform().SetUnityCoords(false); // 이건 유니티좌표계 하면 안댐

	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(L"../WorkSpace/HSK/Test/ui03.png");
	bitmapRenderer->SetOrderInLayer(-1);

	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);
	auto c = owner->AddComponent<CircleCollider>();

}

void NodeObject::OnStart()
{
	
		
}

void NodeObject::OnUpdate()
{

}

void NodeObject::OnDestroy()
{
}


