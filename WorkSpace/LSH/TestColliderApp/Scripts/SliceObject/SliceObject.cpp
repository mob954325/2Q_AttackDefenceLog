#include "SliceObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Math/GameRandom.h"

void SliceObject::OnCreate()
{
	rigid = owner->AddComponent<Rigidbody2D>();
	if (!owner->GetComponent<SliceRenderer>()) // 처음만들어진 오브젝트
	{
		sliceComp = owner->AddComponent<SliceRenderer>();
		// 379, 726
		sliceComp->SetOriginalByPath(L"../../Resource/Sprite/Test_Slice/teemo.png");
		rigid->SetGravity(false);
	}
	else // 추가된 오브젝트
	{
		sliceComp = owner->GetComponent<SliceRenderer>();
		rigid->SetGravity(true);
	}

}

void SliceObject::OnStart()
{
	// 91 102
	// sliceComp->SetOriginalByPath(L"../../Resource/Sprite/Test_Slice/Original.png");
	
	// 가로 자르기
	//auto obj = sliceComp->Slice({0,45}, {91, 45});
	//Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	// 
	//auto obj2 = sliceComp->Slice({ 0,35 }, { 91, 20 });
	//Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj2);

	// 세로 자르기
	// auto obj = sliceComp->Slice({ 50, 30 }, { 50, 102 });
	// Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	// 
	// auto obj2 = sliceComp->Slice({ 0, 40 }, { 40, 40 });
	// Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj2);
	// obj2->GetTransform().SetPosition(12, 12);

	// sliceComp->SetGravity(true);
	// sliceComp->SetSpeed(GameRandom::RandomRange(3.0f, 5.0f));
}

void SliceObject::OnDestroy()
{
}

void SliceObject::OnUpdate()
{
	if (sliceComp->GetOriginal()->GetBitmap())
	{
		HandleOverlap(); // 겹침 확인 함수
	}
}

void SliceObject::OnFixedUpdate()
{
}

bool SliceObject::IsOverlap(float x, float y)
{
	D2D1_SIZE_F bound = sliceComp->GetSize();

	if (x >= owner->GetTransform().GetFinalMatrix().dx &&
		x <= owner->GetTransform().GetFinalMatrix().dx + bound.width &&
		y >= owner->GetTransform().GetFinalMatrix().dy &&
		y <= owner->GetTransform().GetFinalMatrix().dy + bound.height)
	{
		return true; // 찾음알림
	}

	return false; // 못찾음
}

void SliceObject::HandleOverlap()
{
	D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();	// Unity 좌표계를 고려해 매트릭스 값 가져오기
	Vector2 currentPosition = { mat.dx , mat.dy }; // 위치 값을 Vector2로 변경

	//std::cout << mat.dx << ", " << mat.dy << std::endl;
	if (IsOverlap(Input::MouseX, Input::MouseY))
	{
		if (state == OverlapState::Notyet) // 충돌 전
		{
			state = OverlapState::Processing;	// 상태 변경 -> 충돌 중
			startVec = { Input::MouseX, Input::MouseY };			
			startVec.x -= mat.dx;
			startVec.y -= mat.dy;

			startVec = ClampPoisiton(startVec); // 위치 보정

			std::cout << " start " << startVec << std::endl;
		}
	}
	else
	{
		if (state == OverlapState::Processing) // 충돌 중일 때 충돌이 종료됨
		{
			state = OverlapState::End;	// 상태 변경 -> 충돌 종료
			endVec = { Input::MouseX, Input::MouseY };
			endVec.x -= mat.dx;
			endVec.y -= mat.dy;

			endVec = ClampPoisiton(endVec); // 위치 보정
			std::cout << " end " << endVec << std::endl;

			GameObject* obj = sliceComp->Slice(startVec, endVec); // 갱신된 위치를 가지고 slice함수 실행

			// 짤린 오브젝트가 생성되었음
			if (obj != nullptr)
			{
				Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj); // 해당 오브젝트를 씬에 추가해서 실행
				auto rigid = obj->AddComponent<Rigidbody2D>();

				// comp->SetGravity(true);
				 
				obj->AddComponent<SliceObject>();
				auto mono = obj->GetComponent<SliceObject>();
				state = OverlapState::Notyet;	// 다시 자를 수 있게 상태 변경 -> 충돌 전
			}
		}
	}
}

 Vector2 SliceObject::ClampPoisiton(const Vector2& vec)
{
	if (*(sliceComp) == 0 || !sliceComp->GetOriginal()->GetBitmap()) return Vector2::Zero(); // slice Renderer를 사용할 수 없으면 0,0 반환

	Vector2 resultVec = vec;
	if (vec.x < 0) resultVec.x = 0;
	if (vec.x > sliceComp->GetOriginal()->GetBitmap()->GetSize().width) resultVec.x = sliceComp->GetOriginal()->GetBitmap()->GetSize().width;
	if (vec.y < 0) resultVec.y = 0;
	if (vec.y > sliceComp->GetOriginal()->GetBitmap()->GetSize().height) resultVec.y = sliceComp->GetOriginal()->GetBitmap()->GetSize().height;

	return resultVec;
}
