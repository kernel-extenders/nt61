#include <Windows.h>
#include "ntdll.h"

WINBASEAPI BOOL WINAPI GetVersionExW(LPOSVERSIONINFOW verInfo) {
	LPWSTR path;
	LPOSVERSIONINFOEXW ver;
	PPEB peb;
	PKUSER_SHARED_DATA sharedData;
	UINT path_majorversion;
	UINT path_minorversion;
	UINT path_buildnumber;
	UINT path_platformid;
	//LPWSTR path_csdversion[128];
	UINT global_majorversion;
	UINT global_minorversion;
	UINT global_buildnumber;
	UINT global_platformid;
	//LPWSTR global_csdversion[128];
	peb = NtCurrentPeb();
	ver = (LPOSVERSIONINFOEXW) verInfo;
	path = peb->ProcessParameters->ImagePathName.Buffer;
	sharedData = (PKUSER_SHARED_DATA)0x7FFE0000;
	if(verInfo->dwOSVersionInfoSize != sizeof(OSVERSIONINFOW) && verInfo->dwOSVersionInfoSize != sizeof(OSVERSIONINFOEXW)) {
		SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}
	if(GetPrivateProfileIntW(peb->ProcessParameters->ImagePathName.Buffer, L"Enabled", 0, L"osver.ini")) {
		path_majorversion = GetPrivateProfileIntW(path, L"MajorVersion", peb->OSMajorVersion, L"osver.ini");
		path_minorversion = GetPrivateProfileIntW(path, L"MinorVersion", peb->OSMinorVersion, L"osver.ini");
		path_buildnumber = GetPrivateProfileIntW(path, L"BuildNumber", peb->OSBuildNumber, L"osver.ini");
		path_platformid = GetPrivateProfileIntW(path, L"PlatformId", peb->OSPlatformId, L"osver.ini");
		//GetPrivateProfileStringW(path, L"CSDVersion", peb->OSCSDVersion, path_csdversion, 128, L"osver.ini");
		peb->OSMajorVersion = path_majorversion;
		peb->OSMinorVersion = path_minorversion;
		peb->OSBuildNumber = path_buildnumber;
		peb->OSPlatformId = path_platformid;
		//RtlInitUnicodeString(peb->OSCSDVersion, path_csdversion);
	} else {
		global_majorversion = GetPrivateProfileIntW(L"global", L"MajorVersion", peb->OSMajorVersion, L"osver.ini");
		global_minorversion = GetPrivateProfileIntW(L"global", L"MinorVersion", peb->OSMinorVersion, L"osver.ini");
		global_buildnumber = GetPrivateProfileIntW(L"global", L"BuildNumber", peb->OSBuildNumber, L"osver.ini");
		global_platformid = GetPrivateProfileIntW(L"global", L"PlatformId", peb->OSPlatformId, L"osver.ini");
		//GetPrivateProfileStringW(L"global", L"CSDVersion", peb->OSCSDVersion, global_csdversion, 128, L"osver.ini");
		peb->OSMajorVersion = global_majorversion;
		peb->OSMinorVersion = global_minorversion;
		peb->OSBuildNumber = global_buildnumber;
		peb->OSPlatformId = global_platformid;
		//RtlInitUnicodeString(peb->OSCSDVersion, global_csdversion);
	}
	if(verInfo->dwOSVersionInfoSize == sizeof(OSVERSIONINFOEXW)) {
		ver->wServicePackMajor = HIWORD(peb->OSCSDVersion);
		ver->wServicePackMinor = LOWORD(peb->OSCSDVersion);
		ver->wProductType = sharedData->NtProductType;
		ver->wSuiteMask = sharedData->SuiteMask;
	}
	return TRUE;
}