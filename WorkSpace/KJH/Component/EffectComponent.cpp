#include "EffectComponent.h"
#include "Resources/Loaders/SpriteSheetLoader.h"

void EffectComponent::OnCreate()
{
	SpriteSheetLoader::LoadSpriteSheet(L"../../Resource/Particles/effectsheet.png", SpriteData);
}

void EffectComponent::OnStart()
{

}

void EffectComponent::OnDestroy()
{

}

void EffectComponent::Update()
{

}
