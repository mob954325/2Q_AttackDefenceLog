#include "TitleEffectManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"
#include "Platform/Input.h"
#include "Scripts/SceneCore.h"

#include "Scripts/BubbleBox/BubbleBoxTittle.h"



void TitleEffectManager::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(true);

	for (int i = 0; i < 11; ++i) {
		GameObject* obj = new GameObject();
		obj->GetTransform().SetUnityCoords(true);
		obj->SetRenderLayer(EngineData::RenderLayer::None);
		auto br = obj->AddComponent<BitmapRenderer>();
		br->SetOrderInLayer(i);

		effectProgress.push_back({ br, 0.0f });

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj, "TitleImage." + i);
	}

	auto basePath = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\BackGround\\start\\";
	std::wstring files[] =
	{ L"2sky.png", L"3.png",
		L"5.png", L"6.png", L"7boat.png",
		L"8human.png", L"title.png",
		L"top_and_bottom_filter_black1.png", L"top_and_bottom_filter_black2.png",
		L"touch_the_screen.png" };

	for (int i = 0; i < std::size(files); ++i) {
		effectProgress[i].bitmapRenderer->CreateBitmapResource(basePath + files[i]);
		D2D1_SIZE_F rect = effectProgress[i].bitmapRenderer->GetResource()->GetBitmap()->GetSize();
		effectProgress[i].bitmapRenderer->owner->GetTransform().SetOffset(-rect.width / 2, rect.height / 2);
		effectProgress[i].bitmapRenderer->SetCapacity(0.0f);

		if (i == 7 || i == 8)
			effectProgress[i].bitmapRenderer->SetCapacity(1.0f);

		if (i == 6) {
			effectProgress[i].bitmapRenderer->SetUseCustomRect(true);
			effectProgress[i].bitmapRenderer->SetDestRect({ 0.0f, 0.0f, rect.width / 1.5f, rect.height / 1.5f });
			effectProgress[i].bitmapRenderer->SetSrcRect({ 0.0f, 0.0f, rect.width, rect.height });
		}
	}


	GameObject* b = new GameObject();
	b->SetRenderLayer(EngineData::RenderLayer::UI);
	b->GetTransform().SetPosition(+-192.0f, -108.0f);
	b->GetTransform().SetUnityCoords(false);
	guideMessageImage = b->AddComponent<BitmapRenderer>();
	guideMessageImage->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\BattlePanel\\GuideText\\drawing_line_start_text.png");
	guideMessageImage->SetOrderInLayer(10000); // ...? 1억이요? << 너무커서 줄였음
	guideMessageImage->SetCapacity(1.0f);

	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(b, "guideMessageImage.");


}

void TitleEffectManager::OnUpdate()
{

	if (isPlay)
	{
		float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();
		progress += 0.15f * delta;

		for (int i = 0; i < effectProgress.size(); ++i)
		{
			if (i == 9) continue; // 화면터치는 연출 생략

			//날 선형보간의 신이라고 불러라 2트
			float t = clampf((progress - effectProgress[i].startTimingPos) * (1.0f / (effectProgress[i].targetTimingPos - effectProgress[i].startTimingPos)), 0.0f, 1.0f);
			
			// ease-out : 1 - (1 - t)^2
			float posProgress = 1.0f - (1.0f - t) * (1.0f - t);			

			float currentX = effectProgress[i].startPos.x + (effectProgress[i].targetPos.x - effectProgress[i].startPos.x) * posProgress;
			float currentY = effectProgress[i].startPos.y + (effectProgress[i].targetPos.y - effectProgress[i].startPos.y) * posProgress;

			effectProgress[i].bitmapRenderer->owner->GetTransform().SetPosition(currentX, currentY);

			effectProgress[i].alpha = clampf((progress - effectProgress[i].startTimingAlpha) * (1.0f / (effectProgress[i].targetTimingAlpha - effectProgress[i].startTimingAlpha)), 0.0f, 1.0f);
			effectProgress[i].bitmapRenderer->SetCapacity(effectProgress[i].alpha);


			guideMessageImage->SetCapacity(1.0f - progress * 10.0f);
			//식 설명은 effectProgress 구조체에 써있음
		}

		if (progress >= 1.0f) {
			isPlay = false;
			needTouch = true;
			timer = 0.0f;
		}

	}

	if (needTouch) {
		float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();

		if (touchAlpha <= 0.0f)			touchProgress = 0.4f;
		else if (touchAlpha >= 1.0f)	touchProgress = -0.4f;

		touchAlpha += touchProgress * delta;

		effectProgress[9].bitmapRenderer->SetCapacity(touchAlpha); // 내부에 클램핑 기능 들어있음
	}

	if ((progress >= 1.0f) && !isPlay)// 이벤트가 종료되면 마우스 클릭으로 씬 넘어갈 수 있게 추가 : 작성자 - 이성호
	{
		if (timer > 1.0f) { // 1초동안 로고좀 보셈
			if (!isTextCreated && Input::leftButtonDown)
			{
				// title 오브젝트 제거
				effectProgress[6].bitmapRenderer->SetCapacity(0.0f);

				// 화면터치 안내문 제거
				effectProgress[9].bitmapRenderer->SetCapacity(0.0f);
				needTouch = false;

				// title 텍스트 객체 추가
				GameObject* titleBubbleObj = new GameObject();
				auto BBTComp = titleBubbleObj->AddComponent<BubbleBoxTittle>();
				Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(titleBubbleObj, "TItleEffectManager");
				isTextCreated = true;
			}
		}
		else {
			timer += Singleton<GameTime>::GetInstance().GetDeltaTime(); // 타이머 증가
		}
	}
}

void TitleEffectManager::OnDestroy()
{


}

void TitleEffectManager::Start()
{
	Reset();
	isPlay = true;
	needTouch = false;
	touchProgress = 0.4f;
	touchAlpha = 0.0f;
}


void TitleEffectManager::Reset()
{
	//for (int i = 0; i < effectProgress.size(); ++i) { // 굳이 안해줘도 clampf에서 0.0 넣어줌, 
	//	effectProgress[i].alpha = 0.0f; // 알파값 전부 0으로
	//}

	progress = 0.0f;
	//[0]===============================================================
	//하늘 
	auto& p0 = effectProgress[0];
	p0.startPos = { 100.0f,200.0f };	p0.targetPos = { 0.0f,0.0f };
	p0.startTimingPos = 0.0f;			p0.targetTimingPos = 1.0f;
	p0.startTimingAlpha = 0.0f;			p0.targetTimingAlpha = 1.0f;

	//[1]===============================================================
	//전체 원경 - 가로로 긴 이미지
	auto& p1 = effectProgress[1];
	p1.startPos = { 100.0f,-100.0f };	p1.targetPos = { 0.0f,0.0f };
	p1.startTimingPos = 0.0f;			p1.targetTimingPos = 0.9f;
	p1.startTimingAlpha = 0.1f;			p1.targetTimingAlpha = 0.9f;

	//[2]===============================================================
	//오른쪽 근경
	auto& p2 = effectProgress[2];
	p2.startPos = { 150.0f,-250.0f };	p2.targetPos = { 0.0f,0.0f };
	p2.startTimingPos = 0.1f;			p2.targetTimingPos = 0.9f;
	p2.startTimingAlpha = 0.2f;			p2.targetTimingAlpha = 0.5f;

	//[4]===============================================================
	//왼쪽 근경
	auto& p4 = effectProgress[3];
	p4.startPos = { -400.0f,-500.0f };	p4.targetPos = { 0.0f,0.0f };
	p4.startTimingPos = 0.3f;			p4.targetTimingPos = 0.9f;
	p4.startTimingAlpha = 0.4f;			p4.targetTimingAlpha = 0.7f;

	//////////////////////////////////////////////////////////////////////////////////////////	
	//[5]===============================================================
	//보트
	auto& p5 = effectProgress[4];
	p5.startPos = { -100.0f,-150.0f };	p5.targetPos = { 0.0f,0.0f };
	p5.startTimingPos = 0.0f;			p5.targetTimingPos = 0.9f;
	p5.startTimingAlpha = 0.4f;			p5.targetTimingAlpha = 1.0f;
	//[6]===============================================================
	//주인공
	auto& p6 = effectProgress[5];
	p6.startPos = { -400.0f,-500.0f };	p6.targetPos = { 0.0f,0.0f };
	p6.startTimingPos = 0.3f;			p6.targetTimingPos = 0.9f;
	p6.startTimingAlpha = 0.7f;			p6.targetTimingAlpha = 1.0f;

	//////////////////////////////////////////////////////////////////////////////////////////
	//[7]===============================================================
	//로고
	auto& p7 = effectProgress[6];
	p7.startPos = { 650.0f,250.0f };	p7.targetPos = { 500.0f,100.0f };
	p7.startTimingPos = 0.0f;			p7.targetTimingPos = 1.0f;
	p7.startTimingAlpha = 0.9f;			p7.targetTimingAlpha = 1.0f;
	//[8, 9]===============================================================
	//필터
	auto& p8 = effectProgress[7];
	p8.startPos = { 0.0f,0.0f };		p8.targetPos = { 0.0f,1080.0f };
	p8.startTimingPos = 0.0f;			p8.targetTimingPos = 0.3f;
	p8.startTimingAlpha = 0.0f;			p8.targetTimingAlpha = 0.0f;

	auto& p9 = effectProgress[8];
	p9.startPos = { 0.0f,0.0f };		p9.targetPos = { 0.0f,-1080.0f };
	p9.startTimingPos = 0.0f;			p9.targetTimingPos = 0.3f;
	p9.startTimingAlpha = 0.0f;			p9.targetTimingAlpha = 0.0f;

	for (int i = 0; i < effectProgress.size(); ++i) {
		if (i == 9)
		{
			effectProgress[i].bitmapRenderer->owner->GetTransform().SetPosition(0.0f, -150.0f);
			continue;
		};

		effectProgress[i].bitmapRenderer->owner->GetTransform().SetPosition(effectProgress[i].startPos.x, effectProgress[i].startPos.y);
	}
}


