#include "HitEffect.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Scene/SceneManager.h"
#include "Math/EasingFunction.h"
#include <cmath>
#include "Application/AppPaths.h"

void HitEffect::OnUpdate()
{
	float dt = Singleton<GameTime>::GetInstance().GetDeltaTime();
	for (size_t i = 0; i < AnimeList.size(); ++i) {
		auto& state = AnimeStates[i];
		if (!state.playing) continue;

		state.t += dt;
		if (state.t >= state.duration) {
			state.playing = false;
			state.t = 0.0f;

			auto* r = AnimeList[i]->GetComponent<AnimationRenderer>();
			r->SetActive(false);
			auto* p = r->GetAnimationPlayer();
			p->Pause();
			p->Reset();
		}
	}
}

void HitEffect::OnCreate()
{
	for (size_t i = 0; i < 9; i++)
	{
		GameObject* obj = new GameObject();
		obj->AddComponent<AnimationRenderer>();
		obj->SetName(std::string("HitEffect"));
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		obj->GetComponent<AnimationRenderer>()->SetActive(false);
		obj->GetComponent<AnimationRenderer>()->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Sprites\\Effect\\Hit\\hit_spreadsheet.png");
		obj->GetComponent<AnimationRenderer>()->SetSpriteSheet(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\hit\\hit_spreadsheet_sprites.json");
		obj->GetComponent<AnimationRenderer>()->SetAnimationClip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\Resource\\Json\\hit\\hit_spreadsheet_anim.json");
		obj->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->Pause();
		obj->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->SetLoop(false);
		obj->GetTransform().SetUnityCoords(false);
		AnimeList.push_back(obj);
	}

	AnimeStates.resize(AnimeList.size());
	Animeduration = AnimeList[0]->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->GetAnimationClip().duration;
}

void HitEffect::OnStart()
{
}

void HitEffect::OnDestroy()
{
}

void HitEffect::SetAnimePosition(int num, const Vector2& vector)
{
	AnimeList[num]->GetTransform().SetPosition(vector.x, vector.y);
}

void HitEffect::CallAnime(int num, Vector2 vector, float rotationValue)
{
	size_t Animesize = AnimeList.size();
	int a = 0;

	if (num >= AnimeList.size()) return;
	auto* r = AnimeList[num]->GetComponent<AnimationRenderer>();
	r->SetActive(true);
	auto* p = r->GetAnimationPlayer();
	p->Play();
	SetAnimePosition(num, vector);
	AnimeList[num]->GetTransform().SetRotation(rotationValue);

	auto& s = AnimeStates[num];
	s.playing = true;
	s.t = 0.0f;
	s.duration = Animeduration; // 슬롯마다 다르게 가능
}

void HitEffect::StopAnime(int num)
{
	if (num >= AnimeList.size()) return;
	auto& s = AnimeStates[num];
	if (!s.playing) return;

	s.playing = false;
	s.t = 0.0f;

	auto* r = AnimeList[num]->GetComponent<AnimationRenderer>();
	r->SetActive(false);
	auto* p = r->GetAnimationPlayer();
	p->Pause();
	p->Reset();
}

void HitEffect::StopAllAnime()
{
	for (size_t i = 0; i < AnimeList.size(); ++i) StopAnime(i);
}
