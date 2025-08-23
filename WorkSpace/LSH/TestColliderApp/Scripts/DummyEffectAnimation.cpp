#include "DummyEffectAnimation.h"
#include "Components/Base/GameObject.h"
#include "Utils/GameTime.h"
#include "Utils/DebugUtility.h"
#include "Application/AppPaths.h"
#include "Platform/Input.h"

void DummyEffectAnimation::OnCreate()
{
	anim = owner->AddComponent<AnimationRenderer>();
	anim->CreateBitmapResource(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Particles\\defenceplayer\\defence_player_enemy_spreadsheet.png");
	anim->SetSpriteSheet(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Json\\defence\\defence_player_enemy_spreadsheet_sprites.json");
	anim->SetAnimationClip(Singleton<AppPaths>::GetInstance().GetWorkingPath() + L"\\..\\..\\Resource\\Json\\defence\\defence_player_enemy_spreadsheet_anim.json");

	// owner->GetTransform().SetRotation(-90.0f);
	anim->GetAnimationPlayer()->Pause();
	anim->GetAnimationPlayer()->Play();
	anim->GetAnimationPlayer()->SetLoop(false);
}

void DummyEffectAnimation::OnStart()
{
}

void DummyEffectAnimation::OnDestroy()
{
}

void DummyEffectAnimation::OnUpdate()
{
	if (Input::leftButtonDown)
	{
		anim->GetAnimationPlayer()->Reset();
		anim->GetAnimationPlayer()->Play();
	}
	if (Input::rightButtonDown)
	{
		anim->GetAnimationPlayer()->Pause();
	}
}
