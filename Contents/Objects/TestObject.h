#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Components/Rendering/AnimationRenderer.h"

class TestObject : public MonoBehavior
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;
	D2D1_SIZE_F GetSize() { return size; };
	void Test() {
		//¾Æ.
		//
	}


protected: 
	D2D1_SIZE_F size;
	BitmapRenderer* bitmapRenderer{};
	std::shared_ptr<BitmapResource> testImg = nullptr;

	AnimationRenderer* anim{};
};

