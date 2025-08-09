#include "MouseTrailObject.h"
#include "Components/Base/GameObject.h"
// Components
#include "../Engine/Components/Rendering/TrailComponent.h"
#include "../Engine/Components/Logic/InputSystem.h"

void MouseTrailObject::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);
	auto t = owner->AddComponent<TrailComponent>();
	t->SetOrderInLayer(100);
	t->SetBitmap(L"../WorkSpace/HSK/Test/test5.png");
	t->SetTailBitmap(L"../WorkSpace/HSK/Test/test1.png");
	t->SetHeadBitmap(L"../WorkSpace/HSK/Test/white_brush_test3.png");
}

void MouseTrailObject::OnUpdate()
{
	auto t = owner->GetComponent<TrailComponent>();
	t->isDraw = Input::leftButtonDown; //좌클릭시 그리기 연동
	owner->GetTransform().SetPosition(Input::MouseX, Input::MouseY); // 마우스 좌표 갱신(트랜스폼 따라가는 식)	
}

void MouseTrailObject::OnDestroy()
{
}


