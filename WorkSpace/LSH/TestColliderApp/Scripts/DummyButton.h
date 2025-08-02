#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/UI/Button.h"
#include "Components/Rendering/TextRenderer.h"

class DummyButton : public MonoBehavior
{
public:

	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnFixedUpdate() override;
	void OnDestroy() override;

private:
	void OnClick();
	void SetValue(int value);

	Button* button{};
	TextRenderer* fpsText{};

	int value = 0;
};

