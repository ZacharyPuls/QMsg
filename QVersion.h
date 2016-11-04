#ifndef QMSG_QVERSION_H
#define QMSG_QVERSION_H

#if defined(_WIN32)
#define QMSG_WIN32
#elif defined(_WIN64)
#define QMSG_WIN64
#elif defined(__GNUC__)
#define QMSG_UNIX
#endif

#if defined(QMSG_WIN32) || defined(QMSG_WIN64)
#define QMSG_PLATFORM_WINDOWS
#define QMSG_SOCKET_WINSOCK2
#define WIN32_LEAN_AND_MEAN
#if !defined(UNICODE)
#define UNICODE 1
#endif
#if !defined(_UNICODE)
#define _UNICODE 1
#endif
#elif defined(QMSG_UNIX)
#define QMSG_PLATFORM_X11
#define QMSG_SOCKET_POSIX
#endif

// #define QMSG_GL_HIGH_PRECISION 1

#endif


