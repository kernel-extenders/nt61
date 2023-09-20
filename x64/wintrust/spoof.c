#include <Windows.h>
#include <WinError.h>
#include "common.h"

WINBASEAPI LONG WinVerifyTrust(HWND hwnd, GUID *pgActionID, LPVOID pWVTData) {
	return ERROR_SUCCESS;
}