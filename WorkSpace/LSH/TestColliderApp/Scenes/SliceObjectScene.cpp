#include "SliceObjectScene.h"
#include "TestColliderApp/Scripts/SliceObject/TestSliceObject.h"
#include "TestColliderApp/Scripts/SliceObject/TestSliceCursor.h"
#include "Utils/StringConvert.h"

void SliceObjectScene::OnEnterImpl()
{
	const float PI = 3.1415926535f;
	int n = 8;
	for (int i = 0; i < n; i++)
	{
		// 오브젝트 및 컴포넌트 등록
		GameObject* obj = new GameObject();
		PieceObject* comp = obj->AddComponent<PieceObject>();
		pieces.push_back(comp);
		AddGameObject(obj);
	
		// 이미지 찾기
		std::wstring numStr = std::to_wstring(i + 1);
		pieces[i]->SetName("piece" + StringConvert::WstringToString(numStr));
		comp->SetBitmapByPath(L"../../Resource/Sprite/Test_Slice/node_fragment_" + numStr + L".png");

		// 회전 행렬 결정
		Vector2 normDir = { 0,1 };
		float angleDeg = -360.0f / n * (i);
		float angledRad = angleDeg * (PI / 180.0f);
		
		float cosTheta = cosf(angledRad);
		float sinTheta = sinf(angledRad);

		Vector2 rotatedDir;		
		rotatedDir.x = normDir.x * cosTheta - normDir.y * sinTheta;
		rotatedDir.y = normDir.x * sinTheta + normDir.y * cosTheta;

		comp->SetMoveDirection({ rotatedDir.x, rotatedDir.y });

		if (i < n / 2)
		{
			comp->SetMoveDirection({ 1, 0 });
		}
		else
		{
			comp->SetMoveDirection({ -1, 0});
		}
	}
	
	sliceTarget = new GameObject();
	sliceTarget->SetName("SliceTargetObject");
	AddGameObject(sliceTarget);

	TestSliceObject* comp1 = sliceTarget->AddComponent<TestSliceObject>();
	comp1->SetImages(pieces);
	comp1->SetOriginImage(L"../../Resource/Sprite/Test_Slice/Original.png");
	comp1->SetGrid();
	
	cursor = new GameObject();
	cursor->SetName("cursor");
	AddGameObject(cursor);

	TestSliceCursor* comp2 = cursor->AddComponent<TestSliceCursor>();
	comp2->SetSliceTarget(comp1);
}

void SliceObjectScene::OnExitImpl()
{
}

void SliceObjectScene::UpdateImpl()
{
}
