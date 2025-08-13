#include "CloudManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"

void CloudManager::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(true);

	for (int i = 0; i < 5; ++i) {
		GameObject* obj = new GameObject();
		obj->GetTransform().SetUnityCoords(true);
		obj->SetRenderLayer(EngineData::RenderLayer::UI);
		auto br = obj->AddComponent<BitmapRenderer>();		
		br->SetOrderInLayer(i + 100);

		effectProgress.push_back({ br, 0.0f });

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj, "CloudImage." + i);
	}

	auto basePath = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\cloud\\";
	std::wstring files[] =
	{ L"1background.png",L"cloud1.png", L"cloud2.png", L"cloud3.png", L"cloud4.png" };

	for (int i = 0; i < std::size(files); ++i) {
		effectProgress[i].bitmapRenderer->CreateBitmapResource(basePath + files[i]);
		D2D1_SIZE_F rect = effectProgress[i].bitmapRenderer->GetResource()->GetBitmap()->GetSize();
		effectProgress[i].bitmapRenderer->owner->GetTransform().SetOffset(-rect.width / 2, rect.height / 2);
		effectProgress[i].bitmapRenderer->SetCapacity(0.0f);
	}
}

void CloudManager::OnUpdate()
{

	if (isPlay) {
		float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();

		if (isReverse)
			progress -= 0.5f * delta;
		else
			progress += 0.5f * delta;

		for (int i = 0; i < effectProgress.size(); ++i) {
			//날 선형보간의 신이라고 불러라 2트
			float posProgress = clampf((progress - effectProgress[i].startTimingPos) * (1.0f / (effectProgress[i].targetTimingPos - effectProgress[i].startTimingPos)), 0.0f, 1.0f);
			float currentX = effectProgress[i].startPos.x + (effectProgress[i].targetPos.x - effectProgress[i].startPos.x) * posProgress;
			float currentY = effectProgress[i].startPos.y + (effectProgress[i].targetPos.y - effectProgress[i].startPos.y) * posProgress;

			effectProgress[i].bitmapRenderer->owner->GetTransform().SetPosition(currentX, currentY);

			effectProgress[i].alpha = clampf((progress - effectProgress[i].startTimingAlpha) * (1.0f / (effectProgress[i].targetTimingAlpha - effectProgress[i].startTimingAlpha)), 0.0f, 1.0f);
			effectProgress[i].bitmapRenderer->SetCapacity(effectProgress[i].alpha);

			//식 설명은 effectProgress 구조체에 써있음
		}

		if (progress >= 1.0f && !isReverse) isPlay = false;
		if (progress <= 0.0f && isReverse) isPlay = false;
	}
}

void CloudManager::Start()
{
	Reset();
	isReverse = false;
	isPlay = true;
	progress = 0.0f;
}

void CloudManager::ReverseStart()
{
	Reset();
	isReverse = true;
	isPlay = true;
	progress = 1.0f;
}



void CloudManager::Reset()
{
	//	progress = 0.0f; << Reverse 여부에 따라 1.0 혹은 0.0으로 해야함

	//[0]===============================================================
	//배경
	auto& p0 = effectProgress[0];
	p0.startPos = { 0.0f,0.0f };		p0.targetPos = { 0.0f,0.0f };
	p0.startTimingPos = 0.0f;			p0.targetTimingPos = 0.0f;
	p0.startTimingAlpha = 0.5f;			p0.targetTimingAlpha = 1.0f;

	//[1]===============================================================
	//구름 오른쪽 아래
	auto& p1 = effectProgress[1];
	p1.startPos = { 300.0f, -100.0f };	p1.targetPos = { 0.0f,0.0f };
	p1.startTimingPos = 0.0f;			p1.targetTimingPos = 1.0f;
	p1.startTimingAlpha = 0.0f;			p1.targetTimingAlpha = 1.0f;

	//[2]===============================================================
	//구름 왼쪽 위
	auto& p2 = effectProgress[2];
	p2.startPos = { -100.0f,300.0f };	p2.targetPos = { 0.0f,0.0f };
	p2.startTimingPos = 0.0f;			p2.targetTimingPos = 1.0f;
	p2.startTimingAlpha = 0.0f;			p2.targetTimingAlpha = 1.0f;

	//[3]===============================================================
	//구름 왼쪽 아래
	auto& p3 = effectProgress[3];
	p3.startPos = { -300.0f,0.0f };	p3.targetPos = { 0.0f,0.0f };
	p3.startTimingPos = 0.0f;			p3.targetTimingPos = 1.0f;
	p3.startTimingAlpha = 0.0f;			p3.targetTimingAlpha = 1.0f;

	//[4]===============================================================
	//구름 오른쪽 위
	auto& p4 = effectProgress[4];
	p4.startPos = { 300.0f,300.0f };	p4.targetPos = { 0.0f,0.0f };
	p4.startTimingPos = 0.0f;			p4.targetTimingPos = 1.0f;
	p4.startTimingAlpha = 0.0f;			p4.targetTimingAlpha = 1.0f;

	for (int i = 0; i < effectProgress.size(); ++i) {
		effectProgress[i].bitmapRenderer->owner->GetTransform().SetPosition(effectProgress[i].startPos.x, effectProgress[i].startPos.y);
	}
}


