#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "../util.h"

#include "clock.h"

#define MAX_SIZE_DATE 29
#define MAX_SIZE_TIME 9
#define MAX_SIZE_DATE_COMPONENTS 5
#define MAX_SIZE_TIME_COMPONENTS 4
#define YEAR_TM 1900

char *getDay(int number)
{
 char *day = calloc(10, sizeof(char));
 switch(number)
 {
   case 0: strcpy(day, "Sunday"); break;
   case 1: strcpy(day, "Monday"); break;
   case 2: strcpy(day, "Tuesday"); break;
   case 3: strcpy(day, "Wednesday"); break;
   case 4: strcpy(day, "Thursday"); break;
   case 5: strcpy(day, "Friday"); break;
   case 6: strcpy(day, "Saturday"); break;
 }
 return day;
}

char *getMonth(int number)
{
 char *month = calloc(10, sizeof(char));
 switch(number)
 {
   case 0: strcpy(month, "January"); break;
   case 1: strcpy(month, "February"); break;
   case 2: strcpy(month, "March"); break;
   case 3: strcpy(month, "April"); break;
   case 4: strcpy(month, "May"); break;
   case 5: strcpy(month, "June"); break;
   case 6: strcpy(month, "July"); break;
   case 7: strcpy(month, "August"); break;
   case 8: strcpy(month, "September"); break;
   case 9: strcpy(month, "October"); break;
   case 10: strcpy(month, "November"); break;
   case 11: strcpy(month, "December"); break;
 }
 return month;
}

void clockWidget(float offsetX, float offsetY)
{
     //un-comment for local testing:
     //offsetX = offsetY = 0;
     time_t ts;
     struct tm *ct;

     ts = time(NULL);
     ct = localtime(&ts);

     char *day_date_month_year = calloc(MAX_SIZE_DATE, sizeof(char));

     char *day = getDay(ct->tm_wday);
     char *month = getMonth(ct->tm_mon);


     int dateInt = ct->tm_mday;
     char dateStr[MAX_SIZE_DATE_COMPONENTS];
     sprintf(dateStr, "%d", dateInt);

     // The struct tm starts counting the number of years since YEAR_TM(1900)
     int yearInt = ct->tm_year + YEAR_TM;
     char yearStr[MAX_SIZE_DATE_COMPONENTS];
     sprintf(yearStr, "%d", yearInt);

     strcpy(day_date_month_year, day);
     strcat(day_date_month_year, ", ");
     strcat(day_date_month_year, dateStr);
     strcat(day_date_month_year, " ");
     strcat(day_date_month_year, month);
     strcat(day_date_month_year, " ");
     strcat(day_date_month_year, yearStr);


     char *hour_min_sec = calloc(MAX_SIZE_TIME, sizeof(char));

     int hourInt = ct->tm_hour;
     char hourStr[MAX_SIZE_TIME_COMPONENTS];
     sprintf(hourStr, "%02d", hourInt);

     int minInt = ct->tm_min;
     char minStr[MAX_SIZE_TIME_COMPONENTS];
     sprintf(minStr, "%02d", minInt);

     int secInt = ct->tm_sec;
     char secStr[MAX_SIZE_TIME_COMPONENTS];
     sprintf(secStr, "%02d", secInt);

     strcat(hour_min_sec, hourStr);
     strcat(hour_min_sec, ":");
     strcat(hour_min_sec, minStr);
     strcat(hour_min_sec, ":");
     strcat(hour_min_sec, secStr);

     printMessage(day_date_month_year, offsetX, offsetY, 0.2, 2);
     printMessage(hour_min_sec, offsetX, offsetY + 55, 0.5, 6);


     free(day);
     free(month);
     free(day_date_month_year);
     free(hour_min_sec);
}
