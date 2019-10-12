#ifndef UTIL_H
#define UTIL_H
typedef struct point {
  int x, y;
} point_t;

void printMessage(char* message, float x, float y, float size, float thiccness);

void drawLine(point_t start, point_t end, float thiccness);
#endif
