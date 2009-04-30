using gl.*

float spin = 0.0;	
void display()
{
	GL.glClear(GL.GL_COLOR_BUFFER_BIT);
	GL.glPushMatrix();
	GL.glRotatef(spin, 0.0, 0.0, 1.0);
	GL.glColor3f(1.0, 1.0, 1.0);
	GL.glRectf(-25.0, -25.0, 25.0, 25.0);
	GL.glPopMatrix();
	GL.glutSwapBuffers();

}

void init()
{
	GL.glClearColor(0.0, 0.0, 0.0, 0.0);
	GL.glShadeModel(GL.GL_FLAT);
}

void spinDisplay()
{
	spin = spin + 2.0;
	//	print 'bye'
	if (spin > 360.0) {
		spin = spin - 360.0;
	}
	GL.glutPostRedisplay();

}

void reshape(Int w, Int h)
{

	GL.glViewport(0, 0, w, h)
	GL.glMatrixMode(GL.GL_PROJECTION);
	GL.glLoadIdentity();
	GL.glOrtho(-50.0, 50.0, -50.0, 50.0, -1.0, 1.0);
	GL.glMatrixMode(GL.GL_MODELVIEW);
	GL.glLoadIdentity();
	print w, h
}

void mouse(int button int state, int x, int y)
{
	print 'mouse event detected!'
}

int main(String[] args)
{
  GL.glutInit(args);
  GL.glutInitDisplayMode(GL.GLUT_DOUBLE | GL.GLUT_RGB);
  GL.glutInitWindowSize(250, 250);
  GL.glutInitWindowPosition(100, 100);
  GL.glutCreateWindow("hello world");
  Closure c = delegate(display);
  GL.glutDisplayFunc(c);
  Closure i = delegate(init);
  GL.glutInitFunc(i);
  init();
  Closure r = delegate(reshape);
  GL.glutReshapeFunc(r);
  Closure m = delegate(mouse);
  GL.glutMouseFunc(m);
  Closure idle = delegate(spinDisplay);
  GL.glutIdleFunc(idle);
  GL.glutMainLoop();
  return 0;
}


