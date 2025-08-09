#include "NodeObject.h"
#include "Components/Base/GameObject.h"
#include "Components/Collision/CircleCollider.h"
#include "Platform/Input.h"
#include "Application/AppPaths.h"

// #include "Components/Logic/InputSystem.h"

/* 8.05. 한승규
* 유니티 좌표계로 쓰고싶은데
* 쓰게되면 패턴 드로우 컴포넌트 내부 기준점을
* 전부 바꿔야해서
* 귀찮앙 UI니까 어떻게든 되지 않을까
* UI니까 괜찮을듯?
*/
void NodeObject::OnCreate() {
	owner->SetRenderLayer(EngineData::RenderLayer::GameObject);
	owner->GetTransform().SetUnityCoords(false); // 이건 유니티좌표계 하면 안댐

	bitmapRenderer = owner->AddComponent<BitmapRenderer>(); // L"\\..\\Resource\\Sprite\\Mushroom.png"
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\ui03.png");
	bitmapRenderer->SetOrderInLayer(-1);

	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);		

}

void NodeObject::OnStart()
{	
		
}

void NodeObject::OnUpdate()
{
	isOverlap = false;

	float mouseX = Input::MouseX;
	float mouseY = Input::MouseY;
	if (CheckOverlap(mouseX, mouseY))
	{
		isOverlap = true;
	}
}

void NodeObject::OnDestroy()
{
}

bool NodeObject::IsOverlap()
{
	return isOverlap;
}

bool NodeObject::CheckOverlap(float x, float y)
{
	D2D1_SIZE_F bound = bitmapRenderer->GetResource()->GetBitmap()->GetSize();

	if (x >= owner->GetTransform().GetFinalMatrix().dx &&
		x <= owner->GetTransform().GetFinalMatrix().dx + bound.width &&
		y >= owner->GetTransform().GetFinalMatrix().dy &&
		y <= owner->GetTransform().GetFinalMatrix().dy + bound.height)
	{
		return true; // 겹침
	}

	return false; // 안겹침
}



