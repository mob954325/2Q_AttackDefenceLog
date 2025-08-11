#include "GiseGauge.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Utils/GameTime.h"

void GiseGauge::OnUpdate()
{
	ChangeGaugeBar();
	SetAnimePosition();
	ButtonAnime->GetTransform().SetPosition(x_width + x_pic/2, 38.1f);
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
	sliderobj->ChangeGauge(-(currentgague/2));


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
	/*x_pic = 36.0f;*/
	auto it = obj->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->GetSpriteSheet();
	x_pic = it.sprites[0].width;
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
