#include "SelectEffectManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"

void SelectEffectManager::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(true);

	for (int i = 0; i < 6; ++i) {
		GameObject* obj = new GameObject();
		obj->GetTransform().SetUnityCoords(true);
		obj->SetRenderLayer(EngineData::RenderLayer::None);
		auto br = obj->AddComponent<BitmapRenderer>();
		br->SetOrderInLayer(i - 100);

		effectProgress.push_back({ br, 0.0f });

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj, "SelectImage." + i);
	}

	auto basePath = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\robby\\";
	std::wstring files[] =
	{ L"2sky.png", L"3.png", L"4.png", L"5.png", L"6.png", L"robby_text.png"};

	for (int i = 0; i < std::size(files); ++i) {
		effectProgress[i].bitmapRenderer->CreateBitmapResource(basePath + files[i]);
		D2D1_SIZE_F rect = effectProgress[i].bitmapRenderer->GetResource()->GetBitmap()->GetSize();
		effectProgress[i].bitmapRenderer->owner->GetTransform().SetOffset(-rect.width / 2, rect.height / 2);
		effectProgress[i].bitmapRenderer->SetCapacity(0.0f);
	}
}

void SelectEffectManager::OnUpdate()
{

	if (isPlay) {
		float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();
		progress += 0.15f * delta;

		for (int i = 0; i < effectProgress.size(); ++i) {
			float posProgress = clampf((progress - effectProgress[i].startTimingPos) * (1.0f / (effectProgress[i].targetTimingPos - effectProgress[i].startTimingPos)), 0.0f, 1.0f);
			float currentX = effectProgress[i].startPos.x + (effectProgress[i].targetPos.x - effectProgress[i].startPos.x) * posProgress;
			float currentY = effectProgress[i].startPos.y + (effectProgress[i].targetPos.y - effectProgress[i].startPos.y) * posProgress;

			effectProgress[i].bitmapRenderer->owner->GetTransform().SetPosition(currentX, currentY);

			effectProgress[i].alpha = clampf((progress - effectProgress[i].startTimingAlpha) * (1.0f / (effectProgress[i].targetTimingAlpha - effectProgress[i].startTimingAlpha)), 0.0f, 1.0f);
			effectProgress[i].bitmapRenderer->SetCapacity(effectProgress[i].alpha);

		}

		if (progress >= 1.0f) isPlay = false;
	}
}

void SelectEffectManager::OnDestroy()
{


}

void SelectEffectManager::Start()
{
	Reset();
	isPlay = true;
}

void SelectEffectManager::Reset()
{
	progress = 0.0f;
	//[0]===============================================================
	//하늘 
	auto& p0 = effectProgress[0];
	p0.startPos = { 200.0f,100.0f };	p0.targetPos = { 0.0f,0.0f };
	p0.startTimingPos = 0.0f;			p0.targetTimingPos = 0.9f;
	p0.startTimingAlpha = 0.0f;			p0.targetTimingAlpha = 0.6f;

	//[1]===============================================================
	//왼쪽 원경
	auto& p1 = effectProgress[1];
	p1.startPos = { 192.0f,-100.0f };	p1.targetPos = { 0.0f,0.0f };
	p1.startTimingPos = 0.0f;			p1.targetTimingPos = 0.9f;
	p1.startTimingAlpha = 0.3f;			p1.targetTimingAlpha = 1.0f;
	//[2]===============================================================
	//오른쪽 원경
	auto& p2 = effectProgress[2];
	p2.startPos = { -192.0f,-300.0f };	p2.targetPos = { 0.0f,0.0f };
	p2.startTimingPos = 0.3f;			p2.targetTimingPos = 0.9f;
	p2.startTimingAlpha = 0.3f;			p2.targetTimingAlpha = 0.5f;
	//[3]===============================================================
	//오른쪽 중경
	auto& p3 = effectProgress[3];
	p3.startPos = { 200.0f,-400.0f };	p3.targetPos = { 0.0f,0.0f };
	p3.startTimingPos = 0.0f;			p3.targetTimingPos = 0.9f;
	p3.startTimingAlpha = 0.2f;			p3.targetTimingAlpha = 0.8f;
	//[4]===============================================================
	//왼쪽 근경
	auto& p4 = effectProgress[4];
	p4.startPos = { -192.0f,-400.0f };	p4.targetPos = { 0.0f,0.0f };
	p4.startTimingPos = 0.7f;			p4.targetTimingPos = 0.9f;
	p4.startTimingAlpha = 0.7f;			p4.targetTimingAlpha = 0.9f;
	////////////////////////////////////////////////////////////////////
	//[5]===============================================================
	//문구 - 스테이지 선택
	auto& p5 = effectProgress[5];
	p5.startPos = { -100.0f,150.0f };	p5.targetPos = { 0.0f,0.0f };
	p5.startTimingPos = 0.0f;			p5.targetTimingPos = 1.0f;
	p5.startTimingAlpha = 0.95f;		p5.targetTimingAlpha = 1.0f;


	for (int i = 0; i < effectProgress.size(); ++i) { 
		effectProgress[i].bitmapRenderer->owner->GetTransform().SetPosition(effectProgress[i].startPos.x, effectProgress[i].startPos.y);
	}
}


