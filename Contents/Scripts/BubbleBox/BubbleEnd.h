#pragma once
#include "Components/Base/MonoBehavior.h"
#include "../Engine/Components/Rendering/BitmapRenderer.h"
#include "../Engine/Components/Logic/InputSystem.h"

class BubbleEnd : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void CheckInput();

private:

	std::vector<BitmapRenderer*> texts;

	InputSystem* input{};

	float timer = 0.0f;
	float delaytime = 0.5f;
	float rectY = 0.0f;

	size_t count = 0;

	bool StartCheck = true;
};

