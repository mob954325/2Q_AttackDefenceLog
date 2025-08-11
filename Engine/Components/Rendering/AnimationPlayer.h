#pragma once
#include "Resources/BitmapResource.h"
#include "Datas/SpriteDatas.h"
#include "Datas/AnimationDatas.h"

/* 07.31 | 작성자 : 이성호
	 : 스프라이트 애니메이션 처리 모듈화 클래스

*/

class AnimationPlayer
{
public:
	void Update(float delta);	// 애니메이션 index 업데이트
	D2D1_RECT_F GetDestRect() const;
	D2D1_RECT_F GetSrcRect() const;

	void SetBitmapResource(const BitmapResource& resource);
	BitmapResource& GetBitmapResource();
	void SetSpriteSheet(std::wstring path);
	SpriteSheet GetSpriteSheet();
	void SetAnimationClip(std::wstring path); // Sheet 정보가 있어야 로드 가능
	AnimationClip GetAnimationClip();



	void SetLoop(bool value);

	void SetCurrentFrame(int index);
	int GetCurrentFrame() const;

	int GetMaxFrame() const;

	
	

	void Play();
	void Pause();
	void Reset(); // 애니메이션 초기화, 데이터 초기화가 아님
private:
	BitmapResource resource{};
	SpriteSheet sheet{};
	AnimationClip clip{};

	float timer = 0;
	int currentFrameIndex = 0;
	int maxFrameIndex = 0;

	bool isPlay = true;
	bool isLoop = false;
};

