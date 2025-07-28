#pragma once
#include "Datas/SpriteDatas.h"
#include "Datas/AnimationDatas.h"
#include "BitmapRenderer.h"

// 

class AnimationRenderer : public BitmapRenderer
{
public:
	void Render(D2DRenderManager* manager) override;

	/// <summary>
	/// SpriteSheet json 파일 찾기
	/// </summary>
	/// <param name="filePath">파일 경로</param>
	void SetSpriteSheet(std::wstring filePath);

	/// <summary>
	/// AnimationClip json 파일 찾기
	/// </summary>
	/// <param name="filePath">파일 경로</param>
	void SetAnimationClip(std::wstring filePath);

	int GetFrame() { return frameIndex; }

	void Play() { isPlay = true; }
	void Stop() { isPlay = false; }

private:
	SpriteSheet sheet{};
	AnimationClip clip{};

	D2D1_RECT_F srcRect{};

	bool isPlay = false;

	int frameIndex = 0;
	int maxFrameIndex = 1;

	float frameTimer = 0.0f;
	float maxFrameTimer = 0.0f;
};

/// 유니티 SpriteEditor 좌표
///	(0,y) +-----------------+ (x, y)
///		  |                 |
///		  |                 |
///		  |                 |
///		  |                 |
///		  |                 |
///		  |                 |
/// (0,0) +-----------------+ (x, 0)
