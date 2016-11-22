#ifndef QMSG_QGLPOLYGONTYPES_INL
#define QMSG_QGLPOLYGONTYPES_INL

#if defined(QMSG_GL_HIGH_PRECISION)
typedef QGLPolygon<GLdouble, 6> QGLTriangle2D;
typedef QGLPolygon<GLdouble, 9> QGLTriangle3D;
#else
typedef QGLPolygon<GLfloat, 6> QGLTriangle2D;
typedef QGLPolygon<GLfloat, 9> QGLTriangle3D;
#endif

#endif
