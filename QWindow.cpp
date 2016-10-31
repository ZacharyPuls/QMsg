#include "QLog.h"
#include "QWindow.h"

#include <iostream>

#pragma comment(lib, "user32.lib")

QWindow::QWindow(HINSTANCE hInstance, QString name, QString title, int width, int height, int x, int y) : instance_(hInstance), name_(name), title_(title), width_(width), height_(height), x_(x), y_(y) {

}

QWindow::~QWindow() {

}

bool QWindow::Create() {
	window_class_ = {};
	window_class_.cbClsExtra = 0;
	window_class_.cbSize = sizeof(WNDCLASSEX);
	window_class_.cbWndExtra = 0;
	window_class_.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	window_class_.hCursor = LoadCursor(NULL, IDC_ARROW);
	window_class_.hIcon = LoadIcon(instance_, MAKEINTRESOURCE(IDI_WINLOGO));
	window_class_.hIconSm = LoadIcon(instance_, MAKEINTRESOURCE(IDI_WINLOGO));
	window_class_.hInstance = instance_;
	window_class_.lpfnWndProc = &this->internal_message_handler_;
	window_class_.lpszClassName = name_.c_str();
	window_class_.lpszMenuName = NULL;
	window_class_.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

	if (!RegisterClassEx(&window_class_)) {
		Log->Error(L"Could not register window class.");
		return false;
	}

	if ((window_handle_ = CreateWindowEx(QMSG_QWINDOW_EXSTYLE, name_.c_str(), title_.c_str(), QMSG_QWINDOW_STYLE, x_, y_, width_, height_, NULL, NULL, instance_, NULL)) == NULL) {
		Log->Error(L"Could not create window handle.");
		return false;
	}

	ShowWindow(window_handle_, SW_SHOW);
	UpdateWindow(window_handle_);

	// Store a pointer to this QWindow object in USERDATA, so internal_message_handler (a static function) is able to access it and mutate state.
	SetWindowLongPtr(window_handle_, GWLP_USERDATA, reinterpret_cast<LONG>(this));

	render_surface_ = QRenderSurface(window_handle_);

	MSG msg;

	while (PeekMessage(&msg, window_handle_, 0, 0, PM_REMOVE) > 0) {
		if (msg.message == WM_QUIT) {
			break;
		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

LRESULT CALLBACK QWindow::internal_message_handler_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	QWindow *window = reinterpret_cast<QWindow *>(GetWindowLongPtr(hWnd, GWL_USERDATA));

	switch (uMsg) {
	case WM_CLOSE:
		PostQuitMessage(EXIT_SUCCESS);
		break;
	case WM_KEYDOWN:
		window->key_states_[wParam] = true;
		break;
	case WM_KEYUP:
		window->key_states_[wParam] = false;
		break;
	case WM_SIZE:
		return window->on_window_size_(hWnd, uMsg, wParam, lParam);
	case WM_PAINT:
		return window->on_window_draw_(hWnd, uMsg, wParam, lParam);
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK QWindow::on_window_size_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return 0;
}

LRESULT CALLBACK QWindow::on_window_draw_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	return 0;
}
