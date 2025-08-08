#pragma once
#include "Datas/SpriteDatas.h"
#include "Datas/AnimationDatas.h"
#include "BitmapRenderer.h"
#include "Components/Rendering/AnimationPlayer.h"

// 

class AnimationRenderer : public BitmapRenderer
{
public:
	void Render(D2DRenderManager* manager) override;

	void CreateBitmapResource(std::wstring filePath);

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

	AnimationPlayer* GetAnimationPlayer();

private:
	AnimationPlayer player;
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
