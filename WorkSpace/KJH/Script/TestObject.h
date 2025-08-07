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


class TestObject : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void CheckInput();

	float GetValue(size_t type);

private:
	BitmapRenderer* TestImage{};
	InputSystem* input{};

	EffectManager* Emanager{};

	ParticleRenderer* TestParticle{};

	AnimationRenderer* AnimObject{};

	/*AnimationPlayer* AnimPlayer{};*/

	bool eventvalue = false;
	float counttime = 0.0f;
	float maxtime = 1.0f;
	float mydeltatime;

	float PI = 3.141592;

	GameObject* handleObject{};

};

