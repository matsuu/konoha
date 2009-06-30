using opengl.*;
using math.*;

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


int switch1 = 1;
float r = 0.0;
float zoom = 1.0;

void cube(int dx, int dy, int dz)
{
  GL.glBegin(GL.GL_QUADS);
  for (j = 0; j < 6; j++) {
	  GL.glColor3d(color[j,0], color[j,1], color[j,2]);
    for (i = 0; i < 4; i++) {
  	  GL.glVertex3d(vertex[face[j,i],0] + dx,
			vertex[face[j,i],1] + dy,
			vertex[face[j,i],2] + dz);
    }
  }
  GL.glEnd();

}

void go_display()
{
  int i;
  int j;
  
  GL.glClear(GL.GL_COLOR_BUFFER_BIT| GL.GL_DEPTH_BUFFER_BIT);
  GL.glLoadIdentity();
  // gluLookAt(x, y, z, lookat(x,y,z), direction(x,y,z))
  pi = Math.PI;
  GL.gluLookAt(zoom * 5.0 * Math.cos(2 * pi * r / 360),
	       4.0,
	       zoom * 5.0 * Math.sin(2 * pi * r / 360),
	       0.0, 0.0, 0.0, 
	       0.0, 1.0, 0.0);  

  GL.glPushMatrix();
  for (i = -5; i<= 5; i++) {
	  for (j = -5; j <= 5; j++) {
		  for (k = -5; k <= 5; k++) {
			  if (i % 2 == 0 || j % 2 == 0|| k % 2 == 0) {
				  cube(i*2, j*2, k*2);
			  }
		  }
	  } 
  }
  GL.glPopMatrix();
  GL.glutSwapBuffers();
  if (r >= 180) r = -179;
  if (r <= -180) r = 179;
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

void keyboard(int keycode, int x, int y)
{
	Closure c;
	if (keycode == GL.GLUT_KEY_LEFT) {
	  r = r + 5;
	} else if(keycode == GL.GLUT_KEY_RIGHT) {
	  r = r - 5;
	} else if (keycode == GL.GLUT_KEY_UP) {
	  zoom = zoom + 0.05;
	} else if (keycode == GL.GLUT_KEY_DOWN) {
	  zoom = zoom - 0.05;
	} else {
//	  c = delegate(idle_func);
//	  GL.glutIdleFunc(c);
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
  Closure id = delegate(idle_func);
  GL.glutIdleFunc(id);
  Closure key = delegate(keyboard);
  GL.glutSpecialFunc(key);
  GL.glEnable(GL.GL_POLYGON_SMOOTH);
  GL.glEnable(GL.GL_BLEND);
  GL.glBlendFunc(GL.GL_SRC_ALPHA, GL.GL_ONE_MINUS_SRC_ALPHA);
  init();
  GL.glutMainLoop();

  return 0;
}

