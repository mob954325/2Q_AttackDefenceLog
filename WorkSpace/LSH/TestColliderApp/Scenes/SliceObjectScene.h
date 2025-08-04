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
	void CreatePieces(std::vector<PieceObject*>& out);
	SplitObject* CreateGridNode();

	std::vector<SplitObject*> sliceTargets{};
	GameObject* cursor{};
};

