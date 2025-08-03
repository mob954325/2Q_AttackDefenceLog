#include "TestSliceCursor.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"

void TestSliceCursor::OnCreate()
{
	input = owner->AddComponent<InputSystem>();
}

void TestSliceCursor::OnStart()
{
}

void TestSliceCursor::OnUpdate()
{
	if (input->IsKeyPressed('R'))
	{
		for (auto obj : targets)
		{
			obj->Reset();
		}
	}
}

void TestSliceCursor::SetSliceTarget(std::vector<SliceObject*>& obj)
{
	targets = obj;
}