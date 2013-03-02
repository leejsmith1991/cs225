/* 
 * File:   tracks.c
 * Author: ljs5
 *
 * Created on 28 November 2012, 17:26
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"


int num_of_tracks;

/*
 * Read in the file containing data for the track
 */
struct track * get_tracks_file(char * file_name, struct node * nodes) {
    struct track * tracks;
    FILE * tracks_file;
    char * mode = "r";

    num_of_tracks = line_num(file_name);
    tracks_file = fopen(file_name, mode);
    int i;

    int track_num;
    int start_node;
    int end_node;
    int estimated_time;
    
    if (tracks_file != NULL) {
        //create memory for the track list
        tracks = (struct track*) malloc(num_of_tracks * sizeof (struct track));
        for (i = 0; i < num_of_tracks; i++) {
            fscanf(tracks_file, "%d %d %d %d\n", &track_num, &start_node, &end_node, &estimated_time);
            tracks[i].track_number = track_num;
            //link in the nodes for the track
            tracks[i].start_node = nodes[start_node - 1];
            tracks[i].end_node = nodes[end_node - 1];
            tracks[i].estimated_time = estimated_time;
        }
    } else {
        printf("File %s does not exist", file_name);
        exit(0);
    }
    fclose(tracks_file);
    return tracks;
}
