#include "HCURSORChange.h"

using namespace Gdiplus;

HCURSORChange::HCURSORChange()
{
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);

	Status s = GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	if (s != Ok) MessageBox(0, L"GDI+ 초기화 실패", 0, 0);
}

HCURSORChange::~HCURSORChange()
{
	GdiplusShutdown(gdiplusToken);
}

HCURSOR HCURSORChange::LoadPngCursor(LPCWSTR pngPath, int xHotspot, int yHotspot)
{
	Bitmap* bitmap = Bitmap::FromFile(pngPath, FALSE);
	if (!bitmap || bitmap->GetLastStatus() != Ok)
		return nullptr;

	UINT width = bitmap->GetWidth();
	UINT height = bitmap->GetHeight();

	HBITMAP hBitmap = nullptr;
	bitmap->GetHBITMAP(Color(0, 0, 0, 0), &hBitmap); // 알파 채널 포함 HBITMAP 생성
	delete bitmap;

	if (!hBitmap)
		return nullptr;

	ICONINFO iconInfo = {};
	iconInfo.fIcon = FALSE;             // 커서 (FALSE), 아이콘이면 TRUE
	iconInfo.xHotspot = xHotspot;       // 클릭 지점 x
	iconInfo.yHotspot = yHotspot;       // 클릭 지점 y
	/*iconInfo.hbmMask = NULL;*/
	iconInfo.hbmMask = CreateBitmap(width, height, 1, 1, NULL);
	iconInfo.hbmColor = hBitmap;        // 컬러 비트맵 지정

	HCURSOR hCursor = CreateIconIndirect(&iconInfo);

	// iconInfo 구조체에 복사된 비트맵 핸들 해제
	DeleteObject(iconInfo.hbmMask);
	DeleteObject(hBitmap);

	return hCursor;
}
