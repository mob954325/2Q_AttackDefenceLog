#include "DummyEffectAnimation.h"
#include "Components/Base/GameObject.h"
#include "Utils/GameTime.h"
#include "Utils/DebugUtility.h"
#include <iostream>

void DummyEffectAnimation::OnCreate()
{
	anim = owner->AddComponent<AnimationRenderer>(); 
	
	WCHAR buffer[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, buffer);
	std::wstring path = buffer;

	anim->CreateBitmapResource(path + L"\\..\\..\\Resource\\Particles\\Test\\attack_line_spreadsheet.png");
	anim->SetSpriteSheet(path + L"\\..\\..\\Resource\\Json\\Test_Paticles\\attack_line_spreadsheet_sprites.json");
	anim->SetAnimationClip(path + L"\\..\\..\\Resource\\Json\\Test_Paticles\\attack_line_spreadsheet_anim.json");

	// owner->GetTransform().SetRotation(-90.0f);
	anim->GetAnimationPlayer()->Pause();
}

void DummyEffectAnimation::OnStart()
{
}

void DummyEffectAnimation::OnDestroy()
{
}

void DummyEffectAnimation::OnUpdate()
{
	// DebugUtility::DebugLog("Dummy Effect Animation Update");

	//if (timer > maxTimer)
	//{
	//	owner->GetTransform().SetScale(0.0f, 0.0f);
	//	timer = 0.0f;
	//}
	//else
	//{
	//	float delta = Singleton<GameTime>::GetInstance().GetDeltaTime();
	//	float scaleValue = 3.0f;
	//	timer += delta;
	//	Vector2 scale = owner->GetTransform().GetScale();
	//	owner->GetTransform().SetScale(scale.x + delta * scaleValue, scale.y + delta * scaleValue);
	//}
}
