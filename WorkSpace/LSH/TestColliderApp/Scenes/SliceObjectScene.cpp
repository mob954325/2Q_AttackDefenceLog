#include "SliceObjectScene.h"
#include "TestColliderApp/Scripts/SliceObject/TestSliceCursor.h"
#include "Utils/StringConvert.h"

void SliceObjectScene::OnEnterImpl()
{	
	for (int i = 0; i < 9; i++)
	{
		int x = i % 3;
		int y = i / 3;
		sliceTargets.push_back(CreateGridNode());

		sliceTargets[i]->owner->GetTransform().SetPosition(-250 + x * 150, y * 150);
	}
	
	cursor = new GameObject();
	cursor->SetName("cursor");
	AddGameObject(cursor);

	TestSliceCursor* comp2 = cursor->AddComponent<TestSliceCursor>();
	comp2->SetSliceTarget(sliceTargets);
}

void SliceObjectScene::OnExitImpl()
{
}

void SliceObjectScene::UpdateImpl()
{
}

void SliceObjectScene::CreatePieces(std::vector<PieceObject*>& out)
{
	int n = 8; // 이미지 개수
	for (int i = 0; i < n; i++)
	{
		// 오브젝트 및 컴포넌트 등록
		GameObject* obj = new GameObject();
		PieceObject* comp = obj->AddComponent<PieceObject>();
		out.push_back(comp);
		AddGameObject(obj);

		// 이미지 찾기
		std::wstring numStr = std::to_wstring(i + 1);
		out[i]->SetName("piece" + StringConvert::WstringToString(numStr));
		comp->SetBitmapByPath(L"../../Resource/Sprite/Test_Slice/node_fragment_" + numStr + L".png");
	}
}

SplitObject* SliceObjectScene::CreateGridNode()
{
	GameObject* obj = new GameObject();
	obj->SetName("SliceTargetObject");
	AddGameObject(obj);

	SplitObject* comp1 = obj->AddComponent<SplitObject>();
	std::vector<PieceObject*> out;
	CreatePieces(out);
	comp1->SetImages(out);
	comp1->SetOriginImage(L"../../Resource/Sprite/Test_Slice/Original.png");
	comp1->SetGrid(3);

	return comp1;
}