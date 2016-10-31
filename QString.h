#ifndef QMSG_QSTRING_H
#define QMSG_QSTRING_H

#include "QVersion.h"

#include <Windows.h>

#include <string>

#if defined(QMSG_PLATFORM_WINDOWS)
typedef wchar_t QChar;
typedef std::wstring QString;
#define TO_QSTRING(x) std::to_wstring(x)
#define FROM_QSTRING(x) std::wstring_convert<std::codecvt_utf8<QChar>, QChar>.toBytes(x)
#else
typedef std::string QString;
#define TO_QSTRING(x) std::to_string(x)
#endif

#endif
