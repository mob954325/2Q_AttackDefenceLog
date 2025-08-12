#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Datas/SoundDatas.h"
#include "Components/Logic/InputSystem.h"
#include "Components/Camera/Camera.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Component/EffectComponent.h"
#include "Utils/GameTime.h"
#include "Script/Manager/EffectManager.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Components/Rendering/AnimationPlayer.h"
#include "Components/UI/Slider.h"
#include "Script/Effect/EffectInstance.h"
#include "Script/giseSlider/GiseGauge.h"
#include "Script/Effect/EffectMonoB.h"
#include "Script/Effect/Finaleffect.h"
#include "Script/Effect/HitEffect.h"
#include "Script/Effect/EnemyAttackEffect.h"


class TestObject : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void CheckInput();

	float GetValue(size_t type);

	/*void SetPosition();*/

private:
	EnemyAttackEffect* EATK{};
	HitEffect* HitE{};

	EffectMonoB* PAtkE{};
	Finaleffect* FinalA{};
	std::vector<float> RotationList{};
	

	GiseGauge* giseG{};

	BitmapRenderer* TestImage{};
	InputSystem* input{};

	EffectManager* Emanager{};

	ParticleRenderer* TestParticle{};

	AnimationRenderer* AnimObject{};

	/*AnimationPlayer* AnimPlayer{};*/

	bool eventvalue = false;
	bool eventvalue2 = false;
	float counttime = 0.0f;
	float maxtime = 1.0f;
	float mydeltatime;

	float PI = 3.141592;

	GameObject* handleObject{};

	EffectInstance* effectobj;

	Vector2 ObjInfo{};

	GameObject* handleCam{};

	std::vector<Vector2> positionList{};
	std::vector<Vector2> positionList2{};

	//08-11
	GameObject* ButtonAnime{};

	float x_width = 0.0f;
	float y_height = 0.0f;

	float x_pic = 0.0f;

};

