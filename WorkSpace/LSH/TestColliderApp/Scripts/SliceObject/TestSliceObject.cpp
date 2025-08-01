#include "TestSliceObject.h"
#include "Components/Base/GameObject.h"
#include "Platform/Input.h"

void TestSliceObject::OnCreate()
{
	origin = owner->AddComponent<BitmapRenderer>();

	for (int i = 0; i < 9; i++)
	{
		boxes.push_back(owner->AddComponent<BoxRenderer>());
	}
}

void TestSliceObject::OnUpdate()
{
	for (int i = 0; i < 9; i++)
	{
		D2D1_RECT_F bound = grids[i];
		float x = Input::MouseX;
		float y = Input::MouseY;
		if (x >= owner->GetTransform().GetFinalMatrix().dx + bound.left &&
			x <= owner->GetTransform().GetFinalMatrix().dx + bound.right &&
			y >= owner->GetTransform().GetFinalMatrix().dy + bound.top &&
			y <= owner->GetTransform().GetFinalMatrix().dy + bound.bottom)
		{
			std::cout << "current grid = " << i << std::endl;
		}
	}
}

void TestSliceObject::SetOriginImage(std::wstring path)
{
	origin->CreateBitmapResource(path);
}

void TestSliceObject::SetImages(std::vector<PieceObject*> objs)
{
	pieces = objs;
}

void TestSliceObject::Spread()
{
	for (PieceObject* obj : pieces)
	{
		obj->Move();
	}
}

void TestSliceObject::Reset()
{
	for (PieceObject* obj : pieces)
	{
		obj->Reset();
	}
}

void TestSliceObject::SetGrid()
{
	if (!origin->GetResource()->GetBitmap()) return; // 원본이미지가 비어 있으면 무시

	grids.clear();
	
	D2D1_SIZE_F size = origin->GetResource()->GetBitmap()->GetSize();
	for (int y = 0; y < 3; y++)
	{
		float left = 0;
		float top = size.height / 3 * y;
		float right = size.width / 3;
		float bottom = size.height / 3 * (y + 1);
		grids.push_back({left, top, right, bottom});

		left += size.width / 3;
		right += size.width / 3;
		grids.push_back({left, top, right, bottom});

		left += size.width / 3;
		right += size.width / 3;
		grids.push_back({left, top, right, bottom});
	}

	// debug
	for (int i = 0; i < 9; i++)
	{
		std::cout << grids[i].left << ", " << grids[i].top << ", " << grids[i].right << ", " << grids[i].bottom << std::endl;
		boxes[i]->SetRect(grids[i]);
	}
}
