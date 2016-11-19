#ifndef QMSG_QLOG_H
#define QMSG_QLOG_H

#include "QVersion.h"

#include "QString.h"

#include <Windows.h>

#include <ctime>
#include <fcntl.h>
#include <io.h>
#include <iomanip>
#include <iostream>
#include <sstream>


class QLog {
public:
	inline QLog() {
		create_console_window_();
	}
	inline ~QLog() {}

	inline void Info(QString message) {
		this->log_(L"INFO", message);
	}

	inline void Warn(QString message) {
		this->log_(L"WARN", message);
	}

	inline void Error(QString message) {
		this->log_(L"ERROR", message);
	}

	inline void Critical(QString message) {
		this->critical_(message);
	}

    inline void SystemError(QString function) {
        LPVOID message_buffer;
        QString formatted_message;
        DWORD last_error = GetLastError();

        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL, last_error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPWSTR)&message_buffer, 0, NULL);

        QCString message = (QCString)message_buffer;

        formatted_message = function + L" failed with error " + TO_QSTRING(last_error) + L": " + message;
        this->critical_(formatted_message);

        LocalFree(message_buffer);
    }
private:
	inline void create_console_window_() {
#if !defined(NDEBUG)
		AllocConsole();

		HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		INT crt_handle = _open_osfhandle((LONG)std_output_handle, _O_TEXT);
		FILE *std_output_file = _fdopen(crt_handle, "w");
		setvbuf(std_output_file, NULL, _IONBF, 1);
		*stdout = *std_output_file;
#endif
	}

	inline void log_(QString level, QString message) {
		time_t current_time = time(0);
		tm localized_time = { 0 };
		localtime_s(&localized_time, &current_time);
		std::wstringstream messageString;
		messageString << L"[" << std::put_time(&localized_time, L"%FT%TZ") << L"]" << L" [" << level << L"]: " << message << std::endl;;
		// MessageBox(NULL, messageString.str().c_str(), L"QMsg Debug", MB_OK | (level == L"ERROR" ? MB_ICONERROR : level == L"WARN" ? MB_ICONWARNING : MB_ICONINFORMATION));
		// std::wcout << messageString.str() << std::endl;
		OutputDebugString(messageString.str().c_str());
	}

	inline void critical_(QString message) {
		MessageBox(NULL, message.c_str(), L"Critical Error", MB_OK | MB_ICONASTERISK);
	}
};

static QLog *Log = new QLog;

#endif
