#include "TitleEffectManager.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"

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

		bitmaps.push_back(br);

		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj, "TitleImage." + i);
	}

	auto basePath = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\ContentsResource\\start\\";
	std::wstring files[] = { L"2sky.png", L"3.png", L"4.png", L"5.png", L"6.png", L"7boat.png", L"8human.png", L"title.png" };

	for (int i = 0; i < std::size(files); ++i) {


		bitmaps[i]->CreateBitmapResource(basePath + files[i]);
		D2D1_SIZE_F rect = bitmaps[i]->GetResource()->GetBitmap()->GetSize();
		bitmaps[i]->owner->GetTransform().SetOffset(-rect.width / 2, rect.height / 2);
		bitmaps[i]->SetCapacity(0.0f);

		if (i == 7) {
			bitmaps[i]->SetUseCustomRect(true);
			bitmaps[i]->SetDestRect({ 0.0f, 0.0f, rect.width/2, rect.height/2 });
			bitmaps[i]->SetSrcRect({ 0.0f, 0.0f, rect.width, rect.height });
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
		for (int i = 0; i < bitmaps.size(); ++i) {
			bitmaps[i]->SetCapacity(alpha);
		}

		alpha += 0.001f;

		if (alpha > 1.0f) isPlay = false;
	}

}

void TitleEffectManager::OnDestroy()
{
}

void TitleEffectManager::Start()
{
	isPlay = true;
	alpha = 0.0f;

}


