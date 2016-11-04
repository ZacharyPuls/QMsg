#ifndef QMSG_QGLPOLYGONTYPES_INL
#define QMSG_QGLPOLYGONTYPES_INL

#if defined(QMSG_GL_HIGH_PRECISION)
typedef QGLPolygon<QGLVertex2d, 3> QGLTriangle2D;
typedef QGLPolygon<QGLVertex3d, 3> QGLTriangle3D;
#else
typedef QGLPolygon<QGLVertex2f, 3> QGLTriangle2D;
typedef QGLPolygon<QGLVertex3f, 3> QGLTriangle3D;
#endif

#endif
