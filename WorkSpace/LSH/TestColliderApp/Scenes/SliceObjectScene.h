#pragma once
#include "Scene/Scene.h"
#include "TestColliderApp/Scripts/SliceObject/PieceObject.h"

class SliceObjectScene : public Scene
{
protected:
	void OnEnterImpl() override;
	void OnExitImpl() override;
	void UpdateImpl() override;
private:
	std::vector<PieceObject*> pieces;
	GameObject* sliceTarget{};
	GameObject* cursor{};
};

