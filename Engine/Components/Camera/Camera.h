#pragma once
#include "Components/Base/Component.h"
#include "Components/Base/Transform.h"

/// <summary>
/// 카메라 기능이 있는 컴포넌트
/// </summary>
/// <remarks>
/// 해당 컴포넌트를 사용할 때 부착한 오브젝트의 트랜스폼을 SetTransform 함수로 넘겨줘야함
/// 그렇지 않으면 내부적으로 기본 트랜스폼 생성해서 반환
/// 
/// 25 06 18 : SceneManager에 카메라 추가해야 카메라 적용됨
/// </remarks>
class Camera : public Component
{
public:
	void OnStart() override;	// 임시		
	void OnDestroy() override;

	// flag
	bool IsMainCamera();

	// getter, setter
	void SetIsMainCamera(bool value);
	D2D1_MATRIX_3X2_F GetMatrix() const;
	D2D1_MATRIX_3X2_F GetInvertMatrix() const;

	Transform& GetTransform() const;

	int& GetPriority();
	void SetPriority(int value);

	bool IsPriorityChanged() { return isPriorityChanged; }
	void ResetIsPriorityChanged() { isPriorityChanged = false; }

private:
	int priority = 10;
	bool isPriorityChanged = false;
	bool isMainCamera = false;
	bool isLocalTransform = false;	  // 참조한 트랜스폼이 아닌 직접 만든 트랜스폼인지 확인하는 변수
	Transform* localTransform{};	  // 카메라가 가지고 있는 Transform
};

