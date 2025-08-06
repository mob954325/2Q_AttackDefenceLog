#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/SliceRenderer.h"
#include "Components/Logic/InputSystem.h"

/* 25.08.06 | 작성자 : 이성호
*	기능 : 마우스의 좌표값을 받아서 slice renderer로 이미지를 자르는 monobehaivor 코드
*	설명 : 
*		겹침 상태를 Notyet, Processing, End로 구분 지어서 마우스의 시작점과 도착점을 Vector2로 저장한 뒤에 
		두 좌표 값을  SliceRenderer의 Slice 함수로 값을 보낸다.
*/

class SliceObject : public MonoBehavior
{
	enum OverlapState
	{
		Notyet = 0,
		Processing,
		End,
	};

public:
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void OnUpdate() override;
	void OnFixedUpdate() override;

private:
	/// <summary>
	/// 오브젝트와 마우스 겹침 다루는 함수 - 간단한 충돌이므로 Collision 사용 안함
	/// </summary>
	void HandleOverlap();

	/// <summary>
	/// 해당 좌표 값이 충돌 범위 인지 확인하는 함수 | sliceRenderer의 비트맵 이미지랑 비교 ( 충돌하면 true, 아니면 false ) 반환
	/// </summary>
	/// <returns>충돌되면 true 아니면 false</returns>
	bool IsOverlap(float x, float y);

	/// <summary>
	/// 받은 매개변수를 SliceRenderer의 비트맵 크기에 맞춰서 보정하는 함수
	/// </summary>
	/// <param name="vec">위치 값</param>
	/// <returns>보정된 vector2 값</returns>
	Vector2 ClampPoisiton(const Vector2& vec);

	SliceRenderer* sliceComp;
	InputSystem* input;

	OverlapState state = OverlapState::Notyet;

	Vector2 startVec{};
	Vector2 endVec{};
};

