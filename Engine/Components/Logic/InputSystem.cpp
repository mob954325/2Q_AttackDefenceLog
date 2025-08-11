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
	if (!IsStarted()) return;

	input->Update();
}

bool InputSystem::IsKeyPressed(int vKey)
{
	if (!IsStarted()) return false;

	return input->IsKeyPressed(vKey);
}

bool InputSystem::IsKeyDown(int vKey)
{
	if (!IsStarted()) return false;

	return input->IsKeyDown(vKey);
}

bool InputSystem::IsKeyRelease(int vKey)
{
	if (!IsStarted()) return false;

	return input->IsKeyReleased(vKey);
}

bool InputSystem::IsMouseButtonDown(MouseButton button)
{
	if (!IsStarted()) return false;

	return input->IsMouseDown(button);
}
