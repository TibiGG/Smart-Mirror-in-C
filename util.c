#include <string.h>
#include <GL/glut.h>

#include "util.h"

void printMessage(char* message, float x, float y, float size, float thiccness) {
  int len, i;
  void *font = GLUT_STROKE_ROMAN;
  glLineWidth(thiccness);


  glPushMatrix();
  glTranslatef(x, y + size * 100, 0);
	glScalef(size,-size, size);
  len = (int) strlen(message);
  for (i = 0; i < len; i++) {
    glutStrokeCharacter(font, message[i]);
  }
  glPopMatrix();
}

void drawLine(point_t start, point_t end, float thiccness) {
  // glPointSize(thiccness);
  glBegin(GL_LINES);
    glVertex2f(start.x, start.y);
    glVertex2f(end.x, end.y);
  glEnd();
}
