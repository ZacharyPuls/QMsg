#ifndef QMSG_QMSGCLIENT_H
#define QMSG_QMSGCLIENT_H

#include "QString.h"

#include <string>

class QMsgClient {
public:
	QMsgClient() {}
	~QMsgClient() {}
	bool SendMessage(QString message);

private:

};

#endif
