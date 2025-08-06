#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Datas/SoundDatas.h"
#include "Components/Logic/InputSystem.h"
#include "Components/Camera/Camera.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Component/EffectComponent.h"
#include "Utils/GameTime.h"

class TestObject : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void CheckInput();
private:
	BitmapRenderer* TestImage{};
	EffectComponent* TestEffect{};
	InputSystem* input{};

	bool eventvalue = false;
	float counttime = 0.0f;
	float maxtime = 2.0f;
	float mydeltatime;

};

