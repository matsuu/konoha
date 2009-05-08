using gl.*

void display()
{
	GL.glClear(GL.GL_COLOR_BUFFER_BIT);
	GL.glBegin(GL.GL_LINE_LOOP);
	GL.glVertex2d(-0.9, -0.9);
	GL.glVertex2d(0.9, -0.9);
	GL.glVertex2d(0.9, 0.9);
	GL.glVertex2d(-0.9, 0.9);
	GL.glEnd();
	GL.glFlush();
}
	
int main(String[] args)
{
  GL.glutInit(args);
  GL.glutInitDisplayMode(GL.GLUT_RGBA);
  GL.glutCreateWindow("hello world");
  Closure c = delegate(display);
  GL.glutDisplayFunc(c);
  GL.glutMainLoop();
  return 0;
}


