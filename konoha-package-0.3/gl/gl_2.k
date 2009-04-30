using gl.*

void display()
{
	GL.glClear(GL.GL_COLOR_BUFFER_BIT);
	GL.glColor3f(1.0, 1.0, 1.0);
	GL.glBegin(GL.GL_POLYGON);
	GL.glVertex3f(0.25, 0.25, 0.0);
	GL.glVertex3f(0.75, 0.25, 0.0);
	GL.glVertex3f(0.75, 0.75, 0.0);
	GL.glVertex3f(0.25, 0.75, 0.0);
	GL.glEnd();
	GL.glFlush();
}

void init()
{
	GL.glClearColor(0.0,0.0,0.0,0.0);
	GL.glMatrixMode(GL.GL_PROJECTION);
	GL.glLoadIdentity();
	GL.glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
}


int main(String[] args)
{
  GL.glutInit(args);
  GL.glutInitDisplayMode(GL.GLUT_SINGLE | GL.GLUT_RGB);
  GL.glutInitWindowSize(250, 250);
  GL.glutInitWindowPosition(100, 100);
  GL.glutCreateWindow("hello world");
  Closure c = delegate(display);
  GL.glutDisplayFunc(c);
  Closure i = delegate(init);
  GL.glutInitFunc(i);
  GL.glutMainLoop();
  return 0;
}


