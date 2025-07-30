#include "TrailComponent.h"
#include "Components/Camera/Camera.h"
#include "Scene/SceneManager.h"

#include "Utils/GameTime.h"
#include "Datas/SpriteDatas.h"
#include "Utils/DebugUtility.h"
#include "Resources/ResourceManager.h"

/* 사용 예시(마우스 따라가게 설정)
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

constexpr float PI = 3.141592654f; // 이 숫자는 유명한 파이라는거임

void TrailComponent::Update() { // 여기서 삭제(정리)처리해주면 됨
	while (trails.size() > maxTrailCount && isOutFromBox) { // 최대 사이즈대로 빼줌, 나중에 조건추가하면 됨
		trails.pop_front();
	}

	if (wasDraw && !isDraw) { // 이후상태 true + 현재상태 false, 즉 꺼질때 한번
		Clear();
	}
	wasDraw = isDraw;
}

void TrailComponent::Clear()
{
	trails.clear();
}

void TrailComponent::AddStamp(D2D1_POINT_2F pos) {
	if (!isDraw) return; // 플래그 얼리 리턴

	if (trails.empty()) { // 첫 요소는 바로 처리해버림, 어차피 각도 계산할 필요 없으니까
		trails.push_back({ pos, 0.0f });
		return;
	}

	const TrailStamp& last = trails.back(); // 구조체를 빌려옴, 큐의 가장 최근삽입된거 기준으로
	float dx = pos.x - last.position.x; // 변화량임, x증가량
	float dy = pos.y - last.position.y; // y증가량
	float dist = sqrtf(dx * dx + dy * dy); // 제곱해서 더한뒤 루트 씌움, 즉 거리임

	if (dist < minDistance) // 일정거리 이하면 생성안함,
		return;

	int steps = static_cast<int>(dist / minDistance); //최소거리가 현재 간격에 몇번들어가는지 확인하는거임
													  //(최소거리보다 커야 생성되니까 기본적으로 1 이상임 + int라 정수임)
	for (int i = 1; i <= steps; ++i) {
		float t = static_cast<float>(i) / steps; // 보간식, t + 1/t
		D2D1_POINT_2F interpPos = { // 보간으로 중간 점 생성해줌, 변화량(기울기)응용
			last.position.x + dx * t, // 원점에서 변화량만큼 이동 * 보간치
			last.position.y + dy * t 
		};

		float angle = (i == 1) // 첫번째 요소면
			? GetAngle(last.position, interpPos) // 마지막점과 각도 계산
			: GetAngle(trails.back().position, interpPos); // 아니면 마지막 추가된거랑 각도 계산
		trails.push_back({ interpPos, angle }); // 큐에 집어넣음, 나중에 draw에서 좌표 + 각도 기반으로 그려줌
	}
}

void TrailComponent::Draw(D2DRenderManager* manager) { // 본격적으로 그리는 부분
	if (!stampBitmap) return; // 비트맵 등록 안하면 안그림

	for (auto& stamp : trails) { // 큐 전체를 순회하면서
		D2D1_SIZE_F bmpSize = stampBitmap->GetBitmap()->GetSize(); // 사이즈 대충 구해서 중앙기준으로
		D2D1_RECT_F destRect = { // 대충 이미지 정 가운데 기준
		 stamp.position.x - bmpSize.width * 0.5f,
		 stamp.position.y - bmpSize.height * 0.5f,
		 stamp.position.x + bmpSize.width * 0.5f,
		 stamp.position.y + bmpSize.height * 0.5f,
		};

		D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Rotation( // 회전행렬 설정
			stamp.angle * 180.0f / PI,
			stamp.position
		);

		manager->SetBitmapTransform(transform); // 회전행렬 적용
		
		D2D1_RECT_F srcRect = { // 이건 규격 맞출려고 바꿔주는거임
			0.0f, 0.0f,
			bmpSize.width, bmpSize.height
		};

		manager->DrawBitmap(stampBitmap->GetBitmap(), destRect, srcRect); // 드로우 비트맵을 직접 호출해줌
	}
}

void TrailComponent::Render(D2DRenderManager* manager)
{
	Update(); // 여기서는 삭제 여부 판단함
	auto tf = owner->GetTransform().GetPosition(); // 컴포넌트가 붙어있는 오너의 좌표를 받아서
	AddStamp({ tf.x, tf.y }); // 스탬프 추가 시도, 좌표가 어느정도(기준치 이상으로) 움직여야 생성됨 
	Draw(manager); 

}

void TrailComponent::SetBitmap(std::wstring path) // 랩핑한거임
{
	stampBitmap = resourceManager->CreateBitmapResource(path);
}

void TrailComponent::OnDestroy() // 아무튼 필요함
{
	stampBitmap.reset(); // 수정했습니다 20:30 
}
