#include "EffectMonoB.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Scene/SceneManager.h"
#include "Math/EasingFunction.h"
#include <cmath>
#include "Application/AppPaths.h"

void EffectMonoB::OnUpdate()
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

void EffectMonoB::OnCreate()
{
	for (size_t i = 0; i < 9; i++)
	{
		GameObject* obj = new GameObject();
		obj->AddComponent<AnimationRenderer>();
		obj->SetName(std::string("PlayerAttack") + std::to_string(i));
		Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
		obj->GetComponent<AnimationRenderer>()->SetActive(false);
		obj->GetComponent<AnimationRenderer>()->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Particles\\PlayerAttack\\enemy_attack_line_spreadsheet.png");
		obj->GetComponent<AnimationRenderer>()->SetSpriteSheet(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Json\\enemy_attack_line_spreadsheet_sprites.json");
		obj->GetComponent<AnimationRenderer>()->SetAnimationClip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Json\\enemy_attack_line_spreadsheet_anim.json");
		obj->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->Pause();
		AnimeList.push_back(obj);
	}

	AnimeStates.resize(AnimeList.size());

	Animeduration = AnimeList[0]->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->GetAnimationClip().duration;

}

void EffectMonoB::OnStart()
{

}

void EffectMonoB::OnDestroy()
{
}

void EffectMonoB::SetAnimePosition(const Vector2& vector)
{
	for (size_t i = 0; i < 9; i++)
	{
		AnimeList[i]->GetTransform().SetPosition(vector.x, vector.y);
	}
}

void EffectMonoB::CallAnime(int num , const std::vector<float>& rotationValue)
{
	if (num >= AnimeList.size()) return;
	for (int i = 0; i < num; i++)
	{
		auto* r = AnimeList[i]->GetComponent<AnimationRenderer>();
		r->SetActive(true);
		auto* p = r->GetAnimationPlayer();
		p->Play();

		auto t = AnimeList[i]->GetTransform();
		t.SetRotation(rotationValue[i]);

		auto& s = AnimeStates[i];
		s.playing = true;
		s.t = 0.0f;
		s.duration = Animeduration; // 슬롯마다 다르게 가능
	}
}

void EffectMonoB::StopAnime(int num)
{
	if (num >= AnimeList.size()) return;
	
	for (int i = 0; i < num; i++)
	{
		auto& s = AnimeStates[i];
		/*if (!s.playing) return;*/

		s.playing = false;
		s.t = 0.0f;

		auto t = AnimeList[i]->GetTransform();
		t.SetRotation(0.0f);
		auto* r = AnimeList[i]->GetComponent<AnimationRenderer>();
		r->SetActive(false);
		auto* p = r->GetAnimationPlayer();
		p->Pause();
		p->Reset();
	}
}


void EffectMonoB::StopAllAnime()
{
	for (size_t i = 0; i < AnimeList.size(); ++i) StopAnime(i);
}