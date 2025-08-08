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
	inline void SetRadius(float value) { radius = value; }
	D2D1_SIZE_F GetSize() { return size; };

protected:
	bool isInside = false;
	bool nowInside = false;

	float radius;
	D2D1_SIZE_F size;
	BitmapRenderer* bitmapRenderer{};
};

