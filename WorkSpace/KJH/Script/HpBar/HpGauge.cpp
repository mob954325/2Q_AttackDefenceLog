#include "HpGauge.h"
#include "Components/Base/GameObject.h"
#include "Scene/SceneManager.h"
#include "Application/AppPaths.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Utils/GameTime.h"

void HpGauge::OnUpdate()
{
	ChangeGaugeBar();
}

void HpGauge::OnCreate()
{
	owner->GetTransform().SetUnityCoords(false);
	owner->AddComponent<Slider>();
}

void HpGauge::OnStart()
{
	GameObject* obj = new GameObject();
	obj->AddComponent<Slider>();
	obj->SetName(std::string("PlayerHP"));
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	PlayerHP = obj;
	Playerslider = PlayerHP->GetComponent<Slider>();

	GameObject* obj2 = new GameObject();
	obj2->AddComponent<Slider>();
	obj2->SetName(std::string("EnemyHP"));
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj2);
	EnemyHP = obj2;
	Enemyslider = PlayerHP->GetComponent<Slider>();


	Playerslider->ButtonShow(false);
	Enemyslider->ButtonShow(false);


	Playerslider->SetGaugeBackgroundImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\UI\\HP\\hp_ui_background.png");
	Playerslider->SetGaugeBarImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\UI\\HP\\hp_ui_left.png");

	Enemyslider->SetGaugeBackgroundImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\HP\\Slider\\hp_ui_background.png");
	Enemyslider->SetGaugeBarImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\UI\\HP\\hp_ui_right.png");


	ImageMaxwidth = Playerslider->GetGaugeBarImage()->GetResource()->GetBitmap()->GetSize().width;
}

void HpGauge::OnDestroy()
{

}


void HpGauge::ChangeGaugeBar()
{
	Playerslider->ChangeGauge(PlayerValue);
	Enemyslider->ChangeGauge(EnemyValue);
}

void HpGauge::SetHpUiPosition(Vector2 player, Vector2 Enemy)
{
	PlayerHP->GetTransform().SetPosition(player.x, player.y);
	EnemyHP->GetTransform().SetPosition(Enemy.x , Enemy.y);
}

//처음 설정해줘야 하는 값
void HpGauge::SetPlayerMaxGague(float MaxGague)
{
	maxgague = MaxGague;
	PlayergaugeToPixel = ImageMaxwidth / maxgague;
}
//처음 설정해줘야 하는 값
void HpGauge::SetEnemyMaxGague(float MaxGague)
{
	maxgague = MaxGague;
	EnemygaugeToPixel = ImageMaxwidth / maxgague;
}


//저쪽에서 update로 호출해야하는 함수 ( 값을 계속 던져줘야함 )
void HpGauge::CalculatePlayerValue(float endValue)
{
	float targetRight = endValue * PlayergaugeToPixel;

	//현재 게이지의 길이
	auto it = Playerslider->GetGaugeRectValue();

	PlayerValue = (targetRight - it.right) * (Singleton<GameTime>::GetInstance().GetDeltaTime() * speed);
}

void HpGauge::CalculateEnemyValue(float endvalue)
{
	float targetRight = endvalue * EnemygaugeToPixel;

	//현재 게이지의 길이
	auto it = Enemyslider->GetGaugeRectValue();

	EnemyValue = (targetRight - it.right) * (Singleton<GameTime>::GetInstance().GetDeltaTime() * speed);
}
