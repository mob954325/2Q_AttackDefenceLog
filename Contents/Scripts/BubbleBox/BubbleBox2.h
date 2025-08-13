#pragma once
#include "Components/Base/MonoBehavior.h"
#include "../Engine/Components/Rendering/BitmapRenderer.h"
#include "../Engine/Components/Logic/InputSystem.h"

class BubbleBox2 : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void CheckInput();

private:
	BitmapRenderer* TextBox{};
	BitmapRenderer* Text_01{};
	BitmapRenderer* Text_02{};
	BitmapRenderer* Text_03{};
	BitmapRenderer* Text_04{};
	BitmapRenderer* Text_05{};
	InputSystem* input{};

	float delaytime = 0.0f;
	size_t count = 0;

	bool StartCheck = true;
};

