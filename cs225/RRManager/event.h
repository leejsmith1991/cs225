/*
 * File:   event.h
 * Author: ljs5
 *
 * Created on 28 November 2012, 17:26
 */

#define MAX_EVENT_NAME 79
#define MODE_FILE_READ "r";

struct date {
    int date;
    char month[9];
    int year;
};

struct time {
    int hour;
    int minute;
};

struct event {
    char event_name[MAX_EVENT_NAME];
    struct date date_of_event;
    struct time time_of_event;
    struct time current_time;
    int num_of_entrants;
    int num_of_tracks;
    struct entrant * first_entrant;
};

enum checkpoint_type {
    CP,
    JN,
    MC,
};

struct node {
    int node_number;
    enum checkpoint_type type;
};

struct track {
    int track_number;
    struct node start_node;
    struct node end_node;
    int estimated_time;
};

struct course {
    char course_name;
    int num_of_courses;
    int num_nodes_in_course;
    struct node * nodes_list;
};

enum entrant_status {
    NOT_STARTED,
    ON_COURSE,
    FINISHED,
    DISQUALIFIEDWC,
    DISQUALIFIEDMC
};

struct entrant {
    int entrant_number;
    char entrant_name[50];
    struct course * course_entered;

    enum entrant_status status;

    struct time start_time;
    int checkpoints_reached;
    struct time start_medical;
    struct time leave_medical;
    struct node last_checkpoint;
    struct time last_checkin;

    struct node next_expected_checkpoint;
    struct track * estimated_track;

    struct time course_time;

    struct entrant * next_entrant;
};

enum choice {
    VIEW_ENTRANT = 1,
    ENTRANTS_NOT_STARTED = 2,
    ENTRANTS_ON_COURSE = 3,
    ENTRANTS_FINISHED = 4,
    ENTER_TIME_FOR_COMP = 5,
    READ_IN_FILE = 6,
    PRINT_LIST = 7,
    EXIT = 8
};

/* Function Prototypes to read files */
struct node * get_node_file(char * file_name);
struct track * get_tracks_file(char * file_name, struct node * nodes);
struct course * get_courses_file(char * file_name, struct node * nodes);
void get_entrants_file(char * file_name, struct event * new_event, struct course * courses);
struct course * get_entrant_course(char course_letter, struct course * courses);

/* Function prototype to add entrants to linked list */
void add_entrant(int entrant_number, struct course * entrant_course, char * entrant_name, struct event * new_event);

/* Function Definitions */
struct event * get_event_details(char * filename);

/* Function prototype to read checkpoint files and update competitors*/
void read_checkpoint_times(char * filename, struct event * new_event);
void update_competitors(struct event * new_event);
void entrant_checkin(int competitor_number, int checkpoint_number, struct node * nodes, struct event * new_event, struct time new_time, char check_type);

/* Function prototypes to view entrants and information about the entrant*/
struct track * view_entrant_location(struct entrant * entrant);
struct track * get_track(struct entrant * entrant, int i);
struct node get_next_expected_checkpoint(struct entrant * entrant);
void view_entrant(int entrant_selected);

/* Function prototypes to print file read results*/
void print_event();
void print_nodes();
void print_tracks();
void print_courses();
void print_entrants();

