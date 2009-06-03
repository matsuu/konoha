using gl.*;
	
	void showpot()
	{
		GL.glClear(GL.GL_COLOR_BUFFER_BIT);
		GL.glColor3d(0.0, 0.0, 1.0);
		GL.glutWireTeapot(0.5);
		GL.glutSwapBuffers();
	}

	void event()
	{
		GL.glRotatef(1.0, 0.0, 1.0, 0.0);
		GL.glutPostRedisplay();
	}

	int main(String[] args)
	{
		GL.glutInit(args);
		GL.glutInitDisplayMode(GL.GLUT_DOUBLE | GL.GLUT_RGB);
		GL.glutInitWindowSize(250, 250);
		GL.glutInitWindowPosition(100, 100);
		GL.glutCreateWindow("Konoha GL sample");
		Closure d = delegate(showpot);
		GL.glutDisplayFunc(d);
		GL.glClearColor(0.5, 0.5, 0.5, 0.0);
		Closure t = delegate(event);
		GL.glutIdleFunc(t);
		GL.glutMainLoop();
	}
	
  
