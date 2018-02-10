#pragma once
#include "Utils.h"
void CUtils::Print(const char* fmt, ...)
{
	if (!fmt) return;

	va_list va_alist;
	char logBuf[256] = { 0 };

	va_start(va_alist, fmt);
	_vsnprintf(logBuf + strlen(logBuf), sizeof(logBuf) - strlen(logBuf), fmt, va_alist);
	va_end(va_alist);

	if (logBuf[0] != '\0')
	{
		printf(" %s\n", logBuf);
	}
}

bool CUtils::SyncUser()
{
	DWORD Massas = 1614687067;
	DWORD Spy = 1213810804;
	DWORD Twist = -1332106907;

	DWORD Serial;
	LPCTSTR HardDrive = "C:\\";

	GetVolumeInformation(HardDrive, NULL, 255, &Serial, NULL, NULL, NULL, 255);

	if (Serial == Massas || Serial == Spy || Serial == Twist)
		return true;
	else
		return false;
}

DWORD CUtils::FindPatternIDA(std::string moduleName, std::string pattern)
{
	const char* pat = pattern.c_str();
	DWORD firstMatch = 0;
	DWORD rangeStart = (DWORD)GetModuleHandleA(moduleName.c_str());
	MODULEINFO miModInfo;
	K32GetModuleInformation(GetCurrentProcess(), (HMODULE)rangeStart, &miModInfo, sizeof(MODULEINFO));
	DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
	for (DWORD pCur = rangeStart; pCur < rangeEnd; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else
				pat += 2; //one ?
		}
		else
		{
			pat = pattern.c_str();
			firstMatch = 0;
		}
	}

	Print("Bad pattern: '%s' in '%s'", pattern, moduleName.c_str());
	return NULL;
}