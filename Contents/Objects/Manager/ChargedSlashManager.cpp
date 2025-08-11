#include "ChargedSlashManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "../Engine/Datas/EngineData.h"

#include "../Engine/Utils/GameTime.h"
#include "Application/AppPaths.h"

void ChargedSlashManager::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::UI);
	inputSys = owner->AddComponent<InputSystem>();
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\ui01.png");
	bitmapRenderer->SetOrderInLayer(100);
	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetUnityCoords(false); // 노드가 D2D좌표계임
	owner->GetTransform().SetOffset(-size.width / 2.0f, size.height / 2.0f);


	//그거임 좌우 상단에 필터 설정해주는 부분
	auto basePath = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\filter\\";
	std::wstring files[] = { L"left_filter_gradient.png", L"left_filter_black.png" , L"right_filter_gradient.png", L"right_filter_black.png" };

	filter.clear();
	for (int i = 0; i < std::size(files); ++i) {// 0, 2 >>
		filter.push_back(new GameObject);
		filter[i]->GetTransform().SetUnityCoords(true);
		filter[i]->SetRenderLayer(EngineData::RenderLayer::UI);
		auto bir = filter[i]->AddComponent<BitmapRenderer>();


		bir->SetOrderInLayer(500);
		bir->CreateBitmapResource(basePath + files[i]);
		bir->SetActive(false); // 나중에 지워줘야함
		auto si = bir->GetResource()->GetBitmap()->GetSize();
		filter[i]->GetTransform().SetOffset(-si.width / 2.0f, si.height / 2.0f);

		//bir->SetFlip(true);
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(filter[i], "filter." + i);

	}
}

void ChargedSlashManager::OnUpdate() {

	if (nowPos == Vector2::Zero() || nowNormalVec == Vector2::Zero()) return;

	if (!isPlay) return; // 어차피 여기서 isPlay로 걸러주긴 함

	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();

	if (Input::leftButtonDown) {

		if (CheckMouseInside()) {		// [1] 좌클릭을 누른 상태 + 차징 범위 내부에 있으면 델타 증가
			timer += delta;
			mouseTimer = 0.0f;

			//차징하고 있으면 여기옴, 나중에 델리게이트 연결해주면 될듯? <<<<<<<<<<<<<<<<<<<<<<<< 끼뺫!
		}
		else { // [2] 좌클릭 유지한상태로 밖으로 나감
			if (isCharged)  // 차징이 된 상태에서 나간건, 측정 시작을 의미함
				mouseTimer += delta;
			else {
				mouseTimer = 0.0f; // 이건 그냥 나간거임
				timer = 0.0f;
			}

		}
	}
	else // [3] 좌클릭을 놔버리면, 타이머 초기화
	{
		timer = 0.0f;
		if (isCharged)  //차징이 된 상황에서 마우스를 놓았다 = Slash의 마지막 지점임
			Slashing({ Input::MouseX, Input::MouseY }, mouseTimer); // 마지막 놓인 좌표 + 타이머 전달

		mouseTimer = 0.0f;
		isCharged = false;
		return;
	}

	if (!isCharged && timer >= chargeTimeRequired) {
		isCharged = true;
		std::cout << "차징 완료!" << std::endl;
	}

	std::cout << timer << std::endl;

}

void ChargedSlashManager::OnDestroy() {

}


void ChargedSlashManager::SetUpNodePos(const std::vector<Vector2>& vec)
{
	if (vec.size() < 9) return; // 9개짜리 들어와야함

	Vector2 centerPos = vec[4]; // 중앙노드(4번)	

	slashCache.clear();// 지워잇

	for (int i = 0; i < 9; ++i) {
		slashCache.push_back({ vec[i],(centerPos - vec[i]).Normalize() }); // 좌표 + 중앙노드와의 방향백터를 구해서 넣음
	}
}

void ChargedSlashManager::Start(int n) { // 1~9의 값이 들어옴
	if (n == 4) return; // 4번은 안해줄꺼임 어쩔티비 저쩔티비

	nowNormalVec = slashCache[n - 1].normal;
	nowPos = slashCache[n - 1].pos;

	owner->GetTransform().SetPosition(nowPos.x, nowPos.y); // 노드의 좌표로 오너를 옮김
	
	isPlay = true;
	onChargeStart.Invoke(); // 시작되었다고 알려주면, 외부에서는 노드를 비활성화시켜줌(연결해야됨)	
}

void ChargedSlashManager::Cancel() {
	nowNormalVec = { 0,0 };
	nowPos = { 0, 0 };
	isPlay = false;
}

//void ChargedSlashManager::Charging(){}

bool ChargedSlashManager::isSuccess(Vector2 pos, float t)
{

	if (t > exitTimeRequired) return false; // 시간 초과
	std::cout << t << " ";

	Vector2 v = pos - nowPos;
	if (v.Magnitude() < minDist) return false; // 최소거리 못넘김
	std::cout << t << v.Magnitude();

	float dot = Vector2::Dot(v.Normalize(), nowNormalVec);
	std::cout << "끼얏호우~!!!! >?> " << dot << std::endl;

	if (dot <= allowedAngleRadians) return false; // 방향 안 맞음	

	return true;
}

void ChargedSlashManager::Slashing(Vector2 pos, float time)
{
	if (isSuccess(pos, time)) { // 성공
		onFinisherSuccess.Invoke(); // 성공했다고 외부에 알려줌 << 인자 뭐 넣어줘야 할지도 모르겠네
		std::cout << "슬래시 성공" << nowPos << nowNormalVec << std::endl;
		Cancel();
	}
	else
		Reset(); // 실패
}

bool ChargedSlashManager::CheckMouseInside()
{
	Vector2 mouse = { Input::MouseX, Input::MouseY };
	float distSqr = (nowPos - mouse).SqrMagnitude();
	return distSqr < radius * radius;
}

void ChargedSlashManager::Reset() // 차징을 실패한다거나, 마우스가 방향이 틀린방향으로 갔다거나
{
	mouseTimer = 0.0f;
	timer = 0.0f;
	isCharged = false;

}

