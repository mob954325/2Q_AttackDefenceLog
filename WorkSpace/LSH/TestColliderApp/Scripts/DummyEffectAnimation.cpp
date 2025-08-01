#include "DummyEffectAnimation.h"
#include "Components/Base/GameObject.h"
#include "Utils/GameTime.h"

void DummyEffectAnimation::OnCreate()
{
	anim = owner->AddComponent<AnimationRenderer>();
	anim->CreateBitmapResource(L"../../Resource/Particles/Test/FireEffectSheet.png");
	anim->SetSpriteSheet(L"../../Resource/Json/Test_Paticles/FireEffectSheet.json");
	anim->SetAnimationClip(L"../../Resource/Json/Test_Paticles/Fire_Hanabi_anim.json");
}

void DummyEffectAnimation::OnStart()
{
}

void DummyEffectAnimation::OnDestroy()
{
}

void DummyEffectAnimation::OnUpdate()
{
	if (timer > maxTimer)
	{
		owner->GetTransform().SetScale(0.0f, 0.0f);
		timer = 0.0f;
	}
	else
	{
		float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();
		float scaleValue = 3.0f;
		timer += delta;
		Vector2 scale = owner->GetTransform().GetScale();
		owner->GetTransform().SetScale(scale.x + delta * scaleValue, scale.y + delta * scaleValue);
	}
}
