

using gl.*

TEX_HEIGHT = 16;
TEX_WIDTH = 16;
Int[][][] image = new Int[TEX_HEIGHT, TEX_WIDTH, 4]

void initTexture() 
{ 
  int i, j, c;
  for (i=0;i<TEX_HEIGHT;i++) { 
    for (j=0;j<TEX_WIDTH;j++) {
		c = ((i & 0x01) ^ ((j & 0x01))); 
		image[i, j, 0] = c * 255;
		image[i, j, 1] = c * 255;
		image[i, j, 2] = c * 255; 
		image[i, j, 3] = 255;
    } 
  } 
} 
void displayTexPolygon() 
{ 
  GL.glEnable(GL.GL_TEXTURE_2D); 
  GL.glBegin(GL.GL_QUADS);
  GL.glTexCoord2f(0.0, 0.0);
  GL.glVertex3f(-5.0,-5.0, 0.0);
  GL.glTexCoord2f(0.0, 1.0);
  GL.glVertex3f(-5.0, 5.0, 0.0); 
  GL.glTexCoord2f(1.0, 1.0);
  GL.glVertex3f( 5.0, 5.0, 0.0); 
  GL.glTexCoord2f(1.0, 0.0);
  GL.glVertex3f( 5.0,-5.0, 0.0); 
  GL.glEnd();
  GL.glDisable(GL.GL_TEXTURE_2D); 
} 
float spin=0.0;

void display() 
{ 

  GL.glClear(GL.GL_COLOR_BUFFER_BIT | GL.GL_DEPTH_BUFFER_BIT);
  GL.glPushMatrix(); 

  GL.glTranslatef(0.0, 0.0,-20.0); 
  GL.glRotatef(spin, 0.0, 1.0, 0.0); 
  GL.glColor3f(1.0, 1.0, 1.0); 
  displayTexPolygon(); 

  spin+=1.0; 
  GL.glPopMatrix(); 
  GL.glFlush(); 
  GL.glutSwapBuffers(); 
}

void init() 
{ 
  GL.glClearColor(0.0, 0.0, 0.0, 0.0); 
  GL.glDepthFunc(GL.GL_LEQUAL); 
  GL.glEnable(GL.GL_DEPTH_TEST); 
  initTexture();
  GL.glPixelStorei(GL.GL_UNPACK_ALIGNMENT, 1); 
  GL.glTexParameteri(GL.GL_TEXTURE_2D, GL.GL_TEXTURE_WRAP_S, GL.GL_REPEAT); 
  GL.glTexParameteri(GL.GL_TEXTURE_2D, GL.GL_TEXTURE_WRAP_T, GL.GL_REPEAT); 
  GL.glTexParameteri(GL.GL_TEXTURE_2D, GL.GL_TEXTURE_MAG_FILTER, GL.GL_NEAREST); 
  GL.glTexParameteri(GL.GL_TEXTURE_2D, GL.GL_TEXTURE_MIN_FILTER, GL.GL_NEAREST); 
  GL.glTexImage2D(TEX_WIDTH, TEX_HEIGHT, image); 
} 

void reshape(int w, int h) 
{ 
  GL.glViewport(0, 0,  w,  h); 
  GL.glMatrixMode(GL.GL_PROJECTION); 
  GL.glLoadIdentity(); 
  GL.glFrustum(-5.0, 5.0,-5.0, 5.0, 5.0, 500.0); 
  GL.glMatrixMode(GL.GL_MODELVIEW); 
  GL.glLoadIdentity(); 
}
void idle ()
{
	GL.glutPostRedisplay();
}

int main(String[] argv) 
{ 
  GL.glutInit(argv);
  GL.glutInitDisplayMode (GL.GLUT_DEPTH | GL.GLUT_DOUBLE | GL.GLUT_RGBA); 
  GL.glutInitWindowSize (250, 250); 
  GL.glutInitWindowPosition (100, 100); 
  GL.glutCreateWindow(argv[0]); 

  Closure id = delegate(idle);
  GL.glutIdleFunc(id);
  Closure d = delegate(display);
  GL.glutDisplayFunc(d); 
  init();
  Closure r = delegate(reshape);
  GL.glutReshapeFunc(r); 
  GL.glutMainLoop(); 
  return 0; 
} 
