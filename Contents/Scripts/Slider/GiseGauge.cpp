#include "GiseGauge.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Utils/GameTime.h"
#include "../Engine/Datas/EngineData.h"

void GiseGauge::OnUpdate()
{
	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();
	ChangeGaugeBar();
	SetAnimePosition();
	ButtonAnime->GetTransform().SetPosition(EngineData::SceenWidth / 2 - currentgague / 2 + x_width + x_pic / 2, 38.1f);
	ButtonCover->GetTransform().SetPosition(EngineData::SceenWidth / 2 - currentgague / 2 + x_width - coverX / 2, 0);

	if (blackAlpha > 0.0f) {
		blackAlpha -= delta * 0.5f;
		if (blackAlpha < 0.0f) blackAlpha = 0.0f;
		blackEffect->SetCapacity(blackAlpha);
	}

	if (whiteAlpha > 0.0f) {
		whiteAlpha -= delta * 0.5f;
		if (whiteAlpha < 0.0f) whiteAlpha = 0.0f;		
		whiteEffect->SetCapacity(whiteAlpha);
	}

}

void GiseGauge::OnCreate()
{
	owner->GetTransform().SetUnityCoords(false);
	owner->AddComponent<Slider>();
}

void GiseGauge::OnStart()
{

	sliderobj = owner->GetComponent<Slider>();
	sliderobj->ButtonShow(false);
	sliderobj->SetGaugeBackgroundImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Slider\\gise_ui_white.png");
	sliderobj->SetGaugeBarImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Slider\\gise_ui_black.png");


	currentgague = sliderobj->GetGaugeBarImage()->GetResource()->GetBitmap()->GetSize().width;
	sliderobj->ChangeGauge(-(currentgague / 2));


	GameObject* obj = new GameObject();
	obj->AddComponent<AnimationRenderer>();
	obj->SetName(std::string("Button"));
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);

	obj->GetComponent<AnimationRenderer>()->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Slider\\force_clash_spreadsheet.png");
	obj->GetComponent<AnimationRenderer>()->SetSpriteSheet(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\force_clash_spreadsheet_sprites.json");
	obj->GetComponent<AnimationRenderer>()->SetAnimationClip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\force_clash_spreadsheet_anim.json");
	obj->GetComponent<AnimationRenderer>()->SetOrderInLayer(500);
	obj->GetTransform().SetUnityCoords(false);
	ButtonAnime = obj;

	GameObject* obj2 = new GameObject();
	obj2->AddComponent<BitmapRenderer>();
	obj2->SetName(std::string("Buttoncover"));
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj2);
	obj2->GetTransform().SetUnityCoords(false);
	ButtonCover = obj2;
	ButtonCover->GetComponent<BitmapRenderer>()->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Slider\\gise_ui_cover.png");
	ButtonCover->GetComponent<BitmapRenderer>()->SetOrderInLayer(600);
	coverX = ButtonCover->GetComponent<BitmapRenderer>()->GetResource()->GetBitmap()->GetSize().width;


	auto it = obj->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->GetSpriteSheet();
	x_pic = it.sprites[0].width;

	owner->GetTransform().SetPosition((EngineData::SceenWidth - currentgague) / 2.0f, 0.0f);

	float offsetX = 567.0f;
	float offsetY = 0.0f;

	std::vector<Vector2> vec
	{
		{offsetX + 0,  offsetY},
		{offsetX + 786, offsetY},
		{offsetX + 735, offsetY + 73.0f},
		{offsetX + 55, offsetY + 73.0f}
	};
	ButtonAnime->GetComponent<AnimationRenderer>()->SetClipingPosition(vec);
	ButtonCover->GetComponent<BitmapRenderer>()->SetClipingPosition(vec);

	//게이지바 위에 나타날 뭐시깽 ============================== 8.13. 추가
	GameObject* blackEff = new GameObject();
	blackEff->SetRenderLayer(EngineData::RenderLayer::UI);
	blackEff->GetTransform().SetUnityCoords(false);

	blackEffect = blackEff->AddComponent<BitmapRenderer>();
	blackEffect->SetOrderInLayer(1000);
	blackEffect->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Slider\\force_destroy_black.png");
	blackEffect->SetCapacity(0.0f);


	auto bSize = blackEffect->GetResource()->GetBitmap()->GetSize();
	blackEff->GetTransform().SetPosition((EngineData::SceenWidth - bSize.width) / 2.0f, -bSize.height / 2.0f);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(blackEff);

	GameObject* whiteEff = new GameObject();
	whiteEff->SetRenderLayer(EngineData::RenderLayer::UI);
	whiteEff->GetTransform().SetUnityCoords(false);

	whiteEffect = whiteEff->AddComponent<BitmapRenderer>();
	whiteEffect->SetOrderInLayer(1000);
	whiteEffect->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\UI\\Slider\\force_destroy_white.png");
	whiteEffect->SetCapacity(0.0f);

	auto wSize = whiteEffect->GetResource()->GetBitmap()->GetSize();
	whiteEff->GetTransform().SetPosition((EngineData::SceenWidth - wSize.width) / 2.0f, -wSize.height / 2.0f);
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(whiteEff);
}

void GiseGauge::OnDestroy()
{

}

void GiseGauge::SetAnimePosition()
{
	x_width = sliderobj->GetGaugeRectValue().right;
	y_height = sliderobj->GetGaugeRectValue().bottom;
}

void GiseGauge::ChangeGaugeBar()
{
	sliderobj->ChangeGauge(X_Value);
}

//처음 설정해줘야 하는 값
void GiseGauge::SetMaxGague(float MaxGague)
{
	maxgague = MaxGague;
	gaugeToPixel = currentgague / maxgague;
}

//저쪽에서 update로 호출해야하는 함수 ( 값을 계속 던져줘야함 )
void GiseGauge::CalculateValue(float endValue)
{
	float targetRight = endValue * gaugeToPixel;

	//현재 게이지의 길이
	auto it = sliderobj->GetGaugeRectValue();

	X_Value = (targetRight - it.right) * (Singleton<GameTime>::GetInstance().GetDeltaTime() * speed);
}
