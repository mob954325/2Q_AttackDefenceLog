#include "InputSystem.h"

void InputSystem::OnCreate()
{
	input = new Input();
}

void InputSystem::OnStart()
{
}

void InputSystem::OnDestroy()
{
	delete input;
}

void InputSystem::Update()
{
	input->Update();
}

bool InputSystem::IsKeyPressed(int vKey)
{
	return input->IsKeyPressed(vKey);
}

bool InputSystem::IsKeyDown(int vKey)
{
	return input->IsKeyDown(vKey);
}

bool InputSystem::IsKeyRelease(int vKey)
{
	return input->IsKeyReleased(vKey);
}

bool InputSystem::IsMouseButtonDown(MouseButton button)
{
	return input->IsMouseDown(button);
}
