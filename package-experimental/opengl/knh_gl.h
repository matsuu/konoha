/*---------------------------------
 * OpenGL Binding for konoha
 *
 * shinpei nakata(c)2009
 * kindofbrown@users.sourceforge.jp
 *
 *---------------------------------*/

#ifndef __KONOHA_GL_H
#define __KONOHA_GL_H

#include <konoha.h>

#ifdef KONOHA_ON_MACOSX
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <pthread.h>

#endif

#ifdef KONOHA_ON_LINUX
#include <GL/glut.h>
#endif



#endif /* __KONOHA_GL_H */
