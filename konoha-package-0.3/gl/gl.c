/*---------------------------------
 * OpenGL Binding for konoha
 *
 * shinpei nakata(c)2009
 * kindofbrown@users.sourceforge.jp
 *
 *---------------------------------*/

#include <konoha.h>

#ifdef KONOHA_OS__MACOSX
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <pthread.h>
#endif

#ifdef KONOHA_OS__LINUX
#include <GL/glut.h>
#endif

Closure *displayfunc;
Closure *initfunc = NULL;
Closure *reshapefunc;
Closure *mousefunc;
Closure *idlefunc;


Ctx gl_ctx;


static
knh_IntConstData_t IntConstData[] = {
  {"GL.GL_POLYGON", GL_POLYGON},
  {"GL.GL_COLOR_BUFFER_BIT", GL_COLOR_BUFFER_BIT},
  {"GL.GLUT_RGBA", GLUT_RGBA},
  {"GL.GL_LINE_LOOP", GL_LINE_LOOP},
  {"GL.GL_PROJECTION", GL_PROJECTION},
  {"GL.GL_POLYGON", GL_POLYGON},
  {"GL.GLUT_SINGLE", GLUT_SINGLE},
  {"GL.GLUT_RGB", GLUT_RGB},
  {"GL.GL_MODELVIEW", GL_MODELVIEW},
  {"GL.GL_FLAT", GL_FLAT},
  {"GL.GLUT_DOUBLE", GLUT_DOUBLE},
  {NULL} // end of const
};


static
void knh_glut_display(void)
{
#ifndef KNH_USING_PTHREAD
  Ctx *lctx = konoha_getCurrentContext();
#else
  Ctx *lctx = &gl_ctx;
#endif
  knh_sfp_t *lsfp = KNH_LOCAL(lctx);

  knh_Closure_invokesfp(lctx, displayfunc, lsfp, 0);
  //  KNH_SCALL(ctx, lsfp, -1, displayfunc, 0);
  //  displayfunc->fcall_1(ctx, lsfp);
}

void init (void)
{
  if (initfunc == NULL) {
	konoha_loadIntConstData(konoha_getCurrentContext(), IntConstData);
	return;
  }
  
#ifndef KNH_USING_PTHREAD
  Ctx *lctx = konoha_getCurrentContext();
#else
  Ctx *lctx = &gl_ctx;
#endif
  knh_sfp_t *lsfp = KNH_LOCAL(lctx);

  knh_Closure_invokesfp(lctx, initfunc, lsfp, 0);
}

void knh_glut_reshape(int w, int h)
{
#ifndef KNH_USING_PTHREAD
  Ctx *lctx = konoha_getCurrentContext();
#else
  Ctx *lctx = &gl_ctx;
#endif
  knh_sfp_t *lsfp = KNH_LOCAL(lctx);
  //  Object *arg1 = (Object*)new_IntX__fast(lctx, CLASS_Int, w);
  //  Object *arg2 = (Object*)new_IntX__fast(lctx, CLASS_Int, h);
  Int *arg1 = new_Int(lctx, w);
  Int *arg2 = new_Int(lctx, h);
  //  knh_putsfp(lctx, lsfp, 1, reshapefunc);
  knh_putsfp(lctx, lsfp, 2, (Object *)arg1);
  knh_putsfp(lctx, lsfp, 3, (Object *)arg2);
  knh_Closure_invokesfp(lctx, reshapefunc, lsfp, 2);

}

void knh_glut_idle (void)
{
  
#ifndef KNH_USING_PTHREAD
  Ctx *lctx = konoha_getCurrentContext();
#else
  Ctx *lctx = &gl_ctx;
#endif
  knh_sfp_t *lsfp = KNH_LOCAL(lctx);

  knh_Closure_invokesfp(lctx, idlefunc, lsfp, 0);
}

void knh_glut_mouse(int button, int state, int x, int y)
{
#ifndef KNH_USING_PTHREAD
  Ctx *lctx = konoha_getCurrentContext();
#else
  Ctx *lctx = &gl_ctx;
#endif
  knh_sfp_t *lsfp = KNH_LOCAL(lctx);
  Int *arg1 = new_Int(lctx, button);
  Int *arg2 = new_Int(lctx, state);
  Int *arg3 = new_Int(lctx, x);
  Int *arg4 = new_Int(lctx, y);

  knh_putsfp(lctx, lsfp, 2, (Object *)arg1);
  knh_putsfp(lctx, lsfp, 3, (Object *)arg2);
  knh_putsfp(lctx, lsfp, 4, (Object *)arg3);
  knh_putsfp(lctx, lsfp, 5, (Object *)arg4);
  
  knh_Closure_invokesfp(lctx, mousefunc, lsfp, 4);

}

METHOD GL_glutInit(Ctx *ctx, knh_sfp_t *sfp)
{
  int i, argc;
  char **argv;
  Array *a = (Array *)sfp[1].o;
  argc = knh_Array_size(a);
  argv = (char **)alloca(argc * sizeof(char*));
  for (i = 0; i < argc; i++) {
	argv[i] = knh_String_tochar((String *)knh_Array_n(a, i));
  }
  glutInit(&argc, argv);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glutCreateWindow(Ctx *ctx, knh_sfp_t *sfp)
{
  char *title = p_char(sfp[1]);
  glutCreateWindow(title);
  KNH_RETURN_void(ctx, sfp);
}

/*
void *thread_func(void *param)
{
  pthread_detach(pthread_self());
  glutMainLoop();
}

*/
METHOD GL_glutMainLoop(Ctx *ctx, knh_sfp_t *sfp)
{
#ifndef KNH_USING_PTHREAD
  glutMainLoop();
#else
  fprintf(stderr, "thread");
  pthread_t thread;
  memcpy(&gl_ctx, ctx, sizeof(Ctx));

  if (pthread_create(&thread, NULL, thread_func, NULL))
	  perror("cannot create thread");
  //  pthread_join(thread, NULL);
#endif

  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glutDisplayFunc(Ctx *ctx, knh_sfp_t *sfp)
{
  displayfunc = sfp[1].cc;
  glutDisplayFunc(knh_glut_display);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glutInitFunc(Ctx *ctx, knh_sfp_t *sfp)
{
  initfunc = sfp[1].cc;
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glutReshapeFunc(Ctx *ctx, knh_sfp_t *sfp)
{
  reshapefunc = sfp[1].cc;
  glutReshapeFunc(knh_glut_reshape);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glutIdleFunc(Ctx *ctx, knh_sfp_t *sfp)
{
  idlefunc = sfp[1].cc;
  glutIdleFunc(knh_glut_idle);
  KNH_RETURN_void(ctx, sfp);
}


METHOD GL_glutMouseFunc(Ctx *ctx, knh_sfp_t *sfp)
{
  mousefunc = sfp[1].cc;
  glutMouseFunc(knh_glut_mouse);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glutInitDisplayMode(Ctx *ctx, knh_sfp_t *sfp)
{
  int flag = p_int(sfp[1]);
  glutInitDisplayMode(flag);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glClear(Ctx *ctx, knh_sfp_t *sfp)
{
  int flag = p_int(sfp[1]);
  glClear(flag);
  KNH_RETURN_void(ctx, sfp);
}


METHOD GL_glFlush(Ctx *ctx, knh_sfp_t *sfp)
{
  glFlush();
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glColor3d(Ctx *ctx, knh_sfp_t *sfp)
{
  float f1 = p_float(sfp[1]);
  float f2 = p_float(sfp[2]);
  float f3 = p_float(sfp[3]);

  glColor3d(f1, f2, f3);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glClearColor(Ctx *ctx, knh_sfp_t *sfp)
{
  float f1 = p_float(sfp[1]);
  float f2 = p_float(sfp[2]);
  float f3 = p_float(sfp[3]);
  float f4 = p_float(sfp[4]);
  glClearColor(f1, f2, f3, f4);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glVertex2d(Ctx *ctx, knh_sfp_t *sfp)
{
  float f1 = p_float(sfp[1]);
  float f2 = p_float(sfp[2]);
  glVertex2d(f1, f2);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glBegin(Ctx *ctx, knh_sfp_t *sfp)
{
  int flag = p_int(sfp[1]);
  glBegin(flag);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glEnd(Ctx *ctx, knh_sfp_t *sfp)
{
  glEnd();
  KNH_RETURN_void(ctx, sfp);
}

/* void GL.glVertex3f(Float f0, Float f1, Float f2) */

METHOD GL_glVertex3f(Ctx *ctx, knh_sfp_t* sfp)
{
	float f0 = p_float(sfp[1]);
	float f1 = p_float(sfp[2]);
	float f2 = p_float(sfp[3]);
	glVertex3f(f0 ,f1 ,f2 );

	KNH_RETURN_void(ctx, sfp);
}

  
/* void GL.glColor3f(Float f0, Float f1, Float f2) */

METHOD GL_glColor3f(Ctx *ctx, knh_sfp_t* sfp)
{
	float f0 = p_float(sfp[1]);
	float f1 = p_float(sfp[2]);
	float f2 = p_float(sfp[3]);
	glColor3f(f0 ,f1 ,f2 );

	KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glMatrixMode(Ctx *ctx, knh_sfp_t* sfp)
{
  int flag = p_int(sfp[1]);
	glMatrixMode(flag);
	KNH_RETURN_void(ctx, sfp);
}
/* void GL.glLoadIdentity() */

METHOD GL_glLoadIdentity(Ctx *ctx, knh_sfp_t* sfp)
{
	glLoadIdentity();

	KNH_RETURN_void(ctx, sfp);
}

/* void GL.glOrtho(Float f0, Float f1, Float f2, Float f3, Float f4, Float f5) */

METHOD GL_glOrtho(Ctx *ctx, knh_sfp_t* sfp)
{
	float f0 = p_float(sfp[1]);
	float f1 = p_float(sfp[2]);
	float f2 = p_float(sfp[3]);
	float f3 = p_float(sfp[4]);
	float f4 = p_float(sfp[5]);
	float f5 = p_float(sfp[6]);
	glOrtho(f0 ,f1 ,f2 ,f3 ,f4 ,f5 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GL.glutInitWindowPosition(Int i0, Int i1) */

METHOD GL_glutInitWindowPosition(Ctx *ctx, knh_sfp_t* sfp)
{
	int i0 = p_int(sfp[1]);
	int i1 = p_int(sfp[2]);
	glutInitWindowPosition(i0 ,i1 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GL.glutInitWindowSize(Int i0, Int i1) */

METHOD GL_glutInitWindowSize(Ctx *ctx, knh_sfp_t* sfp)
{
	int i0 = p_int(sfp[1]);
	int i1 = p_int(sfp[2]);
	glutInitWindowSize(i0 ,i1 );

	KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glViewport(Ctx *ctx, knh_sfp_t* sfp)
{
	int i0 = p_int(sfp[1]);
	int i1 = p_int(sfp[2]);
	int i2 = p_int(sfp[3]);
	int i3 = p_int(sfp[4]);	
	glViewport(i0 ,i1, (GLsizei)i2, (GLsizei)i3);

	KNH_RETURN_void(ctx, sfp);
}

/* void GL.glPushMatrix() */

METHOD GL_glPushMatrix(Ctx *ctx, knh_sfp_t* sfp)
{
	glPushMatrix();

	KNH_RETURN_void(ctx, sfp);
}
METHOD GL_glPopAttrib(Ctx *ctx, knh_sfp_t* sfp)
{
	glPopAttrib();

	KNH_RETURN_void(ctx, sfp);
}

/* void GL.glPopClientAttrib() */

METHOD GL_glPopClientAttrib(Ctx *ctx, knh_sfp_t* sfp)
{
	glPopClientAttrib();

	KNH_RETURN_void(ctx, sfp);
}

/* void GL.glPopMatrix() */

METHOD GL_glPopMatrix(Ctx *ctx, knh_sfp_t* sfp)
{
	glPopMatrix();

	KNH_RETURN_void(ctx, sfp);
}

/* void GL.glPopName() */

METHOD GL_glPopName(Ctx *ctx, knh_sfp_t* sfp)
{
	glPopName();

	KNH_RETURN_void(ctx, sfp);
}
/* void GL.glRotatef(Float f0, Float f1, Float f2, Float f3) */

METHOD GL_glRotatef(Ctx *ctx, knh_sfp_t* sfp)
{
	float f0 = p_float(sfp[1]);
	float f1 = p_float(sfp[2]);
	float f2 = p_float(sfp[3]);
	float f3 = p_float(sfp[4]);
	glRotatef(f0 ,f1 ,f2 ,f3 );

	KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glShadeModel(Ctx *ctx, knh_sfp_t* sfp)
{
	int flag = p_int(sfp[1]);
	glShadeModel(flag);

	KNH_RETURN_void(ctx, sfp);
}

/* void GL.glutPostRedisplay() */

METHOD GL_glutPostRedisplay(Ctx *ctx, knh_sfp_t* sfp)
{
	glutPostRedisplay();

	KNH_RETURN_void(ctx, sfp);
}
/* void GL.glRectd(Float f0, Float f1, Float f2, Float f3) */

METHOD GL_glRectd(Ctx *ctx, knh_sfp_t* sfp)
{
	float f0 = p_float(sfp[1]);
	float f1 = p_float(sfp[2]);
	float f2 = p_float(sfp[3]);
	float f3 = p_float(sfp[4]);
	glRectd(f0 ,f1 ,f2 ,f3 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GL.glRectf(Float f0, Float f1, Float f2, Float f3) */

METHOD GL_glRectf(Ctx *ctx, knh_sfp_t* sfp)
{
	float f0 = p_float(sfp[1]);
	float f1 = p_float(sfp[2]);
	float f2 = p_float(sfp[3]);
	float f3 = p_float(sfp[4]);
	glRectf(f0 ,f1 ,f2 ,f3 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GL.glRecti(Int i0, Int i1, Int i2, Int i3) */

METHOD GL_glRecti(Ctx *ctx, knh_sfp_t* sfp)
{
	int i0 = p_int(sfp[1]);
	int i1 = p_int(sfp[2]);
	int i2 = p_int(sfp[3]);
	int i3 = p_int(sfp[4]);
	glRecti(i0 ,i1 ,i2 ,i3 );

	KNH_RETURN_void(ctx, sfp);
}

/* void GL.glRects(Int i0, Int i1, Int i2, Int i3) */

METHOD GL_glRects(Ctx *ctx, knh_sfp_t* sfp)
{
	int i0 = p_int(sfp[1]);
	int i1 = p_int(sfp[2]);
	int i2 = p_int(sfp[3]);
	int i3 = p_int(sfp[4]);
	glRects(i0 ,i1 ,i2 ,i3 );

	KNH_RETURN_void(ctx, sfp);
}
/* void GL.glutSwapBuffers() */

METHOD GL_glutSwapBuffers(Ctx *ctx, knh_sfp_t* sfp)
{
	glutSwapBuffers();

	KNH_RETURN_void(ctx, sfp);
}
