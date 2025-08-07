#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Datas/SoundDatas.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Script/EffectObject.h"
#include "Components/Rendering/ParticleRenderer.h"

class EffectManager : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void SetEffectPosition(float x, float y);

	void SetEffectImage(size_t value, std::wstring path);
	void SetEffectValue(size_t value, float width, float height, float capacityvalue, bool checkend);

	void CreateEffectObject(size_t value);
	
	void CreateParticleObject();

	void SetOffEffect();

	ParticleRenderer* GetParticleComponent();



private:
	std::vector<GameObject*> effectList;
	GameObject* particleObj;
};

