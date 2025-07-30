#include "NodeObj.h"
#include "Scene/SceneManager.h"
#include "Utils/GameTime.h"
#include "Components/Base/GameObject.h"
#include "Components/Collision/CircleCollider.h"

void Node::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::GameObject);
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(L"../HSK/Test/test2.png");
	bitmapRenderer->SetOrderInLayer(-1); // 이거 그럼 나중에 밖으로 빼야할 수 있음 잘 적용되는지 몰루임

	auto c = owner->AddComponent<CircleCollider>();




}

void Node::OnUpdate()
{

}

void Node::OnDestroy()
{
}

