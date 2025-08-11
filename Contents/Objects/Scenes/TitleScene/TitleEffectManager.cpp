#include "TitleEffectManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"

void TitleEffectManager::OnStart()
{
	owner->SetRenderLayer(EngineData::RenderLayer::None);
	owner->GetTransform().SetUnityCoords(true);

	for (int i = 0; i < 8; ++i) {
		GameObject* obj = new GameObject();
		obj->GetTransform().SetUnityCoords(true);
		obj->SetRenderLayer(EngineData::RenderLayer::None);
		auto br = obj->AddComponent<BitmapRenderer>();
		br->SetOrderInLayer(i);

		effectProgress.push_back({ br, 0.0f });

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj, "TitleImage." + i);
	}

	auto basePath = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\start\\";
	std::wstring files[] = { L"2sky.png", L"3.png", L"4.png", L"5.png", L"6.png", L"7boat.png", L"8human.png", L"title.png" };

	for (int i = 0; i < std::size(files); ++i) {


		effectProgress[i].bitmapRenderer->CreateBitmapResource(basePath + files[i]);
		D2D1_SIZE_F rect = effectProgress[i].bitmapRenderer->GetResource()->GetBitmap()->GetSize();
		effectProgress[i].bitmapRenderer->owner->GetTransform().SetOffset(-rect.width / 2, rect.height / 2);
		effectProgress[i].bitmapRenderer->SetCapacity(0.0f);

		if (i == 7) {
			effectProgress[i].bitmapRenderer->SetUseCustomRect(true);
			effectProgress[i].bitmapRenderer->SetDestRect({ 0.0f, 0.0f, rect.width / 2, rect.height / 2 });
			effectProgress[i].bitmapRenderer->SetSrcRect({ 0.0f, 0.0f, rect.width, rect.height });
		}

		//bitmaps[i]->SetActive(false);
	}

	//	bitmaps[7]->SetDestRect({ 10,10,0,0, });
		//

	Start();
}




void TitleEffectManager::OnUpdate()
{
	if (isPlay) {
		float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();

		for (int i = 0; i < effectProgress.size(); ++i) {
			//if (effectProgress[i].alpha < 1.0f)

			effectProgress[i].bitmapRenderer->SetCapacity(effectProgress[i].alpha);
			float currentX = effectProgress[i].startPos.x + (effectProgress[i].targetPos.x - effectProgress[i].startPos.x) * progress;
			float currentY = effectProgress[i].startPos.y + (effectProgress[i].targetPos.y - effectProgress[i].startPos.y) * progress;
			effectProgress[i].bitmapRenderer->owner->GetTransform().SetPosition(currentX, currentY);

			//effectProgress[i].pos.x += 10.0f * delta;
			//if (effectProgress[i].alpha >= 1.0f) {
			//	//effectProgress[i].bitmapRenderer->SetActive(false);
			//}
			//L"2sky.png", L"3.png", L"4.png", L"5.png", L"6.png", L"7boat.png", L"8human.png", L"title.png" };
			switch (i) {
			case 0: // 하늘 + 기러긔 // 알파값만
				effectProgress[i].alpha += 0.001f;
				break;
			case 1: // 원경(왼쪽)

				break;
			case 2: // 원경(오른쪽)


				break;
			case 3: // 중경(오른쪽)


				break;
			case 4: // 근경(왼쪽 - 플레이어 발판)


				break;
			case 5: // 원경(보트)


				break;
			case 6: // 캐릭터


				break;
			case 7: // 로고 << 가장 마지막에


				break;

			default:

				break;
			}
		}

		//std::cout << 


//		if (effectProgress[0].alpha > 1.0f) isPlay = false;
	}

}

void TitleEffectManager::OnDestroy()
{


}

void TitleEffectManager::Start()
{
	Reset();
	isPlay = true;
}

void TitleEffectManager::Reset()
{
	for (int i = 0; i < effectProgress.size(); ++i) {
		effectProgress[i].alpha = 0.0f; // 알파값 전부 0으로
	}

	progress = 0.0f;

	effectProgress[0].startPos = { 0.0f,0.0f };
	effectProgress[1].startPos = { -30.0f,0.0f };

	effectProgress[2].startPos = { 0.0f,0.0f };
	effectProgress[3].startPos = { 0.0f,0.0f };

	effectProgress[4].startPos = { 0.0f,0.0f };
	effectProgress[5].startPos = { 0.0f,0.0f };

	effectProgress[6].startPos = { 0.0f,0.0f };
	effectProgress[7].startPos = { 0.0f,0.0f };






}


