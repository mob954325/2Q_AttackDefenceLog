#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

class StageEnemyProfile : public MonoBehavior
{
public:
	void OnCreate() override;
	void SetProfileImage(std::wstring str);
private:
	BitmapRenderer* enemyProfile{};
};

