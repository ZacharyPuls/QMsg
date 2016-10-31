#ifndef QMSG_QSOCKET_H
#define QMSG_QSOCKET_H

#include "QVersion.h"

#if defined(QMSG_SOCKET_WINSOCK2)
#include <WinSock2.h>
#include <WS2tcpip.h>
#elif defined(QMSG_SOCKET_POSIX)
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
typedef int SOCKET;
#endif

class QSocket {
public:
	QSocket();
	~QSocket();
private:
};

#endif
