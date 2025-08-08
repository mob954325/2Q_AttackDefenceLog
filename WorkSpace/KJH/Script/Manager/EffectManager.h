#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Datas/SoundDatas.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Script/EffectObject.h"
#include "Components/Rendering/ParticleRenderer.h"

/*
25.08.07 | 작성자 : 김정현
effect, particle들을 생성, 값설정을 해주는 매니저
사용자는 Manager만 component로 들고있으면 이펙트 생성 및 원하는 위치에 생성 가능
SetEffectPosition는 이펙트, 파티클들을 원하는 위치에서 나오도록 셋팅하는 함수
void CreateEffectObject(size_t value); 에서 생성할 파티클갯수를 적음 ( 해당 Scene에서 사용할 모든 이펙트 생성 )
이펙트 이미지를 넣을때 index를 사용자가 원하는 순서대로 넣을수 있음 ( 이때 5개 생성했는데 SetEffectImage에 5이상의 수를 넣으면 오류 )
파티클의 경우 매니저가 이미지를 넣는게 아니라 반환하는 GetParticleComponent를 사용해서 값설정
사용자가 넣은 이미지 index 기준으로 크기(상하좌우길이) , 투명도, on/off 매개변수로 전달 가능
한번에 모든 이펙트 끄는 함수 존재 SetOffEffect()
*/

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
	
	void CreateParticleObject(size_t value);

	void SetOffEffect();

	void SetLayer(int index, int value);

	void SetUnityValue(bool value);

	ParticleRenderer* GetParticleComponent(size_t index);



private:
	std::vector<GameObject*> effectList;
	std::vector<GameObject*> particleList;
};

