#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <time.h>

#include <pthread.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../util.h"

#define WIDTH 500
#define HEIGHT 500
#define SCALE (0.6)

#define MAX_LINE_LENGTH 512
#define MAX_AMT_EVENTS 10

static bool canCallAPI = true;
static int lastMinuteRead = -1;

enum Month {
  JANUARY   = 1,
  FEBRUARY  = 2,
  MARCH     = 3,
  APRIL     = 4,
  MAY       = 5,
  JUNE      = 6,
  JULY      = 7,
  AUGUST    = 8,
  SEPTEMBER = 9,
  OCTOBER   = 10,
  NOVEMBER  = 11,
  DECEMBER  = 12
};

static void printEvents(float offsetX, float offsetY);
static bool hasTime(char *dateAndTime);
static char *strclone(char *string);
static char *getMonth(enum Month monthId);

static void drawEventLine(char *line, float offsetX, float offsetY);
static void drawDateAndTime(char *dateAndTime, float offsetX, float offsetY);
static void drawDate(char *date, float offsetX, float offsetY);

static pthread_t thread_id;

void *refreshCalendar() {
  system("python3 widgets/quickstart.py");
  return NULL;
}

void calendarWidget(float offsetX, float offsetY) {
  time_t ts;
  struct tm *ct;

  ts = time(NULL);
  ct = localtime(&ts);
  if (canCallAPI) {
    canCallAPI = false;
    lastMinuteRead = ct->tm_min;
    pthread_create(&thread_id, NULL, refreshCalendar, NULL);
    // refreshCalendar();
  } else if (ct->tm_min != lastMinuteRead) {
    canCallAPI = true;
  }

  // Draw header
  glPushMatrix();
  glScalef(SCALE, SCALE, SCALE);
  offsetX /= SCALE;
  offsetY /= SCALE;

  printMessage("Following Events:", offsetX, offsetY, 0.5, 4);

  point_t start = {offsetX - 50, offsetY + 80};
  point_t end = {offsetX + 700, offsetY + 80};
  drawLine(start, end, 10);

  printEvents(offsetX, offsetY);
  glPopMatrix();
}

static void printEvents(float offsetX, float offsetY) {
  char line[MAX_LINE_LENGTH];

  FILE *file = fopen("widgets/events.txt", "r");

  offsetY += 100;
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    drawEventLine(line, offsetX, offsetY);
    offsetY += 100;
  }

  fclose(file);
}

static void drawEventLine(char *line, float offsetX, float offsetY) {
  char *linecpy = strclone(line);
  char *dateAndTime = malloc(sizeof(char) * MAX_LINE_LENGTH);
  char *eventName = malloc(sizeof(char) * MAX_LINE_LENGTH);

  char *ptr;

  // Get date and time
  ptr = strtok(linecpy, " ");
  strncpy(dateAndTime, ptr, MAX_LINE_LENGTH);

  // Get name of event
  ptr = strtok(NULL, "\n");
  strncpy(eventName, ptr, MAX_LINE_LENGTH);

  // Print line on left
  point_t start = {offsetX, offsetY};
  point_t end = {offsetX, offsetY + 70};
  drawLine(start, end, 0.5);
  // Print event name
  printMessage(eventName, offsetX + 50, offsetY, 0.3, 3);

  drawDateAndTime(dateAndTime, offsetX, offsetY);

  free(dateAndTime);
  free(eventName);
  free(linecpy);
}

static void drawDateAndTime(char *dateAndTime, float offsetX, float offsetY) {
  char *cpy = strclone(dateAndTime);
  char *time = malloc(sizeof(char) * MAX_LINE_LENGTH);
  char *date = malloc(sizeof(char) * MAX_LINE_LENGTH);
  char *ptr;
  assert(cpy);
  assert(date);
  assert(time);

  bool isTime = hasTime(cpy);

  ptr = strtok(cpy, "T");
  strncpy(date, ptr, MAX_LINE_LENGTH);
  drawDate(date, offsetX + 50, offsetY + 50);

  if (isTime) {
    ptr = strtok(NULL, "+");
    strncpy(time, ptr, 5);
    time[5] = '\0';
    printMessage(time, offsetX + 625, offsetY + 50, 0.2, 2);
  }

  free(date);
  free(time);
  free(cpy);
}

static void drawDate(char *date, float offsetX, float offsetY) {
  date += 5;
  int monthId = atoi(date);
  date += 3;
  char *month = getMonth(monthId);
  strcat(date, " ");
  strcat(date, month);
  printMessage(date, offsetX, offsetY, 0.2, 2);
  free(month);
}

static bool hasTime(char *dateAndTime) {
  return strchr(dateAndTime, 'T') != NULL;
}

static char *getMonth(enum Month monthId) {
  char *month = malloc(sizeof(char) * MAX_LINE_LENGTH);
  switch (monthId) {
    case JANUARY:
      strcpy(month, "January");
      break;
    case FEBRUARY:
      strcpy(month, "February");
      break;
    case MARCH:
      strcpy(month, "March");
      break;
    case APRIL:
      strcpy(month, "April");
      break;
    case MAY:
      strcpy(month, "May");
      break;
    case JUNE:
      strcpy(month, "June");
      break;
    case JULY:
      strcpy(month, "July");
      break;
    case AUGUST:
      strcpy(month, "August");
      break;
    case SEPTEMBER:
      strcpy(month, "September");
      break;
    case OCTOBER:
      strcpy(month, "October");
      break;
    case NOVEMBER:
      strcpy(month, "November");
      break;
    case DECEMBER:
      strcpy(month, "December");
      break;
    default:
      exit(EXIT_FAILURE);
  }
  return month;
}

static char *strclone(char *string) {
  size_t size = strlen(string) + 1;
  char *cpy = malloc(size);
  if (cpy) {
    memcpy(cpy, string, size);
  }
  return cpy;
}
