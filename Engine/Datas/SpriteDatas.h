#pragma once
#include "pch.h"
#include <unordered_map>

struct Sprite
{
	std::wstring name = L""; // sprite 이름
	float x, y;				 // sprite 좌표 ( sourceRect 위치 값으로 추정 )
	float width, height;	 // sprite 너비
	float pivotX, pivotY;	 // sprite 피벗 ( 중심점 )
};

struct SpriteSheet 
{
	std::wstring texture = L"";			// 해당 시트 이름
	float textureWidth, textureHeight;	// 해당 시트 너비와 높이
	std::vector<Sprite> sprites;		// 시트에 있는 Sprite 목록
	std::unordered_map<std::wstring, int> spriteIndexMap;	// std::wstring으로 찾기 위한 인덱스 맵 <이름, 인덱스>
};