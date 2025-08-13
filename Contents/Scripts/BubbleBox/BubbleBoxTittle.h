#pragma once
#include "Components/Base/MonoBehavior.h"
#include "../Engine/Components/Rendering/BitmapRenderer.h"
#include "../Engine/Components/Logic/InputSystem.h"

class BubbleBoxTittle : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void CheckInput();

private:
	BitmapRenderer* Text_01{};
	BitmapRenderer* Text_02{};
	BitmapRenderer* Text_03{};
	BitmapRenderer* Text_04{};
	BitmapRenderer* Text_05{};
	BitmapRenderer* Text_06{};
	BitmapRenderer* Text_07{};
	BitmapRenderer* Text_08{};
	BitmapRenderer* Text_09{};
	BitmapRenderer* Text_10{};
	BitmapRenderer* Text_11{};
	InputSystem* input{};

	float delaytime = 0.5f;
	size_t count = 0;

	bool StartCheck = true;
};

