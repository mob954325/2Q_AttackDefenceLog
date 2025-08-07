#include "NodeObject.h"
#include "Components/Base/GameObject.h"
#include "Components/Logic/InputSystem.h"

/* 8.05. 한승규
* 유니티 좌표계로 쓰고싶은데
* 쓰게되면 패턴 드로우 컴포넌트 내부 기준점을
* 전부 바꿔야해서
* UI니까 괜찮을듯?
*/
void NodeObject::OnCreate() {
	owner->SetRenderLayer(EngineData::RenderLayer::GameObject);
	owner->GetTransform().SetUnityCoords(false); // 이건 유니티좌표계 하면 안댐

	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(L"../WorkSpace/HSK/Test/ui03.png");
	bitmapRenderer->SetOrderInLayer(-1);

	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetOffset(-size.width / 2, size.height / 2);		

}

void NodeObject::OnStart()
{
	owner->GetTransform().GetPosition();
		
}

void NodeObject::OnUpdate()
{	
	Vector2 pos = owner->GetTransform().GetPosition();
	float dx = Input::MouseX - pos.x;
	float dy = Input::MouseY - pos.y;

	if((dx * dx + dy * dy) <= radius * radius && Input::leftButtonDown) {
		nowInside = true;

		if (!isInside ) {
			// Enter
			//여기다가 이펙트 처리




			std::cout << "무야호" << std::endl;						
		}
	}
	else
		nowInside = false;

	isInside = nowInside;
}

void NodeObject::OnDestroy()
{
}



