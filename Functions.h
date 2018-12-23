#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <linux/kernel.h>
#include <sys/types.h>

#define MSGSIZE 16
#define MAXMSG 5
#define READ_END 0
#define WRITE_END 1

/*Function that will register the progress of the process parameters*/
void writeToFile(FILE archivo, char* text);

void readPipe(int input_pipe[], char buffer[MSGSIZE], char* receive[]);

void writePipe(int input_pipe[], char* msg_to_send[], int seed);

char **addReceived(char *input, char *list[]);

char **removeSended(char *list[]);

#endif