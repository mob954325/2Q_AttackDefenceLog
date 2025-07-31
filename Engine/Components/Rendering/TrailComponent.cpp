#include "TrailComponent.h"
#include "Scene/SceneManager.h"
//#include "Utils/GameTime.h"
//#include "Datas/SpriteDatas.h"
//#include "Utils/DebugUtility.h"
#include "Resources/ResourceManager.h"

constexpr float PI = 3.141592654f; // 이건 유명한 파이임

void TrailComponent::Update() { // 여기서 삭제(정리)처리해주면 됨

	if (wasDraw && !isDraw) { // 이후상태 true + 현재상태 false, 즉 꺼질때 한번
		cachedTrails = trails;
		isNewCached = true;		// 갱신 되었다고 외부에 알려주는 플래그

		//Clear(); // 한번에 지우기
		//isFadingOut = true; // 여러번 천천히 나눠서		

		for (auto& stamp : trails) { // 계속해서 지우기
			stamp.isActive = false; // 다 비활성화
		}
	}
	/*
	if (!wasDraw && isDraw)
		isFadingOut = false;

	if (isFadingOut) {
		for (int i = 0; i < 3 && !trails.empty(); ++i) {
			trails.pop_front();
		}
		if (trails.empty())
			isFadingOut = false;
	}
	*/

	/*
	if (!trails.empty()) {
		int removed = 0;
		while (!trails.empty() && removed < 4) {
			if (!trails.front().isActive) {
				trails.pop_front();
				++removed;
			}
			else {
				break; // 앞에 살아있는 게 있으면 그 뒤는 아직 놔둬야 함
			}
		}
	}
	*/

	if (!trails.empty()) {
		int inactiveCount = 0; // 몇개 지워야하는지 총량 계산
		for (const auto& stamp : trails) {
			if (!stamp.isActive)
				++inactiveCount;
			else
				break; // 연속이니까, 어차피 필요없음
		}

		// 커스텀
		int deleteCount = inactiveCount / 10; // 10% 지움
		if (deleteCount < 3 && inactiveCount > 0) deleteCount = 3; // 3개씩은 지우자
		else if (deleteCount > inactiveCount) deleteCount = inactiveCount;

		// 본격 삭제
		int removed = 0;
		while (!trails.empty() && removed < deleteCount) {
			if (!trails.front().isActive) {
				trails.pop_front();
				++removed;
			}
			else {
				break; // 살아있는거 만나면 중단
			}
		}
	}


	wasDraw = isDraw; // 버퍼 갱신
}

void TrailComponent::Clear()
{
	trails.clear();
}

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
	float dist = sqrtf(dx * dx + dy * dy); // 피타고라고라

	if (dist < minDistance) // 가장 마지막에 찍힌 스탬프에서 일정거리 이상으로 좌표변동이 일어나야함
		return;

	int steps = static_cast<int>(dist / minDistance); //최소거리가 현재 간격에 몇번들어가는지 확인하는거임
	//(최소거리보다 커야 생성되니까 기본적으로 1 이상임 + int라 정수임)

	

	for (int i = 1; i <= steps; ++i) { //1 이상이니까 1부터 시작함
		float t = static_cast<float>(i) / steps; // 보간식, t + 1/t
		D2D1_POINT_2F interpPos = { // 보간으로 중간 점 생성해줌, 변화량(기울기)응용
			last.position.x + dx * t, // 원점에서 변화량만큼 이동 * 보간치
			last.position.y + dy * t
		};

		float angle = GetAngle(last.position, interpPos, trails.back().angle);

		trails.push_back({ interpPos, angle }); // 1 ~ ? 갯수만큼 넣어줌
		
		if (trails.size() == 2) {			
			trails[0].angle = angle;
		}
	}

	if (isOutFromBox) {
		int over = trails.size() > maxTrailCount ? trails.size() - maxTrailCount : 0; // 얼마나 넘쳤는지 계산
		int deleteCount = over / 10; // 넘친 값의 퍼센트, 조절해주면 됨, 초과된 량의 10%씩 지움

		if (deleteCount < 1) deleteCount = 1; // 최소한 하나는 지워야지 
		else if (deleteCount > over) deleteCount = over; // 한번에 다지우는건 막아야지(int라서 그럼)

		// 꼬리 잘라냄
		for (int i = 0; i < deleteCount && !trails.empty(); ++i) {
			trails.pop_front();
		}
	}
}

void TrailComponent::Draw(D2DRenderManager* manager) {

	if (!stampBitmap) return; // 비트맵 없으면 얼리리턴

	if (!IsActiveSelf()) return; // 비활성화 얼리리턴

	D2D1_SIZE_F tailSize = tailBitmap->GetBitmap()->GetSize(); // 꼬리는 한번만 해주면 될듯
	D2D1_RECT_F tailSrcRect = { 0.0f, 0.0f, tailSize.width, tailSize.height };// 이건 규격 맞출려고 바꿔주는거임

	D2D1_SIZE_F bmpSize = stampBitmap->GetBitmap()->GetSize(); // 사이즈 대충 구해서 중앙기준으로
	D2D1_RECT_F srcRect = { 0.0f, 0.0f,	bmpSize.width, bmpSize.height };

	for (int i = 0; i < trails.size(); ++i) { // 큐 전체를 순회하면서
		const TrailStamp& stamp = trails[i];

		D2D1::Matrix3x2F transform = D2D1::Matrix3x2F::Rotation( // 회전 행렬 생성하는거임
			stamp.angle * 180.0f / PI,
			stamp.position
		);

		if (i == 0 && trails.size() >= 2) {
			D2D1_RECT_F tailDestRect = {
			stamp.position.x - tailSize.width * 0.5f,
			stamp.position.y - tailSize.height * 0.5f,
			stamp.position.x + tailSize.width * 0.5f,
			stamp.position.y + tailSize.height * 0.5f
			};
			manager->SetRenderTransform(transform);
			manager->DrawBitmap(tailBitmap->GetBitmap(), tailDestRect, tailSrcRect); // 그려잇
		}
		else {
			D2D1_RECT_F destRect = { // 대충 이미지 정 가운데 기준
			stamp.position.x - bmpSize.width * 0.5f,
			stamp.position.y - bmpSize.height * 0.5f,
			stamp.position.x + bmpSize.width * 0.5f,
			stamp.position.y + bmpSize.height * 0.5f,
			};
			manager->SetRenderTransform(transform);
			manager->DrawBitmap(stampBitmap->GetBitmap(), destRect, srcRect); // 그려잇
		}

	}
}

void TrailComponent::Render(D2DRenderManager* manager)
{
	Update(); // 여기서는 삭제 여부 판단함
	auto tf = owner->GetTransform().GetPosition(); // 컴포넌트가 붙어있는 오너의 좌표를 받아서
	AddStamp({ tf.x, tf.y }); // 스탬프 추가 시도, 좌표가 어느정도(기준치 이상으로) 움직여야 생성됨 
	Draw(manager);
}

void TrailComponent::SetBitmap(std::wstring path) // 랩핑한거임, 별거없음
{
	stampBitmap = resourceManager->CreateBitmapResource(path);
	tailBitmap = stampBitmap; // 일단 몸통으로 초기화
}

void TrailComponent::SetTailBitmap(std::wstring path) //꼬리는 나중에 추가하는걸 추천
{
	tailBitmap = resourceManager->CreateBitmapResource(path);
}

void TrailComponent::OnDestroy() // 이거 안하면 터짐
{
	stampBitmap.reset();
}