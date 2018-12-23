#include "Functions.h"

int main(int argc, char const *argv[])
{
    /* Array to contain file descriptors for the pipe */
    int msg_pipe[2];

    int stgoState = 0;  /* Starts reading */
    int valpoState = 1; /* Starts writing */

    /*file ointer to write status of the process*/
    FILE *fp;
    fp = fopen("comm_log_file.txt", "w+");

    /*Checks if file has opened correctly*/
    if (fp == NULL)
    {
        printf("File doesn't exists.\n");
        exit(1);
    }

    if (pipe(msg_pipe) < 0)
    {
        printf("cannot create pipe\n");
        exit(1); /*exits if pipe fails*/
    }
    else
    {

        pid_t pid1, pid2;
        int status1, status2;

        char *msg_valpo_send[] = {"Va", "Ve", "Vi", "Vo", "Vu"};
        char *msg_stgo_send[] = {"Sa", "Se", "Si", "So", "Su"};
        char *msg_valpo_receive[] = {"NULL", "NULL", "NULL", "NULL", "NULL"};
        char *msg_stgo_receive[MAXMSG] = {"NULL", "NULL", "NULL", "NULL", "NULL"};
        char receive_buffer[MSGSIZE];

        if ((pid1 = fork()) == 0)
        {
            /*1st child: Santiago */
            while (strcmp(msg_stgo_send[0], " ") != 0)
            {
                if (stgoState == 1)
                {
                    printf("stgo sended: %s\n", msg_stgo_send[0]);
                    int seed = getpid();
                    /* send Message through the pipe */
                    writePipe(msg_pipe, msg_stgo_send, seed, *fp);
                    stgoState = 0;
                }
                else
                {
                    printf("stgo recept\n");
                    /* Read the pipe*/
                    readPipe(msg_pipe, receive_buffer, msg_stgo_receive, *fp);
                    stgoState = 1;
                }
            }
        }
        else
        {
            /* parent */
            if ((pid2 = fork()) == 0)
            {
                /*2nd child: Valparaiso */
                while (strcmp(msg_valpo_send[0], " ") != 0)
                {

                    if (valpoState == 1)
                    {
                        int seed = getpid();
                        /* send Message */
                        printf("\n\nvalpo sended\n");
                        writePipe(msg_pipe, msg_valpo_send, seed);
                        valpoState = 0;
                    }
                    else
                    {
                        printf("\n\nvalpo recept\n");
                        /* Read the pipe */
                        readPipe(msg_pipe, receive_buffer, msg_valpo_receive);
                        valpoState = 1;
                    }
                }
            }
            else
            {
                /* parent */
                waitpid(pid1, &status1, 0);
                waitpid(pid2, &status2, 0);
                close(msg_pipe[READ_END]);
                close(msg_pipe[WRITE_END]);

                /*Closes file to save file data*/
                fclose(fp);
            }
        }
        return 0;
    }
}