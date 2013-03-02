/* 
 * File:   main.c
 * Author: ljs5
 *
 * Created on 28 November 2012, 17:26
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

struct event * new_event;
struct node * nodes;
struct track * tracks;
struct course * courses;

int num_of_nodes;
int num_of_tracks;
int num_of_courses;

int line_num(char * file_name);

/*
 * 
 */
int main(int argc, char** argv) {
    //holds the filenames of the files to be read
    char event_filename[100];
    char node_filename[100];
    char track_filename[100];
    char course_filename[100];
    char entrant_filename[100];

    int file_status;
    /* get input for name of event file */
    do {
        printf("Please enter the filename of the event name file: \n");
        scanf("%s", event_filename);
        file_status = check_file(event_filename);
    } while (file_status == 0);
    new_event = get_event_details(event_filename);
    print_event();
    /* get input for nodes file loop while file incorrect */
    do {
        printf("Please enter the filename of the nodes file: \n");
        scanf(" %s", node_filename);
        file_status = check_file(node_filename);
    } while (file_status == 0);
    nodes = get_node_file(node_filename);
    print_nodes();
    /* get input for track file loop while file incorrect */
    do {
        printf("Please enter the filename of the tracks file: \n");
        scanf(" %s", track_filename);
        file_status = check_file(track_filename);
    } while (file_status == 0);
    tracks = get_tracks_file(track_filename, nodes);
    print_tracks();
    /* get input for courses file loop while file incorrect */
    do {
        printf("Please enter the filename of the courses file: \n");
        scanf(" %s", course_filename);
        file_status = check_file(course_filename);
    } while (file_status == 0);
    courses = get_courses_file(course_filename, nodes);
    print_courses();
    /* get input for entrants file loop while file incorrect */
    do {
        printf("Please enter the filename of the entrants file: \n");
        scanf(" %s", entrant_filename);
        file_status = check_file(entrant_filename);
    } while (file_status == 0);
    get_entrants_file(entrant_filename, new_event, courses);
    print_entrants();

    int user_choice;
    /* loop until user selected exit from menu */
    while (user_choice != EXIT) {
        user_choice = get_user_choice();

        switch (user_choice) {
                /* view a single entrant*/
            case VIEW_ENTRANT:
            {
                int entrant_selected;
                printf("Enter Entrant Number: \n");
                scanf("%d", &entrant_selected);
                printf("|| Num  | Course | Name                                               | Last Checkpoint | Type | Check-In Time| Location | Current Time ||\n");
                view_entrant(entrant_selected);
                break;
            }
                /* view entrants not started */
            case ENTRANTS_NOT_STARTED:
            {
                struct entrant * tmp_entrant;
                tmp_entrant = new_event->first_entrant;
                printf("Entrants Not started\n\n");
                printf("|| Num  | Course | Name                                               | Last Checkpoint | Type | Check-In Time| Location | Current Time ||\n");
                do {
                    if (tmp_entrant->status == NOT_STARTED) {
                        view_entrant(tmp_entrant->entrant_number);
                    }
                    tmp_entrant = tmp_entrant->next_entrant;
                } while (tmp_entrant != NULL);
                break;
            }
                /* view entrants that are on course */
            case ENTRANTS_ON_COURSE:
            {
                struct entrant * tmp_entrant;
                tmp_entrant = new_event->first_entrant;
                printf("Entrants on course\n\n");
                printf("|| Num  | Course | Name                                               | Last Checkpoint | Type | Check-In Time| Location | Current Time ||\n");
                do {
                    if (tmp_entrant->status == ON_COURSE) {
                        view_entrant(tmp_entrant->entrant_number);
                    }
                    tmp_entrant = tmp_entrant->next_entrant;
                } while (tmp_entrant != NULL);
                break;
            }
                /* view entrants that have finished the course */
            case ENTRANTS_FINISHED:
            {
                struct entrant * tmp_entrant;
                tmp_entrant = new_event->first_entrant;
                printf("Finished Entrants\n\n");
                printf("|| Num  | Course | Name                                               | Last Checkpoint | Type | Check-In Time| Location | Current Time ||\n");
                do {
                    if (tmp_entrant->status == FINISHED) {
                        view_entrant(tmp_entrant->entrant_number);
                    }
                    tmp_entrant = tmp_entrant->next_entrant;
                } while (tmp_entrant != NULL);
                break;
            }
                /* enter a individual time for a entrant */
            case ENTER_TIME_FOR_COMP:
            {
                int entrant_number;
                int node_number;
                int time_hour;
                int time_minute;
                printf("Please Enter the entrants number: \n");
                scanf(" %d", &entrant_number);
                printf("Please Enter the Node Number: \n");
                scanf(" %d", &node_number);
                printf("Please enter the check-in time (Hour): \n");
                scanf(" %d", &time_hour);
                printf("Please enter the check-in time (Minute): \n");
                scanf(" %d", &time_minute);
                struct time new_time;
                new_time.hour = time_hour;
                new_time.minute = time_minute;
                new_event->current_time = new_time;
                entrant_checkin(entrant_number, node_number, nodes, new_event, new_time, 'T');
                update_competitors(new_event);
                break;
            }
                /* print a full list of entrants */
            case PRINT_LIST:
            {
                struct entrant * tmp_entrant;
                tmp_entrant = new_event->first_entrant;
                printf("|| Num  | Course | Name                                               | Last Checkpoint | Type | Check-In Time| Location | Current Time ||\n");
                do {
                    view_entrant(tmp_entrant->entrant_number);
                    tmp_entrant = tmp_entrant->next_entrant;
                } while (tmp_entrant != NULL);
                printf("Current Event Time: %d:%d\n\n", new_event->current_time.hour, new_event->current_time.minute);
                break;
            }
                /* reads in a file containing checkpoints check ins*/
            case READ_IN_FILE:
            {
                char filename[100];
                do {
                    printf("Enter File name: \n");
                    scanf("%s", filename);
                    file_status = check_file(filename);
                } while (file_status == 0);

                read_checkpoint_times(filename, new_event);
                break;
            }
            case EXIT:
            {
                printf("Thank you for using this program!\n");
            }
        }
    }



    return (EXIT_SUCCESS);
}

/* Check if a file is a existing file */
int check_file(char * filename) {
    FILE * check_file;
    int retval;
    check_file = fopen(filename, "r");

    if (check_file == NULL) {
        printf("File does not exist\n");
        retval = 0;
    } else {
        retval = 1;
    }
    return retval;
}

/* reads in checkpoints from the file */
void read_checkpoint_times(char * filename, struct event * new_event) {
    FILE * read_file;
    read_file = fopen(filename, "r");

    char check_type;
    int checkpoint_number;
    int entrant_number;
    int check_hour;
    int check_minute;
    struct time check_time;
    while (!feof(read_file)) {
        fscanf(read_file, "%c %d %d %d:%d\n", &check_type, &checkpoint_number, &entrant_number, &check_hour, &check_minute);
        check_time.hour = check_hour;
        check_time.minute = check_minute;
        new_event->current_time = check_time;
        entrant_checkin(entrant_number, checkpoint_number, nodes, new_event, check_time, check_type);
    }
    printf("Finished processing file.\n");
    /* update the competitors and estimated location based on the 
       current time in the event                                        */
    update_competitors(new_event);
}

/* Function to get the difference between 2 times */
struct time get_time_diff(struct time start_time, struct time check_time) {
    int start_time_minutes = (start_time.hour * 60) + start_time.minute;
    int check_time_minutes = (check_time.hour * 60) + check_time.minute;
    int time_diff = check_time_minutes - start_time_minutes;
    struct time new_time;
    new_time.hour = time_diff / 60;
    new_time.minute = time_diff % 60;
    return new_time;
}

/* function to convert a time struct into a minutes integer */
int time_min(struct time con_time) {
    int minutes = 0;
    minutes = con_time.hour * 60;
    minutes = minutes + con_time.minute;
    return minutes;
}

/* update a entrant that has checked in */
void entrant_checkin(int competitor_number, int checkpoint_number, struct node * nodes, struct event * new_event, struct time new_time, char check_type) {
    int found = 0;
    struct entrant * update_entrant = new_event->first_entrant;
    while (found == 0) {
        if (update_entrant->entrant_number == competitor_number) {
            found = 1;
            if (nodes[checkpoint_number - 1].type == JN) {
                printf("Error: Entered Node is not a checkpoint\n");
                printf("Check not recorded\n\n");
            } else {
                /* only if the entrant has not yet started a course */
                if (update_entrant->status == NOT_STARTED) {
                    update_entrant->last_checkpoint = nodes[checkpoint_number - 1];
                    update_entrant->checkpoints_reached++;
                    update_entrant->next_expected_checkpoint = get_next_expected_checkpoint(update_entrant);
                    update_entrant->start_time = new_time;
                    update_entrant->last_checkin = new_time;
                    update_entrant->status = ON_COURSE;
                    /* if the entrant is on a course */
                } else if (update_entrant->status == ON_COURSE) {
                    /* check if the entrant has returned to the first checkpoint (start)*/
                    if (update_entrant->course_entered->nodes_list[0].node_number == nodes[checkpoint_number - 1].node_number) {
                        update_entrant->status = FINISHED;
                        /* get the entrants time for the course not include medical */
                        struct time course_finish = get_time_diff(update_entrant->start_time,
                                update_entrant->last_checkin);
                        struct time medi_time = get_time_diff(update_entrant->leave_medical, 
                                update_entrant->start_medical);
                        update_entrant->course_time = get_time_diff(medi_time, course_finish);
                    }
                    struct node entrant_expected_node = update_entrant->next_expected_checkpoint;
                    struct node entrant_arrived_node = nodes[checkpoint_number - 1];
                    /* entrant checks in at checkpoint */
                    if (check_type == 'A') {
                        update_entrant->last_checkpoint = nodes[checkpoint_number - 1];
                        update_entrant->checkpoints_reached++;
                        update_entrant->last_checkin = new_time;
                        update_entrant->start_medical = new_time;
                        /* entrant departs checkpoint */
                    } else if (check_type == 'D') {
                        update_entrant->last_checkpoint = nodes[checkpoint_number - 1];
                        update_entrant->next_expected_checkpoint = get_next_expected_checkpoint(update_entrant);
                        update_entrant->last_checkin = new_time;
                        update_entrant->leave_medical = new_time;
                        /* Disqualified for failing medical */
                    } else if (check_type == 'I' && checkpoint_number == 14) {
                        update_entrant->status = DISQUALIFIEDMC;
                        /* checks if the entrant has checked in at an incorrect node */
                    } else if (entrant_expected_node.node_number != entrant_arrived_node.node_number 
                            || (check_type == 'I') && checkpoint_number != 14) {
                        update_entrant->status = DISQUALIFIEDWC;
                    } else {
                        update_entrant->last_checkpoint = nodes[checkpoint_number - 1];
                        update_entrant->checkpoints_reached++;
                        update_entrant->next_expected_checkpoint = get_next_expected_checkpoint(update_entrant);
                        update_entrant->last_checkin = new_time;
                    }
                }
                printf("Entrant Updated:\n \tEntrant Number: %d\n\tType: %c\n\tCheckpoint: "
                        "%d\n\tTime: %02d:%02d\n", 
                        update_entrant->entrant_number,
                        check_type,
                        update_entrant->last_checkpoint.node_number,
                        update_entrant->last_checkin.hour,
                        update_entrant->last_checkin.minute);
            }
        } else {
            update_entrant = update_entrant->next_entrant;
        }
    }
}

/* Update the competitors based on the current time in the event */
void update_competitors(struct event * new_event) {
    struct entrant * this_entrant;
    this_entrant = new_event->first_entrant;
    while (this_entrant != NULL) {
        /* only do this if the entrant is on a course */
        if (this_entrant->status == ON_COURSE) {
            struct time course_finish = get_time_diff(this_entrant->start_time, this_entrant->last_checkin);
            struct time medi_time = get_time_diff(this_entrant->leave_medical, this_entrant->start_medical);
            this_entrant->course_time = get_time_diff(medi_time, course_finish);
            struct time blank_time;
            blank_time.hour = 0;
            blank_time.minute = 0;
            if (time_min(this_entrant->start_medical) != time_min(blank_time) && time_min(this_entrant->leave_medical) == time_min(blank_time)) {

            } else {
                this_entrant->estimated_track = view_entrant_location(this_entrant);
            }

        }
        this_entrant = this_entrant->next_entrant;
    }
}

/* find out the next checkpoint that an entrant is expected to be at */
struct node get_next_expected_checkpoint(struct entrant * entrant) {
    int i;
    int checked_nodes = 0;
    struct node next_node;

    if (entrant->checkpoints_reached == 1) {
        for (i = 1; i < entrant->course_entered->num_nodes_in_course; i++) {
            if (entrant->course_entered->nodes_list[i].type == CP || entrant->course_entered->nodes_list[i].type == MC) {
                next_node = entrant->course_entered->nodes_list[i];
                return next_node;
            }
        }
    } else {
        for (i = 1; i < entrant->course_entered->num_nodes_in_course; i++) {
            if (entrant->course_entered->nodes_list[i].type == CP || entrant->course_entered->nodes_list[i].type == MC) {
                checked_nodes++;
                if (checked_nodes == entrant->checkpoints_reached) {
                    if (entrant->course_entered->nodes_list[i].type == MC) {
                        next_node = entrant->course_entered->nodes_list[i - 1];
                    } else {
                        next_node = entrant->course_entered->nodes_list[i];
                    }

                    return next_node;
                }
            }
        }
    }
}

/* returns the track that the entrant is expected to be on */
struct track * view_entrant_location(struct entrant * entrant) {
    int entrant_time_mins = time_min(entrant->course_time);
    struct track * curr_track;
    int i = 0;
    while (entrant_time_mins > -1) {
        curr_track = get_track(entrant, i);
        entrant_time_mins = entrant_time_mins - curr_track->estimated_time;
        i++;
    }
    return curr_track;
}

/* Finds the tracks based on the entrants current position and time */
struct track * get_track(struct entrant * entrant, int i) {
    int j;
    struct track * selected_track;
    struct node node1 = entrant->course_entered->nodes_list[i];
    struct node node2 = entrant->course_entered->nodes_list[i + 1];
    for (j = 0; j < num_of_tracks; j++) {
        if (tracks[j].start_node.node_number == node1.node_number && tracks[j].end_node.node_number == node2.node_number) {
            selected_track = &tracks[j];
            break;
        } else if (tracks[j].start_node.node_number == node2.node_number && tracks[j].end_node.node_number == node1.node_number) {
            selected_track = &tracks[j];
            break;
        }
    }
    return selected_track;
}

/* prints out an entrant */
void view_entrant(int entrant_selected) {
    struct entrant * view_comp;
    view_comp = new_event->first_entrant;
    int found = 0;
    while (found != 1) {
        if (view_comp->entrant_number != entrant_selected) {
            view_comp = view_comp->next_entrant;
        } else {
            found = 1;
            printf("|| %3d  ", view_comp->entrant_number);
            printf("| %4c   | ", view_comp->course_entered->course_name);
            printf("%-50s | ", view_comp->entrant_name);
            if (view_comp->status == NOT_STARTED) {
                printf("                         %s                        ||\n", "NOT YET STARTED");
            } else if (view_comp->status == DISQUALIFIEDMC) {
                printf("                       %s                   ||\n", " DISQUALIFIED MEDICAL ");
            } else if (view_comp->status == DISQUALIFIEDWC) {
                printf("                  %s               ||\n", " DISQUALIFIED WRONG CHECKPOINT ");
            } else {
                printf("%8d        | ", view_comp->last_checkpoint.node_number);
                if (view_comp->last_checkpoint.type == CP) {
                    printf(" %2s  | ", "CP");
                } else if (view_comp->last_checkpoint.type == JN) {
                    printf(" %2s  | ", "JN");
                } else if (view_comp->last_checkpoint.type == MC) {
                    printf(" %2s  | ", "MC");
                }
                printf("    %02d:%02d    |", view_comp->last_checkin.hour, view_comp->last_checkin.minute);
                if (view_comp->status == FINISHED) {
                    printf("  FINISH  |");
                    printf("     %02d:%02d    ||\n", view_comp->course_time.hour, view_comp->course_time.minute);
                } else {
                    struct time blank_time;
                    blank_time.hour = 0;
                    blank_time.minute = 0;
                    if (time_min(view_comp->start_medical) != time_min(blank_time) && time_min(view_comp->leave_medical) == time_min(blank_time)) {
                        printf("    MEDICAL CHECKPOINT   ||\n");
                    } else {
                        printf(" Track %2d |", view_comp->estimated_track->track_number);
                        printf("     %02d:%02d    ||\n", view_comp->course_time.hour, view_comp->course_time.minute);
                    }
                }

            }
        }
    }


}

/* following functions print out the information read from files */
void print_event() {
    printf("Event Name: %s\n", new_event->event_name);
    printf("Event Date: %d %s %d\n", new_event->date_of_event.date, new_event->date_of_event.month, new_event->date_of_event.year);
    printf("Event Time: %02d:%02d\n\n", new_event->time_of_event.hour, new_event->time_of_event.minute);
}

void print_nodes() {
    int j;
    for (j = 0; j < num_of_nodes; j++) {
        printf("Node: %d type: ", nodes[j].node_number);
        if (nodes[j].type == CP) {
            printf("CP\n");
        } else if (nodes[j].type == JN) {
            printf("JN\n");
        } else if (nodes[j].type == MC) {
            printf("MC\n");
        }
    }
}

void print_tracks() {
    int i;
    for (i = 0; i < num_of_tracks; i++) {
        printf("Track No: %d SN: %d EN: %d, Time: %d\n", tracks[i].track_number, tracks[i].start_node.node_number, tracks[i].end_node.node_number, tracks[i].estimated_time);
    }
}

void print_courses() {
    int j, k;
    for (j = 0; j < num_of_courses; j++) {
        printf("Course Name: %c Num tracks: %d", courses[j].course_name, courses[j].num_nodes_in_course);
        for (k = 0; k < courses[j].num_nodes_in_course; k++) {
            printf(" %d", courses[j].nodes_list[k].node_number);
        }
        printf("\n");
    }
}

void print_entrants() {
    struct entrant * tmp_entrant = new_event->first_entrant;
    while (tmp_entrant != NULL) {
        printf("Ent Num: %02d Course Entered: %c Ent Name: %s\n", tmp_entrant->entrant_number, tmp_entrant->course_entered->course_name, tmp_entrant->entrant_name);
        tmp_entrant = tmp_entrant->next_entrant;

    }
}

/* main menu function returning the users choice */
int get_user_choice() {
    int choice;
    printf("Please select and option: \n");
    printf("%d -> View Entrant\n", VIEW_ENTRANT);
    printf("%d -> See Entrants not Started\n", ENTRANTS_NOT_STARTED);
    printf("%d -> See Entrants on courses\n", ENTRANTS_ON_COURSE);
    printf("%d -> See Competitors that have finished\n", ENTRANTS_FINISHED);
    printf("%d -> Enter a Time for a competitor\n", ENTER_TIME_FOR_COMP);
    printf("%d -> Read in file of times\n", READ_IN_FILE);
    printf("%d -> Print Competitors\n", PRINT_LIST);
    printf("%d -> Exit\n", EXIT);
    scanf(" %d", &choice);
    return choice;
}

/* function to count the number of lines in a file */
int line_num(char * file_name) {
    FILE * file_ptr;
    char c;
    int line_count = 0;
    file_ptr = fopen(file_name, "r");

    if (file_ptr == NULL) {
        return 0;
    }

    while ((c = fgetc(file_ptr)) != EOF) {
        if (c == '\n') {
            line_count++;
        }
    }
    fclose(file_ptr);
    return line_count;
}

