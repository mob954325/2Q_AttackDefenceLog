#pragma once
#include "Components/Logic/ScriptComponent.h"
#include "Platform/Input.h"
class InputSystem : public ScriptComponent
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void Update();

	bool IsKeyPressed(int vKey);
	bool IsKeyDown(int vKey);
	bool IsKeyRelease(int vKey);
	bool IsMouseButtonDown(MouseButton button);

private:
	Input* input{};
};