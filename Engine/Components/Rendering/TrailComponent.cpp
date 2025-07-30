#include "TrailComponent.h"
#include "Components/Camera/Camera.h"
#include "Scene/SceneManager.h"

#include "Utils/GameTime.h"
#include "Datas/SpriteDatas.h"
#include "Utils/DebugUtility.h"
#include "Resources/ResourceManager.h"

/* 
#include "Components/Logic/InputSystem.h"
#include "Components/Rendering/TrailComponent.h"

Enter
	auto t = obj->GetComponent<TrailComponent>();
	t->isDraw = Input::leftButtonDown;
	t->isOutFromBox = Input::rightButtonDown;
	obj->GetTransform().SetPosition(Input::MouseX, Input::MouseY);

Update
	auto t = obj->GetComponent<TrailComponent>();
	t->isDraw = Input::leftButtonDown;
	t->isOutFromBox = Input::rightButtonDown;
	obj->GetTransform().SetPosition(Input::MouseX, Input::MouseY);
*/

constexpr float PI = 3.141592654f; // 

void TrailComponent::Update() { // 여기서 삭제(정리)처리해주면 됨
	// 	while (trails.size() > maxTrailCount && isOutFromBox) { // 최대 사이즈대로 빼줌, 나중에 조건추가하면 됨
	// 		trails.pop_front();
	// 	}

	// 	if (trails.size() > maxTrailCount && isOutFromBox)
	// 		trails.pop_front();

	if (wasDraw && !isDraw) { // 이후상태 true + 현재상태 false, 즉 꺼질때 한번
		cachedTrails = trails;
		isNewCached = true;		
		Clear();
	}
	wasDraw = isDraw;
}

void TrailComponent::Clear()
{
	trails.clear();
}

void TrailComponent::AddStamp(D2D1_POINT_2F pos) {
	if (!isDraw) return; // 

	if (trails.empty()) { // 
		trails.push_back({ pos, 0.0f });
		return;
	}

	const TrailStamp& last = trails.back(); // 

	float dx = pos.x - last.position.x; // 
	float dy = pos.y - last.position.y; // 
	float dist = sqrtf(dx * dx + dy * dy); // 

	if (dist < minDistance) // 
		return;

	int steps = static_cast<int>(dist / minDistance); //최소거리가 현재 간격에 몇번들어가는지 확인하는거임
	//(최소거리보다 커야 생성되니까 기본적으로 1 이상임 + int라 정수임)
	for (int i = 1; i <= steps; ++i) {
		float t = static_cast<float>(i) / steps; // 보간식, t + 1/t
		D2D1_POINT_2F interpPos = { // 보간으로 중간 점 생성해줌, 변화량(기울기)응용
			last.position.x + dx * t, // 원점에서 변화량만큼 이동 * 보간치
			last.position.y + dy * t
		};

		float angle = (i == 1) // 
			? GetAngle(last.position, interpPos) // 
			: GetAngle(trails.back().position, interpPos); // 
		trails.push_back({ interpPos, angle }); // 
	}

	if (isOutFromBox) {
		int over = trails.size() > maxTrailCount ? trails.size() - maxTrailCount : 0; // 얼마나 넘쳤는지 계산
		int deleteCount = over / 10; // 넘친 값의 퍼센트, 조절해주면 됨

		if (deleteCount < 1) deleteCount = 1; // 최소한 하나는 지워야지 
		else if (deleteCount > over) deleteCount = over; // 한번에 다지우는건 막아야지(int라서 그럼)

		// 꼬리 잘라냄
		for (int i = 0; i < deleteCount && !trails.empty(); ++i) {
			trails.pop_front();
		}
	}
}

void TrailComponent::Draw(D2DRenderManager* manager) { //
	if (!stampBitmap) return; // 
	if (!IsActiveSelf()) return; // 비활성화 얼리리턴

	for (auto& stamp : trails) { // 큐 전체를 순회하면서
		D2D1_SIZE_F bmpSize = stampBitmap->GetBitmap()->GetSize(); // 사이즈 대충 구해서 중앙기준으로
		D2D1_RECT_F destRect = { // 대충 이미지 정 가운데 기준
		 stamp.position.x - bmpSize.width * 0.5f,
		 stamp.position.y - bmpSize.height * 0.5f,
		 stamp.position.x + bmpSize.width * 0.5f,
		 stamp.position.y + bmpSize.height * 0.5f,
		};

		D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Rotation( //
			stamp.angle * 180.0f / PI,
			stamp.position
		);

		manager->SetRenderTransform(transform); // 회전행렬 적용
		D2D1_RECT_F srcRect = { // 이건 규격 맞출려고 바꿔주는거임
			0.0f, 0.0f,
			bmpSize.width, bmpSize.height
		};

		manager->DrawBitmap(stampBitmap->GetBitmap(), destRect, srcRect); // 
	}
}

void TrailComponent::Render(D2DRenderManager* manager)
{
	Update(); // 여기서는 삭제 여부 판단함
	auto tf = owner->GetTransform().GetPosition(); // 컴포넌트가 붙어있는 오너의 좌표를 받아서
	AddStamp({ tf.x, tf.y }); // 스탬프 추가 시도, 좌표가 어느정도(기준치 이상으로) 움직여야 생성됨 
	Draw(manager);
}

void TrailComponent::SetBitmap(std::wstring path) // 
{
	stampBitmap = resourceManager->CreateBitmapResource(path);
}

void TrailComponent::OnDestroy() // 
{
	stampBitmap.reset(); //  20:30 
}