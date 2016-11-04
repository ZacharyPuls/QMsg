#ifndef QMSG_IQGLOBJECT_H
#define QMSG_IQGLOBJECT_H

#include "QVersion.h"

class IQGLObject {
public:
	virtual inline void Bind() = 0;
	virtual bool Create() = 0;
};

#endif
