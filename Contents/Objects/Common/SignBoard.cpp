#include "SignBoard.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "../Engine/Utils/GameTime.h"


void SignBoard::OnStart()
{
	//"C:\Users\A\Documents\GitHub\Kyu\\..\\Resource\UI\Sign\bottom_text.png"
	std::wstring path = Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Sign\\";
	std::wstring files[] =
	{ L"top_text.png", L"mid_text.png", L"bottom_text.png", L"defence_text.png", L"parrying_text.png" };

	/*	HighAttackSign = 0,
		MiddleAttackSign = 1,
		LowAttackSign = 2,
		GuardSign = 3,
		ParrySign = 4*/

	for (int i = 0; i < std::size(files); ++i) {
		GameObject* bm = new GameObject();
		bm->SetRenderLayer(EngineData::RenderLayer::UI);
		auto render = bm->AddComponent<BitmapRenderer>();
		render->CreateBitmapResource(path + files[i]);
		render->SetOrderInLayer(-7); // 패널이 -8이던데				
		bm->GetTransform().SetUnityCoords(false);

		D2D1_SIZE_F size = render->GetResource()->GetBitmap()->GetSize();
		D2D1_RECT_F dest = { 0,0,size.width / 3.0f,size.height / 3.0f };
		D2D1_RECT_F src = { 0,0,size.width ,size.height };

		render->SetUseCustomRect(true);
		render->SetDestRect(dest);
		render->SetSrcRect(src);

		bm->GetTransform().SetPosition((EngineData::SceenWidth / 2.0f) - size.width / 6.0f, 150.0f);

		render->SetActive(false);
		signBitmaps.push_back(render);
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(bm);
	}	
}

void SignBoard::OnUpdate()
{
	if (!isPlay) return;
	

	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();

	progress -= 0.6f * delta;

	signBitmaps[type]->SetCapacity(progress);

	if (progress <= 0.0f) {
		isPlay = false;
		progress = 0.0f;
		ClearAllSigns();
	}
	

}

void SignBoard::OnDestroy() {}

//================================================

void SignBoard::ShowHighSign()
{
	ClearAllSigns();
	isPlay = true;
	progress = 1.0f;
	type = HighAttackSign;
	signBitmaps[type]->SetActive(true);	
}

void SignBoard::ShowMiddleSign()
{
	ClearAllSigns();
	isPlay = true;
	progress = 1.0f;
	type = MiddleAttackSign;
	signBitmaps[type]->SetActive(true);	
}

void SignBoard::ShowLowSign()
{
	ClearAllSigns();
	isPlay = true;
	progress = 1.0f;
	type = LowAttackSign;
	signBitmaps[type]->SetActive(true);
}

//================================================

void SignBoard::ShowParrySign()
{
	ClearAllSigns();
	isPlay = true;
	progress = 1.0f;
	type = ParrySign;
	signBitmaps[type]->SetActive(true);	
}

void SignBoard::ShowGuardSign()
{
	ClearAllSigns();
	isPlay = true;
	progress = 1.0f;
	type = GuardSign;
	signBitmaps[GuardSign]->SetActive(true);
}

//================================================

void SignBoard::ClearAllSigns()
{
	for (int i = 0; i < signBitmaps.size(); ++i) {
		signBitmaps[i]->SetActive(false);
	}	
}


