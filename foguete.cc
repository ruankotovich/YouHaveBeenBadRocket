#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdlib>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static int i = 200;
static int fire = 0;
bool boost = false;
float angle = 0;

void Bico()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 1);
    glVertex3f(3.0, 6.0, 0);
    glVertex3f(4.0, 8.0, 0);
    glVertex3f(5.0, 6.0, 0);
    glEnd();
}

void Corpo()
{
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex3f(3.0, 1.0, 0);
    glVertex3f(5.0, 1.0, 0);
    glVertex3f(5.0, 6.0, 0);
    glVertex3f(3.0, 6.0, 0);
    glEnd();
}

void Fogo(){
	glBegin(GL_TRIANGLES);
	glColor3f((boost? .5: 1), (fire % 3 == 0? 0.0f : 1.0f)*(i>0?1:0), (boost? .9 : 0));	
	glVertex3f(4, -2.0*(i>0?1:0	) - (fire % 3 == 0? 0 : (i/50)*(boost? 30:1) ), 0);
	glVertex3f(3.0, 1.0, 0);
	glVertex3f(5.0, 1.0, 0);
	glEnd();
}

void AsaEsquerda()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);
    glVertex3f(1.5, 1.0, 0);
    glVertex3f(3.0, 1.0, 0);
    glVertex3f(3.0, 3.0, 0);
    glEnd();
}

void AsaDireita()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0, 1, 0);
    glVertex3f(5.0, 1.0, 0);
    glVertex3f(6.5, 1.0, 0);
    glVertex3f(5.0, 3.0, 0);
    glEnd();
}

void draw()
{

    glClearColor(0.0f, .0f, .1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(angle , 0, 0, 1);
    glTranslatef(0, (i/100.0f + (boost? (i/50) : 0 )), 0);
    Bico();
    Corpo();
    AsaEsquerda();
    AsaDireita();
	Fogo();
    glutSwapBuffers();

    glutPostRedisplay();
    glFlush();
}

void makedelay(int)
{

	++fire;
    draw();
    glutTimerFunc(40, makedelay, 1);
}

void init()
{
    glClearColor(0.0f, .0f, .1f, 1.0f);
    glPointSize(1.0);
    gluOrtho2D(100, -100, -100, 100);
}

void keyboard(unsigned char key, int x, int y)
{
	//fechar
    if (key == 'e' || key == 'E')
        exit(0);
    // espaço - boost
    if(key == 32 && i > 0)
    	boost = !boost;
    // desacelerar
   	if(key == 's')
   		i -= (i >= 10? 10 : 0);
   		if(i==0){
  			angle = 0; 			
   		}
   		
   	if(key == 'w')
   		i += i==0? 100 : 10;
    if(key == 'a' && i > 0)
		angle = angle < 90? 355: angle - 5;
	if(key == 'd' && i > 0)
		angle = angle > 90? 5 : angle + 5;
	if(key =='x')
		angle = 0;
		
}


int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Janelinea");
    init();
    glutKeyboardFunc(keyboard);
    glutTimerFunc(40, makedelay, 1);
    glutMainLoop();

    return 0;
}