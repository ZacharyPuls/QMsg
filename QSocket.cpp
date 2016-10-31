#include "QLog.h"
#include "QSocket.h"
#include "QString.h"

#include <iostream>
#include <string>

#if defined(QMSG_SOCKET_WINSOCK2)
#pragma comment(lib, "Ws2_32.lib")
#endif

QSocket::QSocket() {
#if defined(QMSG_SOCKET_WINSOCK2)
	WSADATA wsadata;
	int result = WSAStartup(MAKEWORD(1, 1), &wsadata);
	if (result != 0) {
		Log->Error(L"QSocket initialization failed, could not call WSAStartup. Error code returned was: " + TO_QSTRING(result) + L".");
	}
#endif
}

QSocket::~QSocket() {
#if defined(QMSG_SOCKET_WINSOCK2)
	int result = WSACleanup();
	if (result != 0) {
		Log->Error(L"QSocket deinitialization failed, could not call WSACleanup. Error code returned was " + TO_QSTRING(result) + L".");
	}
#endif
}
