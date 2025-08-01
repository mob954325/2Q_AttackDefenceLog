#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Logic/InputSystem.h"
#include "TestSliceObject.h" // 조각 실행 함수를 가지고 있는 monobehaivor

class TestSliceCursor : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

	void SetSliceTarget(TestSliceObject* obj); // 임시

private:
	InputSystem* input{};
	TestSliceObject* target{};
};

