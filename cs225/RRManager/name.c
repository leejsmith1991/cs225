/* 
 * File:   name.c
 * Author: ljs5
 *
 * Created on 28 November 2012, 17:26
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

/**
 * Read data in from the event name file
 * @param filename
 * @return the event struct
 */
struct event * get_event_details(char *filename) {
    struct event * new_event;
    new_event = (struct event*) malloc(sizeof (struct event));

    FILE *name_file;
    char *mode = "r";
    //create variables for the individual items in the file
    char event_name[MAX_EVENT_NAME];
    int event_date_num;
    struct date event_date;
    char event_date_suffix[3];
    char event_month[9];
    int event_year;
    struct time event_time;

    name_file = fopen(filename, mode);
    if (name_file != NULL) {
        while (feof(name_file) == 0) {
            fscanf(name_file, "%[A-Za-z -]\n", event_name);
            fscanf(name_file, "%2d%2s %s %4d\n", &event_date_num, event_date_suffix, event_month, &event_year);
            fscanf(name_file, "%2d:%2d\n", &event_time.hour, &event_time.minute);
        }
        event_date.date = event_date_num;
        strcpy(event_date.month, event_month);
        event_date.year = event_year;

        strcpy(new_event->event_name, event_name);
        new_event->date_of_event = event_date;
        new_event->time_of_event = event_time;
        new_event->first_entrant = NULL;

    } else {
        printf("Error location file");
        exit(1);
    }
    fclose(name_file);
    return new_event;
}
