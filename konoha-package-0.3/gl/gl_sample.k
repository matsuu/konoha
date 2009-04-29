using gl.*

void display()
{
	GL.glClear();
	GL.glBegin();
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
  GL.glutInitDisplayMode();
  GL.glutCreateWindow("hello world");
  GL.glutDisplayFunc(Script.display);
  GL.glutMainLoop();
  return 0;
}


