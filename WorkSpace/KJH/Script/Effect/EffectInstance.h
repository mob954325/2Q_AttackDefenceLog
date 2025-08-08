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

/*
미리 풀링으로 만들어둔 이펙트, 파티클들
*/

class EffectInstance : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void CallGuardEffect();
	void CallParryEffect();
	void CallNomalEffect();

	float GetValue(size_t type);

private:

	EffectManager* Emanager{};

	AnimationRenderer* AnimObject{};

	bool eventvalue = false;
	bool eventvalue2 = false;

	float counttime = 0.0f;
	float maxtime = 1.0f;
	float mydeltatime;

	float PI = 3.141592;

	GameObject* handleObject{};

};


