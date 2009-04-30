
class GL;


void GL.glutDisplayFunc(Closure c);
void GL.glutInitFunc(Closure c);
void GL.glutReshapeFunc(Closure c);
void GL.glutIdleFunc(Closure c);
void GL.glutMouseFunc(Closure c);

void GL.glutInit(String[] argv);
void GL.glutCreateWindow(String str);
void GL.glutMainLoop();
void GL.glutInitDisplayMode(int flag);



void GL.glClear(int flag);
void GL.glClearColor(Float f1, Float f2, Float f3, Float f4);
void GL.glFlush();
void GL.glColor3d(Float f1, Float f2, Float f3);
void GL.glVertex2d(Float f1, Float f2);
void GL.glEnd();
void GL.glBegin(int flag);

void GL.glVertex3f(Float f0, Float f1, Float f2);

void GL.glColor3f(Float f0, Float f1, Float f2);
void GL.glMatrixMode(int flag);
void GL.glLoadIdentity();
void GL.glOrtho(Float f0, Float f1, Float f2, Float f3, Float f4, Float f5);
void GL.glutInitWindowPosition(Int i0, Int i1);
void GL.glutInitWindowSize(Int i0, Int i1);
void GL.glViewport(Int i0, Int i1, Int i2, Int i3);
void GL.glPushMatrix();
void GL.glPopAttrib();
void GL.glPopClientAttrib();
void GL.glPopMatrix();
void GL.glPopName();
void GL.glRotatef(Float f0, Float f1, Float f2, Float f3);
void GL.glShadeModel(int flag);
void GL.glutPostRedisplay();
void GL.glRectd(Float f0, Float f1, Float f2, Float f3);
void GL.glRectf(Float f0, Float f1, Float f2, Float f3);
void GL.glRecti(Int i0, Int i1, Int i2, Int i3);
void GL.glRects(Int i0, Int i1, Int i2, Int i3);
void GL.glutSwapBuffers();
