#pragma once
#include "Components/Base/MonoBehavior.h"
#include "../Engine/Components/Rendering/BitmapRenderer.h"
#include "../Engine/Components/Logic/InputSystem.h"
#include "Objects/Scenes/Stage/EscMenu/StageESCPanel.h"

class BubbleBox : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void CheckInput();

	void SetEscPanel(StageESCPanel* pPanel);

	bool isTutorial = false;

private:
	BitmapRenderer* TextBox{};
	BitmapRenderer* Text_01{};
	BitmapRenderer* Text_02{};
	BitmapRenderer* Text_03{};
	InputSystem* input{};
	StageESCPanel* escPanel{};

	float delaytime = 0.2f;
	size_t count = 0;

	bool StartCheck = true;
};

