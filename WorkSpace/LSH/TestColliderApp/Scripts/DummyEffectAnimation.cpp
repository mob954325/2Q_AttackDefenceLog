#include "DummyEffectAnimation.h"
#include "Components/Base/GameObject.h"

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
