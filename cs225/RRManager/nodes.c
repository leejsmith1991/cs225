/* 
 * File:   nodes.c
 * Author: ljs5
 *
 * Created on 28 November 2012, 17:26
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"

int num_of_nodes;
/**
 * Read in the Nodes for the event from the nodes file
 * @param file_name
 * @return the nodes list
 */
struct node * get_node_file(char * file_name) {
    struct node * nodes;
    FILE * node_file;
    char * mode = "r";

    num_of_nodes = line_num(file_name);
    node_file = fopen(file_name, mode);
    if (node_file != NULL) {
        //assign memory for the number of nodes
        
        nodes = (struct node*) malloc(num_of_nodes * sizeof (struct node));
        int i;
        for (i = 0; i < num_of_nodes; i++) {
            int node_num = 0;
            char check_type[3];

            fscanf(node_file, "%d %[A-Z]\n", &node_num, check_type);
            nodes[i].node_number = node_num;
            //use enum to avoid errors when checking on this attribute
            if (strcmp(check_type, "CP") == 0){
                nodes[i].type = CP;
            } else if(strcmp(check_type, "JN")==0){
                nodes[i].type = JN;
            } else if (strcmp(check_type, "MC")==0){
                nodes[i].type = MC;
            }
        }
    } else {
        printf("File %s does not exist", file_name);
        exit(0);
    }
    fclose(node_file);
    return nodes;
}
