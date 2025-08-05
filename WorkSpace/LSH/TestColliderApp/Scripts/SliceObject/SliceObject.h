#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/SliceRenderer.h"

class SliceObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void OnUpdate() override;
	void OnFixedUpdate() override;

private:
	SliceRenderer* sliceComp;
};

