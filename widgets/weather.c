#include <curl/curl.h>
#include <GL/glut.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "SOIL/SOIL.h"

#include "weather.h"
#include "jsmn.h"
#include "../util.h"

#define MAX_LINE_LENGTH 512

static bool canCallAPI = true;
static int lastMinuteRead = -1;

struct url_data {
    size_t size;
    char* data;
};

size_t write_data(void *ptr, size_t size, size_t nmemb, struct url_data *data) {
    size_t index = data->size;
    size_t n = (size * nmemb);
    char* tmp;
    data->size += (size * nmemb);
    tmp = realloc(data->data, data->size + 1);
    data->data = tmp;
    memcpy((data->data + index), ptr, n);
    data->data[data->size] = '\0';

    return size * nmemb;
}

void loadTexture(GLuint* texture, char* path){
    *texture = SOIL_load_OGL_texture(path,
                                     SOIL_LOAD_AUTO,
                                     SOIL_CREATE_NEW_ID,
                                     SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
                                    );
}

void DrawImage(char filename,int x, int y) {
  glPushMatrix();

  glTranslatef(x, y, 0);
  glColor3f(1,1,1);
  glEnable(GL_TEXTURE_2D);
  if(canCallAPI) {
  glBindTexture(GL_TEXTURE_2D, filename);
  }

  // Draw a textured quad
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
  glTexCoord2f(0, 1); glVertex3f(0, 150, 0);
  glTexCoord2f(1, 1); glVertex3f(150, 150, 0);
  glTexCoord2f(1, 0); glVertex3f(150, 0, 0);
  glEnd();


  glDisable(GL_TEXTURE_2D);
  glPopMatrix();


  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);

  glPopMatrix();
}

char *handle_url(char* url) {
  CURL *curl;
  struct url_data data;
  data.size = 0;
  data.data = malloc(MAX_LINE_LENGTH);
  data.data[0] = '\0';

  curl = curl_easy_init();
  if (curl) {
      curl_easy_setopt(curl, CURLOPT_URL, url);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);
      curl_easy_perform(curl);
      curl_easy_cleanup(curl);
  }
  return data.data;
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

const char *fetchData() {
  char* request = "http://api.openweathermap.org/data/2.5/weather?q=London&units=metric&appid=6572b870e0cd03b18e3492fde5f2bcd7";
  FILE *file = fopen("widgets/weather_data.txt", "rw");
  static char data[MAX_LINE_LENGTH];
  time_t ts;
  struct tm *ct;

  ts = time(NULL);
  ct = localtime(&ts);

  if (canCallAPI) {
    canCallAPI = false;
    lastMinuteRead = ct->tm_min;
    char *tempData = handle_url(request);
    strcpy(data, tempData);
    free(tempData);
    fprintf(file, "%s", data);
    fclose(file);
    return data;
  } else if (ct->tm_min != lastMinuteRead) {
    canCallAPI = true;
  }

  fgets(data, MAX_LINE_LENGTH, file);
  fclose(file);
  return data;
}

char *getInfo(char *info) {
  char *result = calloc(20, sizeof(char));
  jsmn_parser p;
  jsmntok_t t[128];

  char data[MAX_LINE_LENGTH];
  strcpy(data, fetchData());

  jsmn_init(&p);
  int r = jsmn_parse(&p, data, strlen(data), t, sizeof(t)/sizeof(t[0]));

  for (int i = 1; i < r; i++) {
    if (jsoneq(data, &t[i], info) == 0 && t[i + 1].end - t[i + 1].start <= 20) {
    strncpy(result, data + t[i + 1].start, t[i + 1].end - t[i + 1].start);
    return result;
      i++;
    }
  }
  return result;
}

void weatherWidget(float offsetX, float offsetY) {
  char *temp = getInfo("temp");
  float temp_flt = strtof(temp, NULL);
  sprintf(temp, "%2.1fC", temp_flt);
  printMessage(temp, offsetX, offsetY, 0.4, 5);
  free(temp);

  char *status  = getInfo("main");
  printMessage(status, offsetX, offsetY + 180, 0.35, 3);
  GLuint texture;
  if (strcmp(status, "Rain") == 0) {
    loadTexture(&texture, "widgets/rain.png");
  } else if (strcmp(status, "Clear") == 0) {
    loadTexture(&texture, "widgets/sun.png");
  } else if (strcmp(status, "Clouds") == 0) {
    loadTexture(&texture, "widgets/cloud.png");
  }
  free(status);


  char *location =  getInfo("name");
  printMessage(location, offsetX + 250, offsetY, 0.25, 3);
  free(location);

  // Drawing part
  DrawImage(texture, offsetX + 130, offsetY + 50);
}
