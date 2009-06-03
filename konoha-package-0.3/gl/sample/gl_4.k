using gl.*;

Float[] vertex = new Float[8, 3];
Float[] color = new Float[8, 3];
int[] edge = new Int[12, 2];
int[] face = new Int[6, 4];


void make_vertex(int n, Float[] xyz)
{
  int i;
  for(i=0;i<3;i++) {
    vertex[n, i] = xyz[i];
  }
}
void make_color(int n, Float[] xyz)
{
  int i;
  for(i=0;i<3;i++) {
    color[n, i] = xyz[i];
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

void init_color()
{
  make_color(0, [1.0, 0.0, 0.0]);
  make_color(1, [0.0, 1.0, 0.0]);
  make_color(2, [0.0, 0.0, 1.0]);
  make_color(3, [1.0, 1.0, 0.0]);
  make_color(4, [1.0, 0.0, 1.0]);
  make_color(5, [0.0, 1.0, 1.0]);

}


void make_edge(int n, Float[] xyz)
{
  int i;
  for(i=0;i<2;i++) {
    edge[n, i] = xyz[i];
  }
}


void init_edge()
{
  make_edge(0, [0, 1]);
  make_edge(1, [1, 2]);
  make_edge(2, [2, 3]);
  make_edge(3, [3, 0]);
  make_edge(4, [4, 5]);
  make_edge(5, [5, 6]);	
  make_edge(6, [6, 7]);
  make_edge(7, [7, 4]);
  make_edge(8, [0, 4]);
  make_edge(9, [1, 5]);
  make_edge(10, [2, 6]);
  make_edge(11, [3, 7]);
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




int r = 0;
void go_display()
{
  int i;
  int j;
  
  GL.glClear(GL.GL_COLOR_BUFFER_BIT| GL.GL_DEPTH_BUFFER_BIT);
  GL.glLoadIdentity();
  GL.gluLookAt(3.0, 4.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  
  GL.glRotatef((Float)r, 0.0, 1.0, 0.0);



//  GL.glBegin(GL.GL_LINES);
  GL.glBegin(GL.GL_QUADS);
  for (j = 0; j < 6; j++) {
    GL.glColor3d(color[j,0], color[j,1], color[j,2]);
    for (i = 0; i < 4; i++) {
  	  GL.glVertex3d(vertex[face[j,i],0], vertex[face[j,i],1], vertex[face[j,i],2]);
// 	  GL.glVertex3d(vertex[edge[i,0],0], vertex[edge[i,0],1], vertex[edge[i,0],2]);
//	  GL.glVertex3d(vertex[edge[i,1],0], vertex[edge[i,1],1], vertex[edge[i,1],2]);
    }
  }
  GL.glEnd();
  GL.glutSwapBuffers();
  if (++r >= 360) r = 0;
}

void resize(int w, int h)
{
  GL.glViewport(0, 0, w, h);

  GL.glMatrixMode(GL.GL_PROJECTION);
  GL.glLoadIdentity();
  GL.gluPerspective(30.0, (Float)w/(Float)h, 1.0, 100.0);
  GL.glMatrixMode(GL.GL_MODELVIEW);

}

void idle_func()
{
  GL.glutPostRedisplay();
}

void init()
{
  GL.glClearColor(1.0, 1.0, 1.0, 1.0);
  GL.glEnable(GL.GL_DEPTH_TEST);
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
  init_edge();
  init_face();
  init_color();
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

