#include "AppPaths.h"

void AppPaths::InitPaths()
{
	wchar_t buffer[MAX_PATH];

	GetModuleFileNameW(nullptr, buffer, MAX_PATH);
	ModulePath = buffer;

	GetCurrentDirectoryW(MAX_PATH, buffer);
	WorkingPath = buffer;
}
