#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/TextRenderer.h"

class TestCircleCollider : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnFixedUpdate() override;
	void OnUpdate() override;
	void OnDestroy() override;

private:
	TextRenderer* infoText{};
};