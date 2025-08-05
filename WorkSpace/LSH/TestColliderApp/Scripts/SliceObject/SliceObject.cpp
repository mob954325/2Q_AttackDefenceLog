#include "SliceObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"

void SliceObject::OnCreate()
{
	sliceComp = owner->AddComponent<SliceRenderer>();
	input = owner->AddComponent<InputSystem>();
}

void SliceObject::OnStart()
{
	// 91 102
	sliceComp->SetOriginalByPath(L"../../Resource/Sprite/Test_Slice/Original.png");

	// 가로 자르기
	// auto obj = sliceComp->Slice({0,45}, {91, 45});
	// Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	//  
	// auto obj2 = sliceComp->Slice({ 0,35 }, { 91, 20 });
	// Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj2);
	// obj2->GetTransform().SetPosition(12, 12);

	// 세로 자르기
	// auto obj = sliceComp->Slice({ 50, 30 }, { 50, 102 });
	// Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	// 
	// auto obj2 = sliceComp->Slice({ 0, 40 }, { 40, 40 });
	// Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj2);
	// obj2->GetTransform().SetPosition(12, 12);
}

void SliceObject::OnDestroy()
{
}

void SliceObject::OnUpdate()
{
	// handle input
	if (input->IsKeyDown('W')) owner->GetTransform().Translate({ 0,1 });
	if (input->IsKeyDown('A')) owner->GetTransform().Translate({ -1,0 });
	if (input->IsKeyDown('S')) owner->GetTransform().Translate({ 0,-1 });
	if (input->IsKeyDown('D')) owner->GetTransform().Translate({ 1,0 });
	if (input->IsKeyDown('R')) state = OverlapState::Notyet;

	if (sliceComp->GetOriginal()->GetBitmap())
	{
		HandleOverlap();
	}
}

void SliceObject::OnFixedUpdate()
{
}

bool SliceObject::IsOverlap(float x, float y)
{
	for (int i = 0; i < 9; i++)
	{
		D2D1_SIZE_F bound = sliceComp->GetOriginal()->GetBitmap()->GetSize();
		if (x >= owner->GetTransform().GetFinalMatrix().dx &&
			x <= owner->GetTransform().GetFinalMatrix().dx + bound.width &&
			y >= owner->GetTransform().GetFinalMatrix().dy&&
			y <= owner->GetTransform().GetFinalMatrix().dy + bound.height)
		{
			return true; // 찾음알림
		}
	}

	return false; // 못찾음
}

void SliceObject::HandleOverlap()
{
	D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();
	Vector2 absoluteVec = { mat.dx , mat.dy };
	Vector2 resultVec = Vector2::Zero();
	if (IsOverlap(Input::MouseX, Input::MouseY))
	{
		if (state == OverlapState::Notyet)
		{
			state = OverlapState::Processing;
			startVec = { Input::MouseX, Input::MouseY };			
			resultVec = startVec - absoluteVec;

			// 위치 보정 - 속도가 너무 빠르면 감지값이 초과되거나 음수에 도달해서 처리함
			if (resultVec.x < 0) resultVec.x = 0;
			if (resultVec.x > sliceComp->GetOriginal()->GetBitmap()->GetSize().width) resultVec.x = sliceComp->GetOriginal()->GetBitmap()->GetSize().width;
			if (resultVec.y < 0) resultVec.y = 0;
			if (resultVec.y > sliceComp->GetOriginal()->GetBitmap()->GetSize().height) resultVec.y = sliceComp->GetOriginal()->GetBitmap()->GetSize().height;

			startVec = resultVec;
			std::cout << " start " << startVec << std::endl;
		}
	}
	else
	{
		if (state == OverlapState::Processing)
		{
			state = OverlapState::End;
			endVec = { Input::MouseX, Input::MouseY };
			resultVec = endVec - absoluteVec;

			// 위치 보정
			if (resultVec.x < 0) resultVec.x = 0;
			if (resultVec.x > sliceComp->GetOriginal()->GetBitmap()->GetSize().width) resultVec.x = sliceComp->GetOriginal()->GetBitmap()->GetSize().width;
			if (resultVec.y < 0) resultVec.y = 0;
			if (resultVec.y > sliceComp->GetOriginal()->GetBitmap()->GetSize().height) resultVec.y = sliceComp->GetOriginal()->GetBitmap()->GetSize().height;

			endVec = resultVec;
			std::cout << " end " << endVec << std::endl;

			GameObject* obj = sliceComp->Slice(startVec, endVec);

			if (obj != nullptr)
			{
				Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);		
				state = OverlapState::Notyet;
			}
		}
	}
}