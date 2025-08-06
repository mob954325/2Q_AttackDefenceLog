#pragma once
#include "Components/Logic/ScriptComponent.h"
#include "Datas/SpriteDatas.h"
#include "Resources/BitmapResource.h"

class EffectComponent : public ScriptComponent
{
public :
	void OnCreate() override;
	void OnStart() override;
	void OnDestroy() override;
	void Update() override;

private:
	SpriteSheet SpriteData;

};

