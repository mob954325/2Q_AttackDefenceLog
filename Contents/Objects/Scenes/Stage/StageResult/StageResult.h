#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

enum ResultPanelState
{
	None = 0,
	Win,
	Defeat
};

class StageResult : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

	void SetPanelState(ResultPanelState state);

private:
	BitmapRenderer* winPanel;
	BitmapRenderer* winMark;

	BitmapRenderer* defeatPanel;
	BitmapRenderer* defeatMark;

	bool isSoundPlay = false;
	
	float timer = 0.0f;

};