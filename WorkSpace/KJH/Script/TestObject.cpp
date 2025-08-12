#include "TestObject.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Scene/SceneManager.h"
#include "Math/EasingFunction.h"
#include "Script/Camera/CamInstance.h"
#include "Application/AppPaths.h"


void TestObject::OnUpdate()
{
	CheckInput();
	
	/*SetPosition();
	ButtonAnime->GetTransform().SetPosition(x_width + x_pic , 40);*/
	//if (eventvalue && counttime < maxtime)
	//{
	//	
	//	counttime += Singleton<GameTime>::GetInstance().GetDeltaTime();
	//	Emanager->SetEffectValue(0, GetValue(0), GetValue(0), 1 - GetValue(3), true);
	//	Emanager->SetEffectValue(1, GetValue(1), GetValue(1), 1 - GetValue(2), true);
	//	Emanager->SetEffectValue(2, 343 , 22, 1 -  GetValue(3), true);
	//	std::cout << counttime << std::endl;
	//
	//}
	//else if (eventvalue && counttime >= maxtime)
	//{
	//	/*TestParticle->SetLoop(false);*/
	//	Emanager->SetOffEffect();
	//	eventvalue = false;
	//}
	//
	//if (eventvalue2 && counttime < maxtime)
	//{

	//	counttime += Singleton<GameTime>::GetInstance().GetDeltaTime();
	//	Emanager->SetEffectValue(3, GetValue(1), GetValue(1), 1 - GetValue(2), true);
	//	Emanager->SetEffectValue(4, 343, 22, 1 - GetValue(3), true);
	//	std::cout << counttime << std::endl;

	//}
	//else if (eventvalue2 && counttime >= maxtime)
	//{
	//	/*TestParticle->SetLoop(false);*/
	//	Emanager->SetOffEffect();
	//	eventvalue2 = false;
	//}

	/*handleObject->GetTransform().SetPosition(owner->GetComponent<Slider>()->GetGaugeRectValue().right, owner->GetComponent<Slider>()->GetGaugeRectValue().bottom/2);*/
}

void TestObject::OnCreate()
{
	
	//owner->GetTransform().SetUnityCoords(false);
	//owner->AddComponent<Slider>();
	/*TestImage = owner->AddComponent<BitmapRenderer>();
	TestImage->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\UI\\Slider\\test.png");
	owner->GetTransform().SetOffset(-TestImage->GetResource()->GetBitmap()->GetSize().width / 2, TestImage->GetResource()->GetBitmap()->GetSize().height / 2);*/
	counttime = 0;
	input = owner->AddComponent<InputSystem>();
	/*Emanager = owner->AddComponent<EffectManager>();*/
	/*AnimObject = owner->AddComponent<AnimationRenderer>();*/
	
	effectobj = owner->AddComponent<EffectInstance>();

	


	//GameObject* Test = new GameObject();
	//Test->AddComponent<AnimationRenderer>();
	//Test->SetName("AnimeObject");
	//Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(Test);
	//handleObject = Test;

	//AnimObject = handleObject->GetComponent<AnimationRenderer>();
	
	GameObject* TempObj = new GameObject();
	TempObj->AddComponent<CamInstance>();
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(TempObj);
	handleCam = TempObj;
	handleCam->GetComponent<CamInstance>()->SetWaveValue(2.0f, 25.0f, 150.0f, 96.0f, 54.0f);

	owner->AddComponent<Finaleffect>();
	owner->AddComponent<EffectMonoB>();
	PAtkE = owner->GetComponent<EffectMonoB>();
	FinalA = owner->GetComponent<Finaleffect>();

	Vector2 A = { 800.0f , 550.0f };

	PAtkE->SetAnimePosition(A);
	FinalA->SetAnimePosition(A);

	for (int i = 0; i < 5; i++)
	{
		RotationList.push_back(20.0f + (i * 50));
	}
	
	
	owner->AddComponent<HitEffect>();
	HitE = owner->GetComponent<HitEffect>();
	owner->AddComponent<EnemyAttackEffect>();
	EATK = owner->GetComponent<EnemyAttackEffect>();

	HP = owner->AddComponent<HpGauge>();

}

//void TestObject::SetPosition()
//{
//	auto it = owner->GetComponent<Slider>();
//	x_width = it->GetGaugeRectValue().right;
//	y_height = it->GetGaugeRectValue().bottom;
//
//}

void TestObject::OnStart()
{
	/*owner->AddComponent <GiseGauge>();
	giseG = owner->GetComponent<GiseGauge>();*/
	
	//owner->GetComponent<Slider>()->ButtonShow(false);
	//owner->GetComponent<Slider>()->SetGaugeBackgroundImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\UI\\Slider\\gise_ui_white.png");
	//owner->GetComponent<Slider>()->SetGaugeBarImage(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\UI\\Slider\\gise_ui_black.png");

	//GameObject* obj = new GameObject();
	//obj->AddComponent<AnimationRenderer>();
	//obj->SetName(std::string("Button"));
	//Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);

	////obj->GetComponent<AnimationRenderer>()->SetActive(false);
	//obj->GetComponent<AnimationRenderer>()->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\UI\\Slider\\force_clash_spreadsheet.png");
	//obj->GetComponent<AnimationRenderer>()->SetSpriteSheet(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Json\\force_clash_spreadsheet_sprites.json");
	//obj->GetComponent<AnimationRenderer>()->SetAnimationClip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Json\\force_clash_anim.json");
	///*obj->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->Pause();*/
	//obj->GetComponent<AnimationRenderer>()->SetOrderInLayer(500);
	//obj->GetTransform().SetUnityCoords(false);
	//ButtonAnime = obj;
	//x_pic = 36.0f;
	

	//Emanager->CreateEffectObject(5);
	//Emanager->CreateParticleObject(2);
	////패리
	//Emanager->SetEffectImage(0, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Particles/circle_outer.png");
	//Emanager->SetEffectImage(1, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Particles/circle_inner.png");
	//Emanager->SetEffectImage(2, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Particles/line_horizon.png");
	////방어
	//Emanager->SetEffectImage(3, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Particles/defend/circle_inner.png");
	//Emanager->SetEffectImage(4, Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Particles/defend/horizon_line.png");



	//Emanager->SetLayer(0, 30);
	//Emanager->SetLayer(1, 31);
	//Emanager->SetLayer(2, 32);
	//Emanager->SetLayer(3, 33);
	//Emanager->SetLayer(4, 34);


	//
	//Emanager->GetParticleComponent(0)->SetOrderInLayer(35);
	//Emanager->GetParticleComponent(0)->SetLoop(false);
	//Emanager->GetParticleComponent(0)->SetMinSpeed(0.3f);
	//Emanager->GetParticleComponent(0)->SetMaxSpeed(0.7f);
	//Emanager->GetParticleComponent(0)->SetDuration(0.8f);
	//Emanager->GetParticleComponent(0)->SetFadeOutTime(0.7f);
	//Emanager->GetParticleComponent(0)->SetAmount(25);
	//Emanager->GetParticleComponent(0)->SetAnimPlayer(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Particles/SparkSheet.png",
	//	Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Json/SparkSheet/SparkSheet_sprites.json",
	//	Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Json/SparkSheet/Red_Spark_anim.json");
	//Emanager->GetParticleComponent(0)->SetShowType(ParticleShowType::RandomSingle);
	//Emanager->GetParticleComponent(0)->SetGravity(false);
	//Emanager->GetParticleComponent(0)->SetSeeDirection(true);
	//Emanager->GetParticleComponent(0)->SetDecreasing(true);

	//Emanager->GetParticleComponent(1)->SetOrderInLayer(35);
	//Emanager->GetParticleComponent(1)->SetLoop(false);
	//Emanager->GetParticleComponent(1)->SetMinSpeed(0.3f);
	//Emanager->GetParticleComponent(1)->SetMaxSpeed(0.7f);
	//Emanager->GetParticleComponent(1)->SetDuration(0.8f);
	//Emanager->GetParticleComponent(1)->SetFadeOutTime(0.7f);
	//Emanager->GetParticleComponent(1)->SetAmount(25);
	//Emanager->GetParticleComponent(1)->SetAnimPlayer(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Particles/defend/ParticleGuard.png",
	//	Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Json/SparkSheet/ParticleGuard_sprites.json",
	//	Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Json/SparkSheet/ParticleGuard_Guard_anim.json");
	//Emanager->GetParticleComponent(1)->SetShowType(ParticleShowType::RandomSingle);
	//Emanager->GetParticleComponent(1)->SetGravity(false);
	//Emanager->GetParticleComponent(1)->SetSeeDirection(true);
	//Emanager->GetParticleComponent(1)->SetDecreasing(true);

	//AnimObject->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Dance/Dance.png");
	//AnimObject->SetSpriteSheet(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Dance/Dance_sprites.json");
	//AnimObject->SetAnimationClip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"/../Resource/Dance/Dance_Dance_anim.json");

	//AnimObject->GetAnimationPlayer().Play();
	//AnimObject->SetOrderInLayer(15);

	/*owner->GetComponent<Slider>()->ButtonShow(false);*/




	positionList = {
	{100,-200},{400,-200},{700,-200},
	{100,100},{400,100},{700,100},
	{100,400},{400,400},{700,400}
	};

	positionList2 = {
	{300,200},{700,200},{1100,200},
	{300,400},{700,400},{1100,400},
	{300,600},{700,600},{1100,600}
	};

	Vector2 T1{ 500.0f, 500.0f };
	Vector2 T2{ 1000.0f, 500.0f };

	HP->SetHpUiPosition(T1, T2);

	effectobj->SetAnimePosition(positionList);

	EATK->SetAnimePosition(positionList2);
	/*HitE->SetAnimePosition(positionList2);*/

	// 567.0f;
	float offsetX = 0.0f;
	float offsetY = 0.0f;

	std::vector<Vector2> vec
	{
		{offsetX + 0,  offsetY},
		{offsetX + 786, offsetY},
		{offsetX + 735, offsetY + 73.0f},
		{offsetX + 55, offsetY + 73.0f}
	};

}

void TestObject::OnDestroy()
{

}


void TestObject::CheckInput()
{
	//if (input->IsKeyPressed('W'))
	//{
	//	PAtkE->CallAnime(5, RotationList);
	//}
	//if (input->IsKeyPressed('S'))
	//{
	//	FinalA->CallAnime(60.0f);
	//}

	if (input->IsKeyDown('W'))
	{
		/*giseG->ChangeGaugeBar(-1.0f);*/
		HP->ChangeGaugeBar(-1.0f);
	}
	if (input->IsKeyDown('S'))
	{
		//giseG->ChangeGaugeBar(1.0f);
		HP->ChangeGaugeBar(1.0f);
	}
	// 
	// 
	//if (input->IsKeyPressed('N'))
	//{
	//	Emanager->GetParticleComponent(0)->Reset();
	//	eventvalue = true;
	//	counttime = 0;
	//	Emanager->GetParticleComponent(0)->Play();
	//}

	//if (input->IsKeyPressed('B'))
	//{
	//	Emanager->GetParticleComponent(1)->Reset();
	//	eventvalue2 = true;
	//	counttime = 0;
	//	Emanager->GetParticleComponent(1)->Play();
	//}

	if (input->IsKeyPressed('N'))
	{
		effectobj->CallEffect(EffectType::ParryEffect ,ObjInfo);
	}

	if (input->IsKeyPressed('B'))
	{
		effectobj->CallEffect(EffectType::GuardEffect ,ObjInfo);
	}

	if (input->IsKeyPressed('0'))
	{
		effectobj->CallEffect(EffectType::ChargeEffect ,ObjInfo);
	}
	//if (input->IsKeyPressed('9'))
	//{
	//	effectobj->CallEffect(EffectType::HoldEffect, ObjInfo);
	//}


	//if (input->IsKeyPressed('5'))
	//{
	//	handleCam->GetComponent<CamInstance>()->SetSlowToFast();
	//}
	//if (input->IsKeyPressed('6'))
	//{
	//	handleCam->GetComponent<CamInstance>()->SetFastToSlow();
	//}
	//if (input->IsKeyPressed('7'))
	//{
	//	handleCam->GetComponent<CamInstance>()->SetSlowFastSlow();
	//}



	//if (input->IsKeyPressed('1'))
	//{
	//	handleCam->GetComponent<CamInstance>()->CallCamShake(ShakeType::X);
	//}
	//if (input->IsKeyPressed('2'))
	//{
	//	handleCam->GetComponent<CamInstance>()->CallCamShake(ShakeType::Y);
	//}
	//if (input->IsKeyPressed('3'))
	//{
	//	handleCam->GetComponent<CamInstance>()->CallCamShake(ShakeType::XY);
	//}
	//if (input->IsKeyPressed('4'))
	//{
	//	handleCam->GetComponent<CamInstance>()->CallCamShake(ShakeType::X_Y);
	//}



	//if (input->IsKeyDown('J'))
	//{
	//	owner->GetComponent<Slider>()->ChangeGauge(-1);
	//	owner->GetComponent<Slider>()->ChangeButtonPosition(-1);
	//	std::cout << "w 입력됨" << std::endl;
	//}
	//if (input->IsKeyDown('K'))
	//{
	//	owner->GetComponent<Slider>()->ChangeGauge(1);
	//	owner->GetComponent<Slider>()->ChangeButtonPosition(1);
	//	std::cout << "s 입력됨" << std::endl;
	//}

	if (input->IsKeyPressed('1'))
	{
		//effectobj->CallAnime(0);
		//HitE->CallAnime(0);
		//EATK->CallAnime(0);
	}
	if (input->IsKeyPressed('2'))
	{
		//effectobj->CallAnime(1);
		//HitE->CallAnime(1);
		//EATK->CallAnime(1);
	}
	if (input->IsKeyPressed('3'))
	{
		//effectobj->CallAnime(2);
		//HitE->CallAnime(2);
		//EATK->CallAnime(2);
	}
	if (input->IsKeyPressed('4'))
	{
		//effectobj->CallAnime(3);
		//HitE->CallAnime(3);
		//EATK->CallAnime(3);
	}
	if (input->IsKeyPressed('5'))
	{
		//effectobj->CallAnime(4);
		//HitE->CallAnime(4);
		//EATK->CallAnime(4);
	}
	if (input->IsKeyPressed('6'))
	{
		//effectobj->CallAnime(5);
		//HitE->CallAnime(5);
		//EATK->CallAnime(5);
	}
	if (input->IsKeyPressed('7'))
	{
		//effectobj->CallAnime(6);
		//HitE->CallAnime(6);
		//EATK->CallAnime(6);
	}
	if (input->IsKeyPressed('8'))
	{
		//effectobj->CallAnime(7);
		//HitE->CallAnime(7);
		//EATK->CallAnime(7);
	}
	if (input->IsKeyPressed('9'))
	{
		//effectobj->CallAnime(8);
		//HitE->CallAnime(8);
		//EATK->CallAnime(8);
	}
}



float TestObject::GetValue(size_t type)
{
	switch (type)
	{
		
	case 0:
	{
		float circle_outer = EasingList[EasingEffect::OutExpo](counttime);
		return circle_outer * 189;
		break;
	}
	case 1:
	{
		float circle_inner = EasingList[EasingEffect::OutExpo](counttime);
		return circle_inner * 302;
		break;
	}

	case 2:
	{
		float Capacity = EasingList[EasingEffect::InExpo](counttime);
		return Capacity;
		break;
	}
	case 3:
	{
		float line_horizon = EasingList[EasingEffect::OutExpo](counttime);
		/*return sin(line_horizon * PI)* 343.0f;*/
		/*return line_horizon * 343.0f;*/
		return line_horizon;
		break;
	}
	}
}


