#include "TrailComponent.h"
#include "Scene/SceneManager.h"
#include "Utils/GameTime.h"
#include "Resources/ResourceManager.h"

constexpr float PI = 3.141592654f; // 이건 유명한 파이임

void TrailComponent::Update() { // 여기서 삭제(정리)처리해주면 됨
	float delta = GameTime::GetInstance().GetDeltaTime();

	if (WasJustReleased()) { // 꺼질때 한번
		cachedTrails = trails; // 캐싱하고
		isNewCached = true;		// 갱신 되었다고 외부에 알려주는 플래그

		for (auto& stamp : trails) { // 모든 스탬프의 플래그를 꺼줌
			stamp.isActive = false; // 업데이트에서 발견되면 바로 삭제 시작함
		}
	}

	//==========================================================================

	if (!trails.empty()) {
		int inactiveCount = 0; // 몇개 지워야하는지 총량 계산
		for (auto& stamp : trails) {
			if (!stamp.isActive)
				++inactiveCount; // 넘친 총량을 의미함						
			else
				break; // 연속되는 값이라, 하나 아니면 뒤에는 전부 아님
		}

		int toFade = inactiveCount / deleteStepDivider; // 1/N씩 지움
		if (toFade < 3 && inactiveCount > 0) toFade = 3; // 최소 3개씩은 지우자
		else if (toFade > inactiveCount) toFade = inactiveCount;

		//==========================================================================			
		int activeIndex = 0;

		for (int i = 0; i < trails.size(); i++) {
			auto& stamp = trails[i];

			if (!stamp.isActive) {
				if (stamp.alpha >= 0.9999f) {
					if (toFade-- <= 0) continue;
				}

				stamp.alpha -= fadeSpeed * delta;
				if (stamp.alpha < 0.0f)
					stamp.alpha = 0.0f;
			}
			else { //active = true								
				if (activeIndex < maxIndex) { // 전체 길이의 절반에 투명도를 적용함
					float t = static_cast<float>(activeIndex) / maxIndex; // 0.0 ~ 1.0
					float targetAlpha = std::sin(t * (PI * 0.5f)); // 0.0 ~ 1.0 자연 곡선 // sin(t * π/2)

					constexpr float minAlpha = 0.01f; // 0.0 되버리면 삭제대상이 되버림

					if (targetAlpha < minAlpha)
						targetAlpha = minAlpha;

					if (stamp.alpha > targetAlpha) {
						stamp.alpha -= fadeSpeed * delta;
						if (stamp.alpha < targetAlpha)
							stamp.alpha = targetAlpha;
					}
					else {
						stamp.alpha = targetAlpha;
					}
				}
				++activeIndex;
			}
		}

	}

	//==========================================================================
	// 알파 0인것들 삭제하는 부분
	while (!trails.empty()) {
		const auto& stamp = trails.front();
		if (stamp.alpha <= 0.0f) { // 알파값 0인 경우에
			trails.pop_front();
		}
		else {
			break; // 연속적인 값이라, 아닌거 하나 만나면 종료
		}
	}

	wasDraw = isDraw; // 버퍼 갱신
}

//==========================================================================

void TrailComponent::AddStamp(D2D1_POINT_2F pos) { //스탬프를 찍는건데, 거리거 너무 멀어지면 보간으로 채워넣음
	if (!isDraw) return;

	if (trails.empty()) { // 비었다면, 즉 첫번째 스탬프는 각도계산 필요 x
		trails.push_back({ pos, 0.0f }); // 각도 0으로 처리하고 끝냄
		return;
	}
	const TrailStamp& last = trails.back(); // 꼬리에 있는거 빌려옴

	if (!last.isActive) {
		trails.push_back({ pos, 0.0f });
		return;
	}

	float dx = pos.x - last.position.x; // X 변화량
	float dy = pos.y - last.position.y; // y 변화량
	float dist = sqrtf(dx * dx + dy * dy); // 피타고라그래고리오고라파덕

	if (dist < minDistance) // 가장 마지막에 찍힌 스탬프에서 일정거리 이상으로 좌표변동이 일어나야함
	{
		AddHoldStamp();
		return;
	}

	int steps = static_cast<int>(dist / minDistance); //최소거리가 현재 간격에 몇번들어가는지 확인하는거임
	//(최소거리보다 커야 생성되니까 기본적으로 1 이상임 + int라 정수임)

	for (int i = 1; i <= steps; ++i) { //1 이상이니까 1부터 시작함
		float t = static_cast<float>(i) / steps; // 보간식, t + 1/t
		D2D1_POINT_2F interpPos = { // 보간으로 중간 점 생성해줌, 변화량(기울기)응용
			last.position.x + dx * t, // 원점에서 변화량만큼 이동 * 보간치
			last.position.y + dy * t
		};

		float angle = GetAngle(last.position, interpPos);

		trails.push_back({ interpPos, angle }); // 1 ~ ? 갯수만큼 넣어줌

		if (trails.size() == 2)
			trails[0].angle = angle; // 첫 지점이 0.0f인데, 자연스럽게 방향성을 덮어씌우는 거임
	}

	//==========================================================================
	// 삭제하는곳 
	if (isOutFromBox) {
		int over = trails.size() - maxTrailCount;
		if (over <= 0) return;

		for (auto& stamp : trails) {
			stamp.isActive = false;
			//stamp.fadeTimer = 0.0f;
			if (--over <= 0) break;
		}
	}
}

//==========================================================================

void TrailComponent::Draw(D2DRenderManager* manager) {

	if (!stampBitmap) return; // 비트맵 없으면 얼리리턴

	if (!IsActiveSelf()) return; // 비활성화 얼리리턴

	D2D1_SIZE_F tailSize = tailBitmap->GetBitmap()->GetSize(); // 꼬리는 한번만 해주면 될듯
	D2D1_RECT_F tailSrcRect = { 0.0f, 0.0f, tailSize.width, tailSize.height };// 이건 규격 맞출려고 바꿔주는거임

	D2D1_SIZE_F bmpSize = stampBitmap->GetBitmap()->GetSize(); // 사이즈 대충 구해서 중앙기준으로
	D2D1_RECT_F srcRect = { 0.0f, 0.0f,	bmpSize.width, bmpSize.height };

	D2D1_SIZE_F headSize = headBitmap->GetBitmap()->GetSize();
	D2D1_RECT_F headSrcRect = { 0.0f, 0.0f, headSize.width, headSize.height };

	//==========================================================================

	for (int i = 0; i < trails.size(); ++i) { // 큐 전체를 순회하면서
		const TrailStamp& stamp = trails[i];

		D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Rotation( // 회전 행렬 생성하는거임
			stamp.angle * 180.0f / PI,
			stamp.position
		);
		D2D1_RECT_F destRect = { // 대충 이미지 정 가운데 기준
			stamp.position.x - bmpSize.width * 0.5f,
			stamp.position.y - bmpSize.height * 0.5f,
			stamp.position.x + bmpSize.width * 0.5f,
			stamp.position.y + bmpSize.height * 0.5f,
		};

		manager->SetRenderTransform(transform);

		//==========================================================================

		int head = (static_cast<int>(trails.size()) - headIndex);

		if (i < tailIndex && head > i) // 꼬리
			manager->DrawBitmap(tailBitmap->GetBitmap(), destRect, tailSrcRect, stamp.alpha); // 그려잇
		else if (i >= head && stamp.isActive) // 머리(-했을때, 오버플로우 가능성 있음, 그래서 int로 캐스팅함)
			manager->DrawBitmap(headBitmap->GetBitmap(), destRect, headSrcRect, stamp.alpha); // 그려잇		
		else // 몸통
			manager->DrawBitmap(stampBitmap->GetBitmap(), destRect, srcRect, stamp.alpha); // 그려잇
	}
}

//==========================================================================

void TrailComponent::Render(D2DRenderManager* manager)
{
	Update(); // 여기서는 삭제 여부 판단함
	auto tf = owner->GetTransform().GetPosition(); // 컴포넌트가 붙어있는 오너의 좌표를 받아서
	AddStamp({ tf.x, tf.y }); // 스탬프 추가 시도, 좌표가 어느정도(기준치 이상으로) 움직여야 생성됨 
	Draw(manager);
}

//==========================================================================

void TrailComponent::SetBitmap(std::wstring path) // 랩핑한거임, 별거없음
{
	stampBitmap = resourceManager->CreateBitmapResource(path);
	tailBitmap = stampBitmap; // 일단 몸통으로 초기화
	headBitmap = stampBitmap; // 머리도 초기화
	holdBitmap = stampBitmap; // 몰라 이것도 초기화
}

void TrailComponent::SetTailBitmap(std::wstring path) //꼬리는 나중에 추가하는걸 추천
{
	tailBitmap = resourceManager->CreateBitmapResource(path);
}

void TrailComponent::SetHeadBitmap(std::wstring path)
{
	headBitmap = resourceManager->CreateBitmapResource(path);
}

void TrailComponent::SetHoldBitmap(std::wstring path)
{
	holdBitmap = resourceManager->CreateBitmapResource(path);
}

void TrailComponent::AddHoldStamp() // 마우스 - 위치가 오랫동안 변하지 않으면 작동함
{	
	if (!allowHold) return;
	
	





}

void TrailComponent::OnDestroy() // 이거 안하면 터짐
{
	stampBitmap.reset();
};

void TrailComponent::Clear()
{
	trails.clear();
}
