#pragma once
#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Utils/GameTime.h"
#include "Script/Manager/EffectManager.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Components/Rendering/AnimationPlayer.h"
#include "Math/Vector2.h"
#include <vector>


class Finaleffect : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void SetAnimePosition(const Vector2& vector);

	void CallAnime(float rotationValue);
	void StopAnime();

private:
	struct AnimeState {
		bool   playing = false;
		float  t = 0.0f;        // 경과 시간
		float  duration = 0.0f; // 슬롯별 지속시간
	};

	/*std::vector<AnimeState>  AnimeStates;
	std::vector<GameObject*> AnimeList;*/

	AnimeState  AnimeStates{};
	GameObject* AnimeList{};

	float Animeduration = 0.0f;
	float rot = 0.0f;
};

