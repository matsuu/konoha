/*---------------------------------
 * OpenGL Binding for konoha
 *
 * shinpei nakata(c)2009
 * kindofbrown@users.sourceforge.jp
 *
 *---------------------------------*/

#include "knh_gl.h"


METHOD GL_glVertex3dv(Ctx *ctx, knh_sfp_t *sfp)
{
  int i;
  knh_FArray_t *fa = (knh_FArray_t *)sfp[1].o;
  int argc = knh_Array_size(fa);
  assert(argc == 3);
  GLdouble array[3];
  //  array = (GLdouble *)alloca(argc * sizeof(GLdouble));
  for (i = 0; i < argc; i++) {
	array[i] = fa->flist[i];
  }
  glVertex3dv(array);
  
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glNormal3dv(Ctx *ctx, knh_sfp_t *sfp)
{
  int i;
  knh_FArray_t *fa = (knh_FArray_t *)sfp[1].o;
  int argc = knh_Array_size(fa);
  assert(argc == 3);
  GLdouble array[3];
  //  array = (GLdouble *)alloca(argc * sizeof(GLdouble));
  for (i = 0; i < argc; i++) {
	//	fprintf(stderr, "get:(%d)%f\n", i, fa->flist[i]);
	array[i] = (GLdouble)fa->flist[i];

  }
  glNormal3dv(array);
  
  KNH_RETURN_void(ctx, sfp);
}

	
METHOD GL_glLightfv(Ctx *ctx, knh_sfp_t *sfp)
{
  int i;
  GLenum e1 = p_int(sfp[1]);
  GLenum e2 = p_int(sfp[2]);
  knh_FArray_t *fa = (knh_FArray_t *)sfp[3].o;
  int argc = knh_Array_size(fa);
  GLfloat array[3];
  for (i = 0; i < argc; i++) {
	array[i] = (GLfloat)fa->flist[i];
  }
  glLightfv(e1, e2, (const GLfloat *)array);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glMaterialfv(Ctx *ctx, knh_sfp_t *sfp)
{
  int i;
  GLenum e1 = p_int(sfp[1]);
  GLenum e2 = p_int(sfp[2]);
  knh_FArray_t *fa = (knh_FArray_t *)sfp[3].o;
  int argc = knh_Array_size(fa);
  GLfloat array[3];
  for (i = 0; i < argc; i++) {
	array[i] = (GLfloat)fa->flist[i];
  }
  glMaterialfv(e1, e2, (const GLfloat *)array);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glDepthMask(Ctx *ctx, knh_sfp_t* sfp)
{
  int i = p_int(sfp[1]);
  glDepthMask(i);
  KNH_RETURN_void(ctx, sfp);
}


