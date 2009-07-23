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

#ifdef KONOHA_OS__MACOSX
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <pthread.h>

#endif

#ifdef KONOHA_OS__LINUX
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pthread.h> 
#endif



#endif /* __KONOHA_GL_H */
