#include <iostream>

#include "QLog.h"
#include "QMain.h"
#include "QWindow.h"

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, INT nShowCmd) {
	QWindow window = QWindow(hInstance, L"qmsgclient", L"QMsg Client", 480, 640, CW_USEDEFAULT, CW_USEDEFAULT);
	if (!window.Create()) {
		Log->Error(L"Could not create QWindow.");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}