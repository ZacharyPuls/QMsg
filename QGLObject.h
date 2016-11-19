#ifndef QMSG_IQGLOBJECT_H
#define QMSG_IQGLOBJECT_H

#include "QVersion.h"

#include "QGL.h"

class IQGLObject {
public:
	virtual inline void Bind() = 0;
	virtual inline void Unbind() = 0;
	virtual bool Create() = 0;
	inline GLuint get_id() {
		return id_;
	}
protected:
	GLuint id_ = 0;
	bool bound_ = false;
};

#endif
