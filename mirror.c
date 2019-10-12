#include <string.h>
#include <GL/glut.h>
#include "widgets/clock.h"
#include "widgets/calendar.h"
#include "widgets/note.h"
#include "widgets/weather.h"
#include "util.h"

#define RESOLUTION_X 1080
#define RESOLUTION_Y 1920

void init(int argc, char **argv);


int main(int argc, char **argv)
{
  init(argc, argv);
  return 0;
}

void tick(void)
{
  //angle -= 2;
  glutPostRedisplay();
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);

  // MAKE CHANGES HERE
  clockWidget(100,100);
  weatherWidget(700, 100);
  calendarWidget(50,1300);
  noteWidget(700,1300);
  //--------------------

  glutSwapBuffers();
}

void init(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(RESOLUTION_X,RESOLUTION_Y);
  glutCreateWindow("Smart Mirror");
  glutFullScreen();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, RESOLUTION_X, RESOLUTION_Y, 0);
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glLineWidth(15.0);
  glTranslatef(0, 0, 0);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glColor3f(1.0, 1.0, 1.0);
  glutDisplayFunc(display);
  glutIdleFunc(tick);
  glutMainLoop();
}
