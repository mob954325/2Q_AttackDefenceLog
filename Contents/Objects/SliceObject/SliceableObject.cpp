#include "SliceableObject.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "SlicedObject.h"

void SliceableObject::OnCreate()
{
	if (owner->GetComponent<SliceRenderer>() == nullptr)
	{
		sliceComp = owner->AddComponent<SliceRenderer>();
	}
	else
	{
		sliceComp = owner->GetComponent<SliceRenderer>();
	}
}

void SliceableObject::OnStart()
{

}

void SliceableObject::OnUpdate()
{
	if (!isSliceable) return; 

	if (sliceComp->GetOriginal())
	{
		HandleOverlap(); // 겹침 확인 함수
	}
}

void SliceableObject::SetImage(std::wstring path)
{
	sliceComp->SetOriginalByPath(path);
}

void SliceableObject::AddEvent(std::function<void()> f)
{
	OnSlice.Add(f);
}

void SliceableObject::SetSliceable(bool value)
{
	isSliceable = value;
}

void SliceableObject::HandleOverlap()
{
	D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();	// Unity 좌표계를 고려해 매트릭스 값 가져오기
	Vector2 currentPosition = { mat.dx , mat.dy }; // 위치 값을 Vector2로 변경

	if (IsOverlap(Input::MouseX, Input::MouseY) )
	{
		if (state == OverlapState::Notyet && Input::leftButtonDown) // 충돌 전
		{
			state = OverlapState::Processing;	// 상태 변경 -> 충돌 중
			startVec = { Input::MouseX, Input::MouseY };
			startVec.x -= mat.dx;
			startVec.y -= mat.dy;

			startVec = ClampPoisiton(startVec); // 위치 보정
		}
	}
	else
	{
		if (state == OverlapState::Processing && Input::leftButtonDown) // 충돌 중일 때 충돌이 종료됨
		{
			state = OverlapState::End;	// 상태 변경 -> 충돌 종료
			endVec = { Input::MouseX, Input::MouseY };
			endVec.x -= mat.dx;
			endVec.y -= mat.dy;

			endVec = ClampPoisiton(endVec); // 위치 보정

			GameObject* obj = sliceComp->Slice(startVec, endVec); // 갱신된 위치를 가지고 slice함수 실행

			// 짤린 오브젝트가 생성되었음
			if (obj != nullptr)
			{
				Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj); // 해당 오브젝트를 씬에 추가해서 실행

				obj->AddComponent<SlicedObject>();

				if (!isSliced)
				{
					OnSlice.Invoke();
					isSliced = true;
				}

				state = OverlapState::Notyet;	// 다시 자를 수 있게 상태 변경 -> 충돌 전
			}
		}
	}
}

bool SliceableObject::IsOverlap(float x, float y)
{
	D2D1_SIZE_F bound = sliceComp->GetSize();
	Vector2 scale = owner->GetTransform().GetScale();
	float topGap = 40.0f;
	float widthGap = 10.0f;

	float minX = (owner->GetTransform().GetFinalMatrix().dx + widthGap) * scale.x;
	float maxX = (owner->GetTransform().GetFinalMatrix().dx + bound.width - widthGap) * scale.x;
	float minY = (owner->GetTransform().GetFinalMatrix().dy + topGap) * scale.y;
	float maxY = (owner->GetTransform().GetFinalMatrix().dy + bound.height) * scale.y;

	if (x >= minX && x <= maxX && y >= minY && y <= maxY)
	{
		return true; // 찾음알림
	}

	return false; // 못찾음
}

Vector2 SliceableObject::ClampPoisiton(const Vector2& vec)
{
	if (!sliceComp || !sliceComp->GetOriginal()->GetBitmap()) return Vector2::Zero(); // slice Renderer를 사용할 수 없으면 0,0 반환

	Vector2 resultVec = vec;
	if (vec.x < 0) resultVec.x = 0;
	if (vec.x > sliceComp->GetOriginal()->GetBitmap()->GetSize().width) resultVec.x = sliceComp->GetOriginal()->GetBitmap()->GetSize().width;
	if (vec.y < 0) resultVec.y = 0;
	if (vec.y > sliceComp->GetOriginal()->GetBitmap()->GetSize().height) resultVec.y = sliceComp->GetOriginal()->GetBitmap()->GetSize().height;

	return resultVec;
}
