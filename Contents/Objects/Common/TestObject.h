#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"
#include "Components/Rendering/AnimationRenderer.h"

class TestObject : public MonoBehavior
{
public:
	void OnCreate() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;
	D2D1_SIZE_F GetSize() { return size; };
	void Test() {
		//아.
		//이 오브젝트를 봤다면 희망을 버려라 아쎄이!
		//이 오브젝트에 선언된 비트맵은 이세상에 존재하지 않는다!
	}


protected: 
	D2D1_SIZE_F size;
	BitmapRenderer* bitmapRenderer{};
	std::shared_ptr<BitmapResource> testImg = nullptr;

	AnimationRenderer* anim{};
};

