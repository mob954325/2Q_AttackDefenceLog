#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/SliceRenderer.h"
#include "Components/Logic/InputSystem.h"

class SliceObject : public MonoBehavior
{
	enum OverlapState
	{
		Notyet = 0,
		Processing,
		End,
	};

public:
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void OnUpdate() override;
	void OnFixedUpdate() override;

private:
	bool IsOverlap(float x, float y);
	void HandleOverlap();

	SliceRenderer* sliceComp;
	InputSystem* input;

	OverlapState state = OverlapState::Notyet;

	Vector2 startVec{};
	Vector2 endVec{};
};

