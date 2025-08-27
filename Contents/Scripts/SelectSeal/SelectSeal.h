#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"

class SelectSeal : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;

private:
	BitmapRenderer* left;
	BitmapRenderer* right;

	float timer = 0.0f;
	float maxTimer = 0.8f;

	float readyTimer = 4.0f; //8.28.추가, 연출 조정해줄려고 임의로 만듬
	bool go = false; //상남자 작명법
	
	bool isRighDone = false;
};

