#include "BattleBoard.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"


void BattleBoard::OnStart()
{
	std::wstring path = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Sign\\";
	std::wstring files[] =
	{ L"top_text.png",		L"mid_text.png",
	  L"bottom_text.png",	L"defence_text.png",
	  L"parrying_text.png",	L"hit_text.png",
	  L"evasion_text.png",	L"attack_text.png" };

	/*
		HighAttackSign = 0,
		MiddleAttackSign = 1,
		LowAttackSign = 2,
		GuardSign = 3,
		ParrySign = 4,
		HitSign = 5,
		EvasionSign = 6,
		EnemyAttackSign = 7
	*/

	for (int i = 0; i < std::size(files); ++i) {

		GameObject* bm = new GameObject();
		bm->SetRenderLayer(EngineData::RenderLayer::UI);

		auto render = bm->AddComponent<BitmapRenderer>();
		render->CreateBitmapResource(path + files[i]);
		render->SetOrderInLayer(-7); // 패널이 -8이던데				

		bm->GetTransform().SetUnityCoords(false);

		D2D1_SIZE_F size = render->GetResource()->GetBitmap()->GetSize(); // 430 * 273(8개 동일)
		D2D1_RECT_F dest = { 0, 0, size.width / 3.0f, size.height / 3.0f };
		D2D1_RECT_F src = { 0, 0, size.width, size.height };

		render->SetUseCustomRect(true);
		render->SetDestRect(dest);
		render->SetSrcRect(src);


		bm->GetTransform().SetOffset(-size.width / 6.0f, size.height / 6.0f);
		// 기존 사이즈의 3배 줄인거라, 6으로 나누면 중점임(아마)

		bm->GetTransform().SetPosition((EngineData::SceenWidth / 2.0f), 200.0f);
		//bm->GetTransform().SetPosition((EngineData::SceenWidth / 2.0f) - 330.0f, 150.0f);		
		// Y값에 대해서는 딱히 정해진 기준이 없어서, 하드코딩으로 자리잡음
		// 패널 크기는 660 * 660 정사각형임(중요)				

		render->SetActive(false);
		battleSignBitmaps.push_back(render);
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(bm, "SignBoard." + i);
	}
}

void BattleBoard::OnUpdate()
{


}

void BattleBoard::OnDestroy() {}
