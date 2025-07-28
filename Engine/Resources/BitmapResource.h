#pragma once
#include "pch.h"

/// <summary>
/// 비트맵 데이터 클래스
/// </summary>
class BitmapResource
{
public:

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> GetBitmap();
	void SetBitmap(ID2D1Bitmap1** pBitmap);

protected:
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap;	
};

