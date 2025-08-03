#pragma once
#include "Scene/Scene.h"
#include "TestColliderApp/Scripts/SliceObject/PieceObject.h"
#include "TestColliderApp/Scripts/SliceObject/SliceObject.h"

class SliceObjectScene : public Scene
{
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;
private:
	void CreatePieces(std::vector<PieceObject*>& out);
	SliceObject* CreateGridNode();

	std::vector<SliceObject*> sliceTargets{};
	GameObject* cursor{};
};

