#include "SliceObject.h"
#include "Components/Base/GameObject.h"
#include "Platform/Input.h"
#include "Math/Vector2.h"

void SliceObject::OnCreate()
{
	origin = owner->AddComponent<BitmapRenderer>();

	for (int i = 0; i < 9; i++)
	{
		boxes.push_back(owner->AddComponent<BoxRenderer>());
	}

	input = owner->AddComponent<InputSystem>();
}

void SliceObject::OnUpdate()
{
	HandleOverlap();

	// test reset code
	if (input->IsKeyDown('R'))
	{
		state = OverlapState::Notyet;
	}
}

void SliceObject::HandleOverlap()
{
	int detectedIndex = -1;
	if (IsOverlap(Input::MouseX, Input::MouseY, detectedIndex))
	{
		if (state == OverlapState::Notyet)
		{
			state = OverlapState::Processing;
			std::cout << " start " << detectedIndex << std::endl;
			startVec = { Input::MouseX, Input::MouseY };
		}

		prevIndex = detectedIndex;
	}
	else
	{
		if (state == OverlapState::Processing)
		{
			if (prevIndex == detectedIndex) return;

			state = OverlapState::End;
			std::cout << " end " << prevIndex << std::endl;

			endVec = { Input::MouseX, Input::MouseY };
			Vector2 dir = (endVec - startVec).Normalize();

			float dot = Vector2::Dot(dir, HorizontalVec);
			float cross = Vector2::Cross(dir, HorizontalVec);

			std::cout << " dot : " << dot << std::endl;
			std::cout << " cross : " << cross << std::endl;

			// 임시 -> 시계방향으로 저장했을 때를 기준
			if ((dot >= 0 && dot >= -HORIZONTAL_DOT_THRESHOLD) && (dot >= 0 && dot <= HORIZONTAL_DOT_THRESHOLD)) // | 모양으로 가르기 ( 왼쪽 오른쪽 이동)
			{
				SliceVertical();
			}
			else if ((dot >= -1 && dot <= -VERTICAL_DOT_THRESHOLD) || (dot <= 1 && dot >= VERTICAL_DOT_THRESHOLD)) // - 모양으로 가르기 ( 위 아래 이동 )
			{
				SliceHorizon();
			}
			else if((dot < -HORIZONTAL_DOT_THRESHOLD && dot > -VERTICAL_DOT_THRESHOLD && cross >= 0) || 
					(dot > HORIZONTAL_DOT_THRESHOLD && dot < VERTICAL_DOT_THRESHOLD && cross <= 0)) // \ 모양으로 가르기 ( /의 반대 모양, 좌측하단, 우측 상단으로 이동)
			{
				SliceDiagonalRight();
			}
			else if ((dot > HORIZONTAL_DOT_THRESHOLD && dot < VERTICAL_DOT_THRESHOLD && cross > 0) || 
					(dot < -HORIZONTAL_DOT_THRESHOLD && dot > -VERTICAL_DOT_THRESHOLD && cross < 0)) // / 모양으로 가르기 ( 좌측상단, 우측 하단으로 이동)
			{

				SliceDiagonalLeft();
			}

			Spread();
		}
	}

}

bool SliceObject::IsOverlap(float x, float y, int& outIndex)
{
	for (int i = 0; i < 9; i++)
	{
		D2D1_RECT_F bound = grids[i];
		if (x >= owner->GetTransform().GetFinalMatrix().dx + bound.left &&
			x <= owner->GetTransform().GetFinalMatrix().dx + bound.right &&
			y >= owner->GetTransform().GetFinalMatrix().dy + bound.top &&
			y <= owner->GetTransform().GetFinalMatrix().dy + bound.bottom)
		{
			outIndex = i;	// 찾은 인덱스 out Param에 넣기
			return true;	// 찾음알림
		}
	}

	outIndex = -1;
	return false; // 못찾음
}

void SliceObject::SetOriginImage(std::wstring path)
{
	origin->CreateBitmapResource(path);
	origin->SetActive(false);
}

void SliceObject::SetImages(std::vector<PieceObject*> objs)
{
	pieces = objs;

	for (int i = 0; i < objs.size(); i++)
	{
		objs[i]->owner->GetTransform().SetParent(&this->owner->GetTransform());
	}
}

void SliceObject::Spread()
{
	for (PieceObject* obj : pieces)
	{
		obj->Move();
	}
}

void SliceObject::Reset()
{
	for (PieceObject* obj : pieces)
	{
		obj->Reset();
	}
}

void SliceObject::SetGrid(int gridSize)
{
	if (!origin->GetResource()->GetBitmap()) return; // 원본이미지가 비어 있으면 무시

	grids.clear();
	
	D2D1_SIZE_F size = origin->GetResource()->GetBitmap()->GetSize();
	for (int y = 0; y < gridSize; y++)
	{
		// y번째 첫번째 칸
		float left = owner->GetTransform().GetPosition().x;
		float top = size.height / gridSize * y + owner->GetTransform().GetPosition().y;
		float right = size.width / gridSize + owner->GetTransform().GetPosition().x;
		float bottom = size.height / gridSize * (y + 1) + owner->GetTransform().GetPosition().y;
		grids.push_back({ left, top, right, bottom });

		// 두번째 칸
		left += size.width / gridSize;
		right += size.width / gridSize;
		grids.push_back({ left, top, right, bottom });

		// 세번째 칸
		left += size.width / gridSize;
		right += size.width / gridSize;
		grids.push_back({left, top, right, bottom});
	}

	this->gridSize = gridSize;

	// debug
	for (int i = 0; i < gridSize * gridSize; i++)
	{
		std::cout << grids[i].left << ", " << grids[i].top << ", " << grids[i].right << ", " << grids[i].bottom << std::endl;
		boxes[i]->SetRect(grids[i]);
	}
}

void SliceObject::SliceVertical()
{
	for (int i = 0; i < pieces.size(); i++)
	{
		if (i < pieces.size() / 2)
		{
			pieces[i]->SetMoveDirection(Vector2::Right());
		}
		else
		{
			pieces[i]->SetMoveDirection(Vector2::Left());
		}
	}
}

void SliceObject::SliceHorizon()
{
	int size = pieces.size();
	int quarter = size / 4;
	int threeQuarter = size * 3 / 4;

	for (int i = 0; i < size; ++i)
	{
		if ((i >= 0 && i < quarter) || (i >= threeQuarter && i < size))
		{
			pieces[i]->SetMoveDirection(Vector2::Up()); // 양 끝은 위쪽
		}
		else
		{
			pieces[i]->SetMoveDirection(Vector2::Down()); // 가운데는 아래쪽
		}
	}
}

void SliceObject::SliceDiagonalLeft()
{
	int size = pieces.size();
	int quarter = size / 4;
	int threeQuarter = size * 3 / 4;

	for (int i = 0; i < size; i++)
	{
		int curr = i + 1;
		if (curr <= size / 2)
		{
			pieces[curr]->SetMoveDirection({ 0.45f, -0.45f }); // 우측 하단
		}
		else
		{
			pieces[curr % size]->SetMoveDirection({ -0.45f, 0.45f }); // 우측 하단
		}
	}
}

void SliceObject::SliceDiagonalRight()
{
	int size = pieces.size();
	int quarter = size / 4;
	int threeQuarter = size * 3 / 4;

	for (int i = 0; i < size; i++)
	{
		int curr = i - 1;
		if (curr < 0) curr += size;
		if (i < size / 2)
		{
			pieces[curr]->SetMoveDirection({ 0.45f, 0.45f }); // 우측 상단
		}
		else
		{
			pieces[curr]->SetMoveDirection({ -0.45f, -0.45f }); // 좌측 하단
		}
	}
}
