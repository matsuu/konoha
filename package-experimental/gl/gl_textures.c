
/*---------------------------------
 * OpenGL Binding for konoha
 *
 * shinpei nakata(c)2009
 * kindofbrown@users.sourceforge.jp
 *
 *---------------------------------*/

#include "knh_gl.h"

METHOD GL_glGenTextures(Ctx *ctx, knh_sfp_t *sfp)
{
  int i;
  int n = p_int(sfp[1]);
  GLuint *textures = (GLuint *)malloc(sizeof(GLuint) * n);  
  knh_IArray_t *ia = (knh_IArray_t *)sfp[2].o;
  glGenTextures(n, textures);
  for (i = 0; i < n; i++) {
	ia->ilist[i] = textures[i];
  }
  KNH_RETURN_void(ctx, sfp);
}


METHOD GL_glTexImage2D(Ctx *ctx, knh_sfp_t *sfp)
{
  int x,y,z,index, index_c;
  GLsizei f3 = p_int(sfp[1]); // width
  GLsizei f4 = p_int(sfp[2]); // height
  knh_IArray_t *iarray= (knh_IArray_t *)sfp[3].o;

  int w = f3;
  int h = f4;
  int a = knh_Array_size(iarray) / (w * h);

  //  unsigned char ***image = (unsigned char ***)alloca(sizeof(unsigned char**) * w );
  //  unsigned char **image = (unsigned char **)alloca(sizeof(unsigned char*) * h );
  unsigned char *image = (unsigned char *)alloca(sizeof(unsigned char) * a * w * h );
   for (x = 0; x < h; x++) {
	for (y = 0; y < w; y++) {
	  for (z = 0; z < a; z++) {
		index = x + y * h + z * h * w;
		index_c = x * a * h + y * a + z;
		image[index_c] = (unsigned char)iarray->ilist[index];
		//		fprintf(stderr, "%d, ", image[index]);
	  }
	}
   }

  glTexImage2D(GL_TEXTURE_2D,0 ,GL_RGBA ,
			   f3 ,f4 ,0,
			   GL_RGBA ,GL_UNSIGNED_BYTE, image);
  KNH_RETURN_void(ctx, sfp);
}
