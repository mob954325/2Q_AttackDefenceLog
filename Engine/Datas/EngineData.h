#pragma once
#include "pch.h"

namespace EngineData
{
	const static std::wstring WindowName = L"WindowClass";
	const static std::wstring TitleName = L"DirectX11 2D Physics Test";

 	static int SceenHeight = 1080;
	static int SceenWidth = 1920;

	/// <summary>
	/// 랜더링 레이어 enum ( 숫자가 낮을 수록 먼저 렌더링됨 )
	/// </summary>
	enum RenderLayer
	{
		None = 0,
		GameObject,
		Player,
		UI,
		LayerCount
	};
}