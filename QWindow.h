#ifndef QMSG_QWINDOW_H
#define QMSG_QWINDOW_H

#include "QRenderSurface.h"
#include "QString.h"

#include <Windows.h>

#include <string>

#define QMSG_QWINDOW_EXSTYLE WS_EX_ACCEPTFILES | WS_EX_APPWINDOW
#define QMSG_QWINDOW_STYLE WS_OVERLAPPEDWINDOW | WS_VSCROLL

class QWindow {
public:
	QWindow() {}
	QWindow(HINSTANCE hInstance, QString name, QString title, int width, int height, int x, int y);
	~QWindow();
	bool Create();
private:
	QString name_;
	QString title_;
	int width_;
	int height_;
	int x_;
	int y_;

	HINSTANCE instance_;
	HWND window_handle_;
	WNDCLASSEX window_class_;
	QRenderSurface render_surface_;

	bool key_states_[256] = { 0 };
	static LRESULT CALLBACK internal_message_handler_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Message/Event callbacks
	LRESULT CALLBACK on_window_size_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK on_window_draw_(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif