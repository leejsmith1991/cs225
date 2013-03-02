/* 
 * File:   entrant.c
 * Author: ljs5
 *
 * Created on 28 November 2012, 17:26
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"


/**
 * Read the file containing the list of entrants
 * @param file_name name of the file
 * @param new_event the event details
 * @param courses the courses for the event
 * @return the event containing the first entrant
 */
void get_entrants_file(char * file_name, struct event * new_event, struct course * courses) {
    FILE * entrants_file;
    char * mode = "r";
    int number_of_entrants;
    number_of_entrants = line_num(file_name);
    new_event->num_of_entrants = number_of_entrants;

    entrants_file = fopen(file_name, mode);
    while (!(feof(entrants_file))) {
        int entrant_number = 0;
        char course_letter;
        char entrant_name[50];
        struct course * entrant_course = malloc(sizeof(struct course));
        
        fscanf(entrants_file, "%d %c %[a-zA-Z ]\n", &entrant_number, &course_letter, entrant_name);
        entrant_course = get_entrant_course(course_letter, courses);
        add_entrant(entrant_number, entrant_course, entrant_name, new_event);
    }
    fclose(entrants_file);
}
/**
 * Adds element to the linked list of entrants
 * @param entrant_number 
 * @param entrant_course
 * @param entrant_name
 * @param new_event
 */
void add_entrant(int entrant_number, struct course * entrant_course, char * entrant_name, struct event * new_event) {
    //create memory for the entrant
    struct entrant * new_entrant = (struct entrant *)malloc(sizeof(struct entrant));
    struct time blank_time;
    blank_time.hour = 0;
    blank_time.minute = 0;
    new_entrant->entrant_number = entrant_number;
    new_entrant->course_entered = entrant_course;
    new_entrant->next_expected_checkpoint = entrant_course->nodes_list[0];
    new_entrant->start_medical = blank_time;
    new_entrant->leave_medical = blank_time;
    new_entrant->checkpoints_reached = 0;
    strcpy(new_entrant->entrant_name, entrant_name);
    new_entrant->next_entrant = NULL;  
    new_entrant->status = NOT_STARTED;
    //ask if the first element is set
    if (new_event->first_entrant == NULL) {
        new_event->first_entrant = new_entrant;
    } else {
        //loop through until the next entrant becomes NULL
        struct entrant * tmp_entrant = new_event->first_entrant;
       
        while (tmp_entrant->next_entrant != NULL) {
            tmp_entrant = tmp_entrant->next_entrant;
        }
        
        tmp_entrant->next_entrant = new_entrant;
    }
}
//return an individual course that an entrant will be competing on
struct course * get_entrant_course(char course_letter, struct course * courses){
    int i;
    int num_of_courses = courses->num_nodes_in_course;
                
    for (i=0; i < num_of_courses; i++){
        if(courses[i].course_name == course_letter){
            return &courses[i];
        }
    }
}
