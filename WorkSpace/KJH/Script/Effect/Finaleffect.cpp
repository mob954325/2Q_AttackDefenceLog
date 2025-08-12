#include "Finaleffect.h"
#include "Components/Base/GameObject.h"
#include <iostream>
#include "Systems/AudioSystem.h"
#include "Components/Camera/CameraManager.h"
#include "Scene/SceneManager.h"
#include "Math/EasingFunction.h"
#include <cmath>
#include "Application/AppPaths.h"

void Finaleffect::OnUpdate()
{
	float dt = Singleton<GameTime>::GetInstance().GetDeltaTime();
		auto& state = AnimeStates;
		if (!state.playing) return;

		state.t += dt;
		if (state.t >= state.duration) {
			state.playing = false;
			state.t = 0.0f;

			auto* r = AnimeList->GetComponent<AnimationRenderer>();
			r->SetActive(false);
			auto* p = r->GetAnimationPlayer();
			p->Pause();
		}
}

void Finaleffect::OnCreate()
{
	GameObject* obj = new GameObject();
	obj->AddComponent<AnimationRenderer>();
	obj->SetName(std::string("FinalAttack"));
	Singleton<SceneManager>::GetInstance().GetCurrentScene()->AddGameObject(obj);
	obj->GetComponent<AnimationRenderer>()->SetActive(false);
	obj->GetComponent<AnimationRenderer>()->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Particles\\Final\\final_blow_line_spreadsheet.png");
	obj->GetComponent<AnimationRenderer>()->SetSpriteSheet(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Json\\final_blow_line_spreadsheet_sprites.json");
	obj->GetComponent<AnimationRenderer>()->SetAnimationClip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Json\\final_blow_line_spreadsheet_anim.json");
	obj->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->Pause();
	obj->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->SetLoop(false);
	obj->GetTransform().SetUnityCoords(false);
	AnimeList = obj;

	Animeduration = AnimeList->GetComponent<AnimationRenderer>()->GetAnimationPlayer()->GetAnimationClip().duration;
}

void Finaleffect::OnStart()
{
}

void Finaleffect::OnDestroy()
{
}

void Finaleffect::SetAnimePosition(const Vector2& vector)
{
	AnimeList->GetTransform().SetPosition(vector.x, vector.y);
}

void Finaleffect::CallAnime(float rotationValue)
{
	if (AnimeList == nullptr) return;
	auto* r = AnimeList->GetComponent<AnimationRenderer>();
	r->SetActive(true);
	r->GetAnimationPlayer()->Reset();
	r->GetAnimationPlayer()->Play();

	AnimeList->GetTransform().SetRotation(rotationValue);

	auto& s = AnimeStates;
	s.playing = true;
	s.t = 0.0f;
	s.duration = Animeduration; // 슬롯마다 다르게 가능
}

void Finaleffect::StopAnime()
{
	if (AnimeList == nullptr) return;
	auto& s = AnimeStates;
	/*if (!s.playing) return;*/

	s.playing = false;
	s.t = 0.0f;

	auto t = AnimeList->GetTransform();
	t.SetRotation(0.0f);
	auto* r = AnimeList->GetComponent<AnimationRenderer>();
	r->SetActive(false);
	auto* p = r->GetAnimationPlayer();
	p->Pause();
	p->Reset();
}



