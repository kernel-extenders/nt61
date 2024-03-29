#include <Windows.h>
#include <Shlwapi.h>
#include <Winhttp.h>

#undef WINBASEAPI
#define WINBASEAPI __declspec(dllexport)
#define WINAPI __stdcall

DWORD WINBASEAPI WINAPI WinHttpWebSocketClose( HINTERNET hsocket, USHORT status, void *reason, DWORD len ) {
    return WinHttpCloseHandle(hsocket);
}

DWORD WINBASEAPI WINAPI WinHttpWebSocketReceive(HINTERNET hWebSocket, PVOID pvBuffer, DWORD dwBufferLength, DWORD *pdwBytesRead, enum WINHTTP_WEB_SOCKET_BUFFER_TYPE *peBufferType) {
	return WinHttpReceiveResponse(hWebSocket, pvBuffer);
}

DWORD WINBASEAPI WINAPI WinHttpWebSocketSend(HINTERNET hWebSocket, enum WINHTTP_WEB_SOCKET_BUFFER_TYPE *eBufferType, PVOID pvBuffer, DWORD dwBufferLength) {
	return WinHttpSendRequest(hWebSocket, ((LPCWSTR)pvBuffer), dwBufferLength, pvBuffer, 0, 0, NULL);	
}

HINTERNET WINBASEAPI WINAPI WinHttpWebSocketCompleteUpgrade(HINTERNET hRequest, DWORD_PTR pContext) {
	return WinHttpSetStatusCallback(hRequest, NULL, WINHTTP_CALLBACK_FLAG_SENDREQUEST_COMPLETE, NULL);
}