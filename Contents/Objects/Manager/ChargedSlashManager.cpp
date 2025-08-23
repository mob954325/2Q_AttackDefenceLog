#include "ChargedSlashManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "../Engine/Datas/EngineData.h"

#include "../Engine/Utils/GameTime.h"
#include "Application/AppPaths.h"
#include "../Contents/Scripts/Camera/CamInstance.h"
#include "../Contents/Objects/Sound/SoundPlayScene.h"

void ChargedSlashManager::OnCreate()
{
	GameObject* c = new GameObject();
	c->SetRenderLayer(EngineData::RenderLayer::UI);
	pressDotInfo = c->AddComponent<BitmapRenderer>();
	pressDotInfo->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\press_dot_stage_text.png");
	pressDotInfo->SetOrderInLayer(1001);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(c, "pressDotInfo.");


	GameObject* a = new GameObject();
	a->SetRenderLayer(EngineData::RenderLayer::UI);
	slashLineInfo = a->AddComponent<BitmapRenderer>();
	slashLineInfo->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\drawing_line_stage_text.png"); // 선을 그어라
	slashLineInfo->SetOrderInLayer(1002);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(a, "slashLineInfo.");

}




void ChargedSlashManager::OnStart()
{

// 	auto camIns = owner->GetQuery()->FindByName("CAM");
// 	if (camIns) { camIns->GetComponent<CamInstance>()->(1, 1, 1, ShakeType::X); }

	owner->SetRenderLayer(EngineData::RenderLayer::UI);
	inputSys = owner->AddComponent<InputSystem>(); 
	bitmapRenderer = owner->AddComponent<BitmapRenderer>();
	bitmapRenderer->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Mouse\\ui01.png");
	bitmapRenderer->SetOrderInLayer(100);
	size = bitmapRenderer->GetResource()->GetBitmap()->GetSize();
	owner->GetTransform().SetUnityCoords(false); // 노드가 D2D좌표계임
	owner->GetTransform().SetOffset(-size.width / 2.0f, size.height / 2.0f);
	bitmapRenderer->SetActive(false);



	pressDotInfo->owner->GetTransform().SetUnityCoords(false); // 노드가 D2D좌표계임
	pressDotInfo->owner->GetTransform().SetOffset(-192.0f, 108.0f  );
	pressDotInfo->SetActive(false);
	
	slashLineInfo->owner->GetTransform().SetUnityCoords(false); // 노드가 D2D좌표계임
	slashLineInfo->owner->GetTransform().SetOffset(-192.0f, 108.0f);
	slashLineInfo->SetActive(false);





	//그거임 좌우 상단에 필터 설정해주는 부분
	auto basePath = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\filter\\";
	std::wstring files[] = { L"left_filter_black.png", L"left_filter_gradient.png", L"right_filter_black.png" , L"right_filter_gradient.png" };

	filter.clear();
	filterSizes.clear();

	for (int i = 0; i < std::size(files); ++i) {// 0, 2 >>
		filter.push_back(new GameObject);
		filter[i]->GetTransform().SetUnityCoords(true);
		filter[i]->SetRenderLayer(EngineData::RenderLayer::UI);
		auto bir = filter[i]->AddComponent<BitmapRenderer>();

		bir->SetActive(false);
		bir->SetOrderInLayer(500);
		bir->CreateBitmapResource(basePath + files[i]);
		filterSizes.push_back(bir->GetResource()->GetBitmap()->GetSize());
		filter[i]->GetTransform().SetOffset(-filterSizes[i].width / 2.0f, filterSizes[i].height / 2.0f);

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(filter[i], "filter." + i);
	}

	eff = owner->AddComponent<EffectInstance>();	
	fff = owner->AddComponent<Finaleffect>();		
	fff->SetAnimePosition(centerPos);

	soundFlag = true;
}

void ChargedSlashManager::OnUpdate() {
	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();
	HideOrRevealFilter(delta); // 필터 관리해주는 함수임, 내부에서 알아서 얼리리턴 해줌

	if (nowPos == Vector2::Zero() || nowNormalVec == Vector2::Zero()) return;

	if (!isPlay) return; // 어차피 여기서 isPlay로 걸러주긴 함



	if (Input::leftButtonDown) {
		pressDotInfo->SetActive(false);
		if (CheckMouseInside()) {		// [1] 좌클릭을 누른 상태 + 차징 범위 내부에 있으면 델타 증가
			if(timer == 0.0f)
				eff->CallEffect(EffectType::ChargeEffect, nowPos); // 아무튼 한번만 호출되죠?

			timer += delta;
			mouseTimer = 0.0f;			

			//차징하고 있으면 여기옴, 나중에 델리게이트 연결해주면 될듯? <<<<<<<<<<<<<<<<<<<<<<<< 끼뺫!
			if (soundFlag) {
				auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
				if (SoundCom) {
					SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"ComboCharge");
					SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
				}
				soundFlag = false;
			}
		}
		else { // [2] 좌클릭 유지한상태로 밖으로 나감
			eff->EndEffects(); // 모든 이펙트 끔
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
		
		soundFlag = true;

		eff->EndEffects(); // 모든 이펙트 끔
		timer = 0.0f;
		if (isCharged)  //차징이 된 상황에서 마우스를 놓았다 = Slash의 마지막 지점임
			Slashing({ Input::MouseX, Input::MouseY }, mouseTimer); // 마지막 놓인 좌표 + 타이머 전달

		mouseTimer = 0.0f;
		isCharged = false;
		return;
	}

	if (!isCharged && timer >= chargeTimeRequired) {
		isCharged = true;
		slashLineInfo->SetActive(true);
		std::cout << "차징 완료!!!!!" << std::endl;
	}

	//std::cout << sceneExittimer << std::endl;
}

void ChargedSlashManager::OnDestroy() {

}


void ChargedSlashManager::SetUpNodePos(const std::vector<Vector2>& vec)
{
	if (vec.size() < 9) return; // 9개짜리 들어와야함

	centerPos = vec[4]; // 중앙노드(4번)	

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

	bitmapRenderer->SetActive(true);
	pressDotInfo->SetActive(true);
	isPlay = true;


	isUpperLeft = (n == 1 || n == 9);
	isUpperRight = (n == 3 || n == 7);
	isHide = false;
	isMoveDone = false;

	//================================================(필터설정)
	if (isUpperLeft) { //뒤집어줘야함
		for (int i = 0; i < filter.size(); ++i) {
			auto fttt = filter[i]->GetComponent<BitmapRenderer>();
			fttt->SetFlipY(true);
			fttt->SetActive(true);

			if (i == 0 || i == 1)
				filter[i]->GetTransform().SetPosition(-EngineData::SceenWidth, -filterSizes[i].height);
			else // 2 3
				filter[i]->GetTransform().SetPosition(EngineData::SceenWidth, -filterSizes[i].height);

		}
	}
	else if (isUpperRight) { // 돌려놔야함(원본)
		for (int i = 0; i < filter.size(); ++i) { //필터 전부를 뒤집는거임 헷갈리면 안댐
			auto fttt = filter[i]->GetComponent<BitmapRenderer>();
			fttt->SetFlipY(false);
			fttt->SetActive(true);

			if (i == 0 || i == 1)
				filter[i]->GetTransform().SetPosition(-EngineData::SceenWidth, 0);
			else // 2 3
				filter[i]->GetTransform().SetPosition(EngineData::SceenWidth, 0);
		}
	}

	//1 3 -> 2 4 순서 등장
	// 2 4 -> 1 3 순서로 퇴장

	onChargeStart.Invoke(); // 시작되었다고 알려주면, 외부에서는 노드를 비활성화시켜줌(연결해야됨)	
}

void ChargedSlashManager::Cancel() {
	nowNormalVec = { 0,0 };
	nowPos = { 0, 0 };
	bitmapRenderer->SetActive(false);
	pressDotInfo->SetActive(false);
	slashLineInfo->SetActive(false);
	isPlay = false;
	isHide = true;
	isMoveDone = false;
}

bool ChargedSlashManager::isSuccess(Vector2 pos, float t)
{
	if (t > exitTimeRequired) return false; // 시간 초과
	std::cout << t << " ";

	Vector2 v = pos - nowPos;
	if (v.Magnitude() < minDist) return false; // 최소거리 못넘김
	std::cout << v.Magnitude();

	float dot = Vector2::Dot(v.Normalize(), nowNormalVec);
	std::cout << "내적 결과 >>>>>>>> " << dot << std::endl;

	if (dot <= allowedAngleRadians) return false; // 방향 안 맞음	

	return true;
}

void ChargedSlashManager::Slashing(Vector2 pos, float time)
{	
	if (isSuccess(pos, time)) { // 성공
		//fff->CallAnime(std::atan2(nowPos.y, nowPos.x) * 2 * PI );
		fff->CallAnime(std::atan2(nowNormalVec.y, nowNormalVec.x) * (180.0f / PI));
		onFinisherSuccess.Invoke(); // 성공했다고 외부에 알려줌 << 인자 뭐 넣어줘야 할지도 모르겠네
		slashLineInfo->SetActive(false);
		pressDotInfo->SetActive(false);
		auto camIns = owner->GetQuery()->FindByName("CAM");
		if (camIns) {
			camIns->GetComponent<CamInstance>()->Start(2.0f, 10.0f, 30.0f, ShakeType::X_Y);
			camIns->GetComponent<CamInstance>()->SetFastToSlow();
		}

		auto SoundCom = owner->GetQuery()->FindByName("SOUNDSTAGE");
		if (SoundCom) {
			SoundCom->GetComponent<SoundPlayScene>()->SetKeyHandle(L"ComboFinish");
			SoundCom->GetComponent<SoundPlayScene>()->PlaySound();;
		}


		std::cout << "슬래시 성공!!!!!" << nowPos << nowNormalVec << std::endl;
		Cancel();
	}
	else {
		std::cout << "슬래시 실패...." << nowPos << nowNormalVec << std::endl;
		Reset(); // 실패

	}
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
	pressDotInfo->SetActive(true); // 실패하면 다시 뜸
	slashLineInfo->SetActive(false);
}

void ChargedSlashManager::HideOrRevealFilter(float dt) // 델타를 받음
{
	if (isMoveDone == true) return;

	// 0이면 화면밖, 1이면 중앙임
	if (isHide) {
		progress -= 0.4f * dt; // 화면밖으로 나감
		if (progress <= 0.0f) isMoveDone = true;
	}
	else {
		progress += 0.2f * dt; // 중앙으로 옴
		if (progress >= 1.0f) isMoveDone = true;
	}

	progress = clampf(progress, 0.0f, 1.0f); \

		//progress(0.0 ~ 1.0) 기반으로, 좌표를 옮겨주면 되는데

		//1,3 항 같은 경우에는 0.0 ~ 0.5의 진행도로 움직임 << 먼저 나와야함
		//currentProgress = clampF((progress) * (1.0f / 0.5f), 0.0f, 1.0f) 

		// 0,2 항 같은 경우에는 0.5 ~ 1.0 << 나중에 나와야함
		// currentProgress = clampF((progress - 0.5f) * (1.0f / ( 1.0f - 0.5f)), 0.0f, 1.0f)

		// 보간식은, startPos + (targetPos - startPos) * currentProgress

		// 0, 1 항은 왼쪽 x = -EngineData::SceenWidth;  
		// 2, 3 항은 오른쪽 x = EngineData::SceenWidth;

		// Y는 변하지 않음, Flip여부에 따라서만 움직임
		// 즉, 플립한 경우 >> y = -filterSizes[i].height 플립 아니면 >> y = 0

		// X의 목표는 0임, 중앙으로 들어가는것 즉, 
		// targetPos는 플립 안하면 (0, 0), 플립하면 (0, -filterSizes[i].height)

		// isUpperRight인 경우, 원본 이미지(플립X)
		// isUpperLeft인 경우, 플립한 거임

		for (int i = 0; i < filter.size(); ++i) {

			float currentY = 0.0f;
			if (isUpperRight)
				currentY = 0.0f;
			else if (isUpperLeft)
				currentY = -filterSizes[i].height;

			float startX = 0.0f;

			if (i == 0 || i == 1)
				startX = -EngineData::SceenWidth;  //-startX << 왼쪽 , +startX << 오른쪽
			else if (i == 2 || i == 3)
				startX = EngineData::SceenWidth;

			float currentProgress = 0.0f;
			if (i == 1 || i == 3)
				currentProgress = clampf((progress) * (1.0f / 0.5f), 0.0f, 1.0f);
			else if (i == 0 || i == 2)
				currentProgress = clampf((progress - 0.5f) * (1.0f / (1.0f - 0.5f)), 0.0f, 1.0f);

			float currentX = startX + (0.0f - startX) * currentProgress;

			filter[i]->GetTransform().SetPosition(currentX, currentY);
		}
}



