/* 
 * File:   course.c
 * Author: ljs5
 *
 * Created on 28 November 2012, 17:26
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

int num_of_courses;
/**
 * Read in the courses file entered by the user
 * @param file_name
 * @param nodes
 * @return the list of courses;
 */

struct course * get_courses_file(char * file_name, struct node * nodes) {
    //list of the courses attribute
    struct course * course_list;
    
    FILE * courses_file;
    char * mode = "r";

    //number of courses in the file
    num_of_courses = line_num(file_name);

    //create memory for the number of courses in the file
    course_list = (struct course*) malloc(num_of_courses * sizeof (struct course));
    
    //open the file
    courses_file = fopen(file_name, mode);

    int i;
    //loop over the file 
    for (i = 0; i < num_of_courses; i++) {
        struct course new_course;

        char course_name;
        int num_nodes_in_course;
        int node_count = 0;
        struct node * course_nodes;
        if (courses_file != NULL) {
            fscanf(courses_file, "%c %d", &course_name, &num_nodes_in_course);
            new_course.course_name = course_name;
            new_course.num_of_courses = num_of_courses;
            new_course.num_nodes_in_course = num_nodes_in_course;
            //create the memory for to store all the nodes in the course
            course_nodes = (struct node *) malloc(num_nodes_in_course * sizeof (struct node));
            //loop through the line getting the nodes
            for (node_count = 0; node_count < num_nodes_in_course; node_count++) {
                int current_node;
                fscanf(courses_file, "%d", &current_node);
                //get node from nodes list
                course_nodes[node_count] = nodes[current_node - 1];
            }
            //set the nodes list in the course
            new_course.nodes_list = course_nodes;
        }
        fscanf(courses_file, "\n");
        //assign the course in the course list
        course_list[i] = new_course;
    }
    fclose(courses_file);
    return course_list;
}

