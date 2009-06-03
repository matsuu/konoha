using gl.*;

Float[] vertex = new Float[8, 3];
Float[] normal = new Float[6, 3];
int[] face = new Int[6, 4];

Float[] light0pos = [0.0, 3.0, 5.0, 1.0];
Float[] light1pos = [5.0, 3.0, 0.0, 1.0];
Float[] green = [0.0, 1.0, 0.0, 1.0];
Float[] red = [0.8, 0.2, 0.2, 1.0];

void make_vertex(int n, Float[] xyz)
{
  int i;
  for(i=0;i<3;i++) {
    vertex[n, i] = xyz[i];
  }
}

void init_vertex()
{
  make_vertex(0, [0.0, 0.0, 0.0]);
  make_vertex(1, [1.0, 0.0, 0.0]);
  make_vertex(2, [1.0, 1.0, 0.0]);
  make_vertex(3, [0.0, 1.0, 0.0]);
  make_vertex(4, [0.0, 0.0, 1.0]);
  make_vertex(5, [1.0, 0.0, 1.0]);
  make_vertex(6, [1.0, 1.0, 1.0]);
  make_vertex(7, [0.0, 1.0, 1.0]);
}

void make_normal(int n, Float[] xyz)
{
  int i;
  for(i=0;i<3;i++) {
    normal[n, i] = xyz[i];
  }
}

void init_normal()
{
  make_normal(0, [0.0, 0.0, -1.0]);
  make_normal(1, [1.0, 0.0, 0.0]);
  make_normal(2, [0.0, 0.0, 1.0]);
  make_normal(3, [-1.0, 0.0, 0.0]);
  make_normal(4, [0.0, -1.0, 0.0]);
  make_normal(5, [0.0, 1.0, 0.0]);
}

void make_face(int n, Int[] xyz)
{
  int i;
  for(i=0;i<|xyz|;i++){
    face[n, i] = xyz[i];
  }
}

void init_face()
{
  make_face(0, [0,1,2,3]);
  make_face(1, [1,5,6,2]);
  make_face(2, [5,4,7,6]);
  make_face(3, [4,0,3,7]);	
  make_face(4, [4,5,1,0]);
  make_face(5, [3,2,6,7]);
}



void cube()
{
  int i;
  int j;
  GL.glBegin(GL.GL_QUADS);
  for (j = 0; j < 6; j++) {
    GL.glNormal3d(normal[j,0], normal[j,1], normal[j,2]);
    for (i = 0; i < 4; i++) {
  	  GL.glVertex3d(vertex[face[j,i],0], vertex[face[j,i],1], vertex[face[j,i],2]);
    }
  }
  GL.glEnd();
}

Float r = 0.0;
void go_display()
{
  int i;
  int j;
  
  GL.glClear(GL.GL_COLOR_BUFFER_BIT| GL.GL_DEPTH_BUFFER_BIT);


  GL.glLightf(GL.GL_LIGHT0, GL.GL_POSITION, 1.0);
  GL.glLightf(GL.GL_LIGHT1, GL.GL_POSITION, 6.0);

  GL.glPushMatrix();
  GL.glRotatef(r, 0.0, 1.0, 0.0);
  GL.glMaterialf(GL.GL_FRONT_AND_BACK, GL.GL_DIFFUSE, 0.8);
  cube();
  GL.glPushMatrix();
  GL.glTranslated(1.0, 1.0, 1.0);
  GL.glRotatef(r*2, 0.0, 1.0, 0.0);
  GL.glMaterialf(GL.GL_FRONT_AND_BACK, GL.GL_DIFFUSE, -0.8);
  cube();
  GL.glPopMatrix();

  GL.glPopMatrix();

  GL.glutSwapBuffers();
  r = r + 0.5;
  if (r >= 360.0) r = 0.0;
}

void resize(int w, int h)
{
  GL.glViewport(0, 0, w, h);

  GL.glMatrixMode(GL.GL_PROJECTION);
  GL.glLoadIdentity();
  GL.gluPerspective(30.0, (Float)w/(Float)h, 1.0, 100.0);
  GL.glMatrixMode(GL.GL_MODELVIEW);
  GL.glLoadIdentity();
  GL.gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  
}

void idle_func()
{
  GL.glutPostRedisplay();
}

void init()
{
  GL.glClearColor(1.0, 1.0, 1.0, 1.0);
  GL.glEnable(GL.GL_DEPTH_TEST);

  GL.glEnable(GL.GL_CULL_FACE);
  GL.glCullFace(GL.GL_FRONT);

  GL.glEnable(GL.GL_LIGHTING);
  GL.glEnable(GL.GL_LIGHT0);
  GL.glEnable(GL.GL_LIGHT1);
  GL.glLightf(GL.GL_LIGHT1, GL.GL_DIFFUSE, 2.0);
  GL.glLightf(GL.GL_LIGHT1, GL.GL_SPECULAR, 2.0);
}

void stop_disp()
{
 ;
}

void mouse(int button, int state, int x, int y)
{
	Closure c;

	if (button == GL.GLUT_LEFT_BUTTON) {
		if (state == GL.GLUT_DOWN) {
			c = delegate(idle_func);
			GL.glutIdleFunc(c);
		}else {
			c = delegate(stop_disp);
			GL.glutIdleFunc(c);
		}
	}
}


int main(String[] args)
{
  init_vertex();
  init_face();
  init_normal();
  GL.glutInit(args);
  GL.glutInitDisplayMode(GL.GLUT_RGB | GL.GLUT_DOUBLE | GL.GLUT_DEPTH);

  GL.glutCreateWindow("Double Buffering");
  Closure dis = delegate(go_display);
  GL.glutDisplayFunc(dis);
  Closure r = delegate(resize);
  GL.glutReshapeFunc(r);
  Closure id = delegate(stop_disp);
  GL.glutIdleFunc(id);
  Closure mou = delegate(mouse);
  GL.glutMouseFunc(mou);
  init();
  GL.glutMainLoop();

  return 0;
}

