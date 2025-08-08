#pragma once
#include "Components/Rendering/RenderComponent.h"
#include "Platform/D2DRenderManager.h"
#include "Resources/BitmapResource.h"
#include <array>

struct SliceEffectPiece {
	D2D1_RECT_F rect;   // 프레임 내부 로컬 src (px)
	float angle;
	Vector2 pos;
	float length;
};

class AnimatedChainEffect : public RenderComponent {
public:
	void OnStart() override;
	void OnCreate() override;
	void Render(D2DRenderManager* manager) override;

	void SetAtlasStrip(std::wstring path, int maxF);
	void SetupNodes(Vector2 center, float interval);
	void PlayOnce(const std::vector<int>& pattern);

	void SliceRect(const std::vector<int>& pattern);
	void Draw(D2DRenderManager* manager);
private:
	std::shared_ptr<BitmapResource> atlasBitmap;
	std::array<Vector2, 9> positions{};
	std::vector<SliceEffectPiece> pieces;

	float timer = 0.0f;
	float frameW = 0.0f;
	float frameH = 0.0f;

	int currentFrame = 0;
	int maxFrame = 0;

	bool  isPlaying = false;

	D2D1_SIZE_F size;
};
