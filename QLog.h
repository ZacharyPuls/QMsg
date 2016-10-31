#ifndef QMSG_QLOG_H
#define QMSG_QLOG_H

#include "QString.h"
#include "QVersion.h"

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

class QLog {
public:
	inline QLog() {}
	inline ~QLog() {}

	inline void Info(QString message) {
		this->log_(L"INFO", message);
	}

	inline void Error(QString message) {
		this->log_(L"ERROR", message);
	}
private:
	inline void log_(QString level, QString message) {
		time_t current_time = time(0);
		tm localized_time = { 0 };
		localtime_s(&localized_time, &current_time);
		std::wstringstream messageString;
		messageString << L"[" << std::put_time(&localized_time, L"%FT%TZ") << L"]" << L" [" << level << L"]: " << message;
		// MessageBox(NULL, messageString.str().c_str(), L"QMsg Debug", MB_OK | (level == L"ERROR" ? MB_ICONERROR : level == L"WARN" ? MB_ICONWARNING : MB_ICONINFORMATION));
		std::wcout << messageString.str() << std::endl;
	}
};

static QLog *Log = new QLog;

#endif
