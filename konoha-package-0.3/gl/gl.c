#include <konoha.h>

#ifdef KONOHA_OS__MACOSX
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif

#ifdef KONOHA_OS__LINUX
#include <GL/glut.h>
#endif

Method *displayfunc;

static
void knh_display(void)
{
  Ctx *ctx = konoha_getCurrentContext();
  knh_sfp_t *lsfp = KNH_LOCAL(ctx);
  KNH_SCALL(ctx, lsfp, -1, displayfunc, 0);
  //  displayfunc->fcall_1(ctx, lsfp);
}

METHOD GL_glutInit(Ctx *ctx, knh_sfp_t *sfp)
{
  int i, argc;
  //  char argv0[] = "./konoha";
  //  char argv1[] = "./gl_sample.k";
  char **argv;
  Array *a = (Array *)sfp[1].o;
  argc = knh_Array_size(a);
  argv = (char **)alloca(argc * sizeof(char*));
  for (i = 0; i < argc; i++) {
	argv[i] = knh_String_tochar((String *)knh_Array_n(a, i));
  }
  //  argv[0] = argv0;
  //  argv[1] = argv1;
  //snprintf(argv[0], sizeof("./konoha"), "%s","./konoha"); 
  glutInit(&argc, argv);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glutCreateWindow(Ctx *ctx, knh_sfp_t *sfp)
{
  char *title = p_char(sfp[1]);
  glutCreateWindow(title);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glutMainLoop(Ctx *ctx, knh_sfp_t *sfp)
{
  glutMainLoop();

  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glutDisplayFunc(Ctx *ctx, knh_sfp_t *sfp)
{
  displayfunc = sfp[1].mtd;
  glutDisplayFunc(knh_display);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glutInitDisplayMode(Ctx *ctx, knh_sfp_t *sfp)
{
  glutInitDisplayMode(GLUT_RGBA);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glClear(Ctx *ctx, knh_sfp_t *sfp)
{
  glClear(GL_COLOR_BUFFER_BIT);
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

METHOD GL_glVertex2d(Ctx *ctx, knh_sfp_t *sfp)
{
  float f1 = p_float(sfp[1]);
  float f2 = p_float(sfp[2]);
  glVertex2d(f1, f2);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glBegin(Ctx *ctx, knh_sfp_t *sfp)
{
  glBegin(GL_LINE_LOOP);
  KNH_RETURN_void(ctx, sfp);
}

METHOD GL_glEnd(Ctx *ctx, knh_sfp_t *sfp)
{
  glEnd();
  KNH_RETURN_void(ctx, sfp);
}
