#include "NodeObj.h"
#include "Scene/SceneManager.h"
#include "Utils/GameTime.h"
#include "Components/Base/GameObject.h"
#include "Components/Collision/CircleCollider.h"

void NodeObj::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::GameObject);
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(L"../HSK/Test/ui03.png");
	bitmapRenderer->SetOrderInLayer(-1); // 이거 그럼 나중에 밖으로 빼야할 수 있음 잘 적용되는지 몰루임
	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize(); 
	auto c = owner->AddComponent<CircleCollider>();
	owner->GetTransform().SetUnityCoords(false);
}

void NodeObj::OnUpdate()
{

}

void NodeObj::OnDestroy()
{
}


