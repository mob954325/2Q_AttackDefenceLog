#include "SliceRenderer.h"
#include "Components/Base/GameObject.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/ResourceManager.h"
#include "Utils/GameTime.h"

void SliceRenderer::Render(D2DRenderManager* manager)
{
	if (!IsActiveSelf()) return;

	D2D1_MATRIX_3X2_F mat = owner->GetTransform().GetFinalMatrix();

	ID2D1Layer* pLayer = NULL;
	renderManager->CreateLayer(&pLayer);	// 레이어 생성
	
	// 위치 갱신
	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();
	infos.position.x += infos.dirVec.x * infos.speed * delta;
	infos.position.y += infos.dirVec.y * infos.speed * delta;

	// infos.dirVec.y += delta;
	mat.dx += infos.position.x;
	mat.dy += infos.position.y;

	renderManager->SetRenderTransform(mat); // 위치 설정

	renderManager->PushLayer(D2D1::InfiniteRect(), pathGeometry.Get(), pLayer); // 레이어 추가

	// draw rect 설정
	Vector2 ownerPosition = owner->GetTransform().GetPosition(); // owner 위치
	D2D1_SIZE_F size = originBitmap->GetBitmap()->GetSize();
	D2D1_RECT_F destRect = { 0, 0, size.width, size.height }; // 오브젝트 움직이면 마스크위치가 안움직임
	D2D1_RECT_F srcRect = { 0, 0, size.width, size.height };

	// 이미지 그리기
	renderManager->DrawBitmap(originBitmap->GetBitmap(), destRect, srcRect);
	renderManager->PopLayer(); // 사용한 레이어 제거

	pLayer->Release();
	pLayer = NULL;
}

void SliceRenderer::SetOriginalByPath(std::wstring path)
{
	if (originBitmap)
	{
		originBitmap.reset();
	}

	originBitmap = resourceManager->CreateBitmapResource(path);

	D2D1_SIZE_F size = originBitmap->GetBitmap()->GetSize();

	SetPoint({
	{ 0.f, 0.f },
	{ size.width, 0.f },
	{ size.width, size.height },
	{ 0.f, size.height }
	});
}

void SliceRenderer::SetOriginalByBitmap(std::shared_ptr<BitmapResource> bitmap)
{
	originBitmap = bitmap; // bitmapresource 추가하기

	D2D1_SIZE_F size = originBitmap->GetBitmap()->GetSize();
	SetPoint({
	{ 0.f, 0.f },
	{ size.width, 0.f },
	{ size.width, size.height },
	{ 0.f, size.height }
		});
}

std::shared_ptr<BitmapResource> SliceRenderer::GetOriginal() const
{
	return originBitmap;
}

void SliceRenderer::SetPoint(const std::vector<Vector2>& points)
{
	this->points = points;

	// debug
	//if (points.size() > lrs.size())
	//{
	//	int size = points.size() - lrs.size();
	//	for (int i = 0; i < size; i++) lrs.push_back(owner->AddComponent<LineRenderer>());

	//	for (int i = 0; i < lrs.size(); i++)
	//	{
	//		lrs[i]->SetPosition1(points[i % points.size()]);
	//		lrs[i]->SetPosition2(points[(i + 1) % points.size()]);
	//		lrs[i]->SetWidth(3);
	//	}
	//}
}

GameObject* SliceRenderer::Slice(const Vector2& left, const Vector2& right)
{
	assert(originBitmap && "originalBitmap is emtpy.");

	if (NearlyEqual(left.x, right.x) && NearlyEqual(left.y, right.y)) return nullptr;

	// NOTE : 단일 이미지 기준 작성
	D2D1_SIZE_F size = originBitmap->GetBitmap()->GetSize();

	std::vector<Vector2> polygon = points;

	if (points.empty()) return nullptr;

	ClipEdge cutLine = { right, left };
	GameObject* obj = nullptr;

	if (left.x < right.x) // 왼쪽에서 오른쪽 
	{
		// 위쪽 polygon 잘라서 자기 자신 geometry로 사용
		std::vector<Vector2> upper = ClipPolygon(polygon, cutLine);
		CreateGeomatryByPolygon(upper);
		SetPoint(upper);

		// 아래족 polygon 잘라서 새 GameObject 생성
		obj = new GameObject;
		auto comp = obj->AddComponent<SliceRenderer>();
		comp->SetOriginalByBitmap(originBitmap);

		Vector2 ownerVec = owner->GetTransform().GetPosition();
		obj->GetTransform().SetPosition(ownerVec.x, ownerVec.y); // 생성된 오브젝트 위치값 설정

		std::vector<Vector2> lower = ClipPolygon(polygon, { left, right });
		comp->CreateGeomatryByPolygon(lower);
		comp->SetPoint(lower);

		// test code
		if (useGravity)
		{
			comp->SetDirection({ 0, 1 });
			comp->SetSpeed(speed);
		}
	}
	else // 오른쪽에서 왼쪽
	{
		std::vector<Vector2> lower = ClipPolygon(polygon, { left, right });
		CreateGeomatryByPolygon(lower);
		SetPoint(lower);

		obj = new GameObject;
		auto comp = obj->AddComponent<SliceRenderer>();
		comp->SetOriginalByBitmap(originBitmap);

		Vector2 ownerVec = owner->GetTransform().GetPosition();
		obj->GetTransform().SetPosition(ownerVec.x, ownerVec.y); // 생성된 오브젝트 위치값 설정

		std::vector<Vector2> upper = ClipPolygon(polygon, cutLine);
		comp->CreateGeomatryByPolygon(upper);
		comp->SetPoint(upper);

		if (useGravity)
		{
			comp->SetDirection({ 0, 1 }); // d2d기준 y값 증가 -> 밑으로 떨어짐
			comp->SetSpeed(speed);
		}
	}


	return obj;
}

void SliceRenderer::CreateGeomatryByPolygon(const std::vector<Vector2>& polygon)
{
	HRESULT hr;

	renderManager->CreatePathGeometry(&pathGeometry); // 기하학 도형 path 객체 생성
	pathGeometry->Open(&pSink);

	pSink->SetFillMode(D2D1_FILL_MODE_WINDING);

	if (!polygon.empty())
	{
		pSink->BeginFigure(
			D2D1::Point2F(polygon[0].x, polygon[0].y),
			D2D1_FIGURE_BEGIN_FILLED
		);

		for (size_t i = 1; i < polygon.size(); ++i)
		{
			pSink->AddLine(D2D1::Point2F(polygon[i].x, polygon[i].y));
		}

		pSink->EndFigure(D2D1_FIGURE_END_CLOSED);
	}

	hr = pSink->Close();
	assert(SUCCEEDED(hr));
	pSink->Release();
	pSink = nullptr;
}

std::vector<Vector2> SliceRenderer::ClipPolygon(const std::vector<Vector2>& subjectPolygon, const ClipEdge& edge)
{
	std::vector<Vector2> output;
	int count = subjectPolygon.size();	// 크기
	Vector2 startVec = subjectPolygon.back();	// 검사 중인 변의 시작점 -> 항상 이전 위치를 유지, 첫 반복에서는 마지막점

	for (int i = 0; i < count; ++i)
	{
		Vector2 endVec = subjectPolygon[i];	// 현재 검사중인 변의 끝점 -> 반복문에서는 현재 위치

		bool isEndInside = IsInside(endVec, edge);
		bool isStartInside = IsInside(startVec, edge);

		if (isEndInside)
		{
			if (!isStartInside)
			{
				output.push_back(GetIntersection(startVec, endVec, edge));
			}

			output.push_back(endVec);
		}
		else if (isStartInside)
		{
			output.push_back(GetIntersection(startVec, endVec, edge));
		}

		startVec = endVec;
	}

	return output;
}

Vector2 SliceRenderer::GetIntersection(const Vector2& s, const Vector2& e, const ClipEdge& edge)
{
	Vector2 dir1 = e - s;                 // 잘리는 선분 (subject polygon)
	Vector2 dir2 = edge.p2 - edge.p1;     // 클리핑 선분

	Vector2 diff = edge.p1 -  s;		  // 교차크기

	float denom = Vector2::Cross(dir2, dir1);
	if (fabs(denom) < 1e-6f) // 0에 가깝다 -> 두 직선은 유사하다
		return s; // 또는 예외 처리 -> 시작점 반환

	// 선분 교차의 기본 수식 - 두 선분이 같은 점을 가르킬때의 t와 u를 구하는 식
	// s + t * dir1 = edge.p1 + u * dir2
	// 여기서 t와 u는 각 선분 위에서의 비율 ( 0 ~ 1이면 선분 안, 그 이상이면 연장선 )
	// t = (dir2 x (edge.p1 - s)) / (dir2 x dir1)
	float t = Vector2::Cross(dir2, diff) / Vector2::Cross(dir2, dir1); // 두 벡터의 교차비율

	return Vector2(s.x + dir1.x * t, s.y + dir1.y * t); // 반환 값 : dir1에 대한 교차비율 만큼 s의 위치값을 이동 시킨 결과
}

void SliceRenderer::SetPosition(const Vector2& position)
{
	infos.position = position;
}

void SliceRenderer::SetDirection(const Vector2& dir)
{
	infos.dirVec = dir;
}

void SliceRenderer::SetSpeed(float value)
{
	infos.speed = value;
}

void SliceRenderer::SetGravity(bool value)
{
	useGravity = value;
}

SliceBitmapInfo SliceRenderer::GetInfo() const
{
	return infos;
}

bool SliceRenderer::IsInside(const Vector2& p, const ClipEdge& edge)
{
	Vector2 edgeDir = edge.p2 - edge.p1;
	Vector2 pointDir = p - edge.p1;

	return Vector2::Cross(edgeDir, pointDir) >= 0; // cross 결과값이 양수면 clipEdge보다 위에 있음
}

bool SliceRenderer::NearlyEqual(float a, float b, float epsilon)
{
	return std::fabs(a - b) <= epsilon;
}
