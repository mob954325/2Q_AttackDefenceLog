#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Utils/GameTime.h"
#include "../Contents/Scripts/Effect/EffectManager.h"
#include "Components/Rendering/AnimationRenderer.h"
#include "Components/Rendering/AnimationPlayer.h"
#include "Math/Vector2.h"
#include <vector>
class EnemyAttackEffect : public MonoBehavior
{
public:
	void OnUpdate() override;
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;

	void SetAnimePosition(const std::vector<Vector2>& vectorList);

	void CallAnime(int num);
	void StopAnime(int num);
	void StopAllAnime();

private:
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

