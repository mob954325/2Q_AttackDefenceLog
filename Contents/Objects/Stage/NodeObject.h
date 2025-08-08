#pragma once
#include "Components/Base/MonoBehavior.h"
#include "Components/Rendering/BitmapRenderer.h"


class NodeObject : public MonoBehavior
{
public:
	void OnStart() override;
	void OnCreate() override;
	void OnUpdate() override;
	void OnDestroy() override;

	D2D1_SIZE_F GetSize() { return size; };
	bool IsOverlap();

protected:
	bool IsOverlap(float x, float y);

	D2D1_SIZE_F size;
	BitmapRenderer* bitmapRenderer{};	
	bool isOverlap = false;

	Vector2 startVec{};
	Vector2 endVec{};
};