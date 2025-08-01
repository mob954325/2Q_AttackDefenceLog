#include "TestSliceCursor.h"
#include "Components/Base/GameObject.h"

void TestSliceCursor::OnCreate()
{
	input = owner->AddComponent<InputSystem>();
}

void TestSliceCursor::OnStart()
{
}

void TestSliceCursor::OnUpdate()
{
	if (input->IsKeyPressed('E'))
	{
		if ((*target) != 0)
		{
			target->Spread();
		}
	}

	if (input->IsKeyPressed('R'))
	{
		if ((*target) != 0)
		{
			target->Reset();
		}
	}
}

void TestSliceCursor::SetSliceTarget(TestSliceObject* obj)
{
	target = obj;
}