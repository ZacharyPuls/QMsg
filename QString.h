#ifndef QMSG_QSTRING_H
#define QMSG_QSTRING_H

#include "QVersion.h"

#include <Windows.h>

#include <string>
#include <locale>
#include <codecvt>

#if defined(QMSG_PLATFORM_WINDOWS)
typedef wchar_t QChar;
typedef std::wstring QString;
typedef QChar *QCString;
#define ITO_QSTRING(x) std::to_wstring(x)
#define TO_QSTRING(x) std::wstring_convert<std::codecvt_utf8<QChar>, QChar>().from_bytes(x)
#define FROM_QSTRING(x) std::wstring_convert<std::codecvt_utf8<QChar>, QChar>().to_bytes(x)
#else
typedef std::string QString;
#define TO_QSTRING(x) std::to_string(x)
#endif

#endif
