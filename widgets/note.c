#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>

#include "../util.h"

#define MAX_LINE_LEN 512
#define MAX_NOTE_WIDTH 20
#define SCALE 15

void noteWidget(float offsetX, float offsetY) {
  FILE *file = fopen("widgets/quotes.txt", "r");
  int length = 0;
  int adjust = 25;

  char buffer[MAX_LINE_LEN];
  char line[MAX_LINE_LEN];
  char *ptr;

  while (fgets(buffer, MAX_LINE_LEN, file) != 0) {
    ptr = strtok(buffer, " \n");

    if (length + strlen(ptr) + 1 > MAX_NOTE_WIDTH) {
      printMessage(line, offsetX + 5, offsetY + adjust, 0.18, 2);
      adjust += 50;
      strcpy(line, "");
      length = 0;
    }
    length += strlen(ptr) + 1;
    strcat(line, " ");
    strcat(line, ptr);
    while ((ptr = strtok(NULL, " \n"))) {
      if (length + strlen(ptr) > MAX_NOTE_WIDTH) {
        printMessage(line, offsetX + 5, offsetY + adjust, 0.18, 2);
        adjust += 50;
        strcpy(line, "");
        length = 0;
      }
      length += strlen(ptr) + 1;
      strcat(line, " ");
      strcat(line, ptr);
    }
    printMessage(line, offsetX + 5, offsetY + adjust, 0.18, 2);
    adjust += 50;
    strcpy(line, "");
    length = 0;
  }

  fclose(file);

  // Increase the scale to increase the size of the note
  glBegin(GL_LINE_STRIP);
  glVertex2f(offsetX, offsetY);
  glVertex2f(offsetX, offsetY + 20 * SCALE);
  glVertex2f(offsetX + 2 * SCALE, offsetY + 25 * SCALE);
  glVertex2f(offsetX + 20 * SCALE, offsetY + 25 * SCALE);
  glVertex2f(offsetX + 20 * SCALE, offsetY);
  glVertex2f(offsetX, offsetY);
  glEnd();
}
