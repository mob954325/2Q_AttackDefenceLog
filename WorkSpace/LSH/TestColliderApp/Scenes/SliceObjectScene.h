#pragma once
#include "Scene/Scene.h"
#include "TestColliderApp/Scripts/SliceObject/PieceObject.h"
#include "TestColliderApp/Scripts/SliceObject/SplitObject.h"

class SliceObjectScene : public Scene
{
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;
private:
	std::vector<SplitObject*> sliceTargets{};
	GameObject* cursor{};
	GameObject* slice{};
};

