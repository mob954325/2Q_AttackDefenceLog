#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
//#include "Component/EffectComponent.h"
#include "Utils/GameTime.h"
#include "Script/Manager/EffectManager.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Components/Rendering/AnimationPlayer.h"
#include "Math/Vector2.h"
#include <vector>

class EffectMonoB : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void SetAnimePosition(const Vector2& vector);

	void CallAnime(int num , const std::vector<float>& rotationValue);
	void StopAnime(int num);
	void StopAllAnime();

private:


	//각 애니메이션을 관리하기위한 struct
	struct AnimeState {
		bool   playing = false;
		float  t = 0.0f;        // 경과 시간
		float  duration = 0.0f; // 슬롯별 지속시간
	};

	//그것을 담는 백터
	std::vector<AnimeState>  AnimeStates;
	std::vector<GameObject*> AnimeList;

	float Animeduration = 0.0f;
};

