#pragma once
#include "Components/Base/MonoBehavior.h"
#include "SliceableMenu.h"
#include "Components/Rendering/BitmapRenderer.h"

class EscMenuBar : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;

private:
	void CreateMenuObjects();

	BitmapRenderer* br;
	std::vector<SliceableMenu*> objs; // continueObject, exitObject, soundObject
	float width = 500.0f;
	float gap = 50.0f;
};

