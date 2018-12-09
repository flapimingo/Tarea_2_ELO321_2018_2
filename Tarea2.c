#include "Functions.h"

int main(int argc, char const *argv[])
{
    /* Arrays to contain file descriptors for two pipes */
    int valpo_to_stgo[2];
    int stgo_to_valpo[2];

    int stgoState = 0;  /* Starts reading */
    int valpoState = 1; /* Starts writing */

    if (pipe(valpo_to_stgo) < 0 || pipe(stgo_to_valpo) < 0)
    {
        printf("cannot create pipes\n");
        exit(1); /*exits if pipe fails*/
    }
    else
    {

        pid_t pid1, pid2;
        int status1, status2;

        char *msg_valpo_send[] = {"Va", "Ve", "Vi", "Vo", "Vu"};
        char *msg_stgo_send[] = {"Sa", "Se", "Si", "So", "Su"};
        char *msg_valpo_receive[] = {"NULL","NULL","NULL","NULL","NULL"};
        char *msg_stgo_receive[MAXMSG] = {"NULL","NULL","NULL","NULL","NULL"};
        char receive_buffer[MSGSIZE];

        if ((pid1 = fork()) == 0)
        {
            /*1st child: Santiago */
            while ((msg_valpo_send[0] != " ") && (msg_stgo_send[0] != " "))
            {
                if (stgoState == 1)
                {
                    printf("\n\nstgo sended\n");
                    int seed = getpid();
                    /* send Message through the pipe */
                    writePipe(stgo_to_valpo, msg_stgo_send, seed);
                    stgoState = 0;
                }
                else
                {
                    printf("\n\nstgo recept\n");
                    /* Read the pipe*/
                    readPipe(valpo_to_stgo, receive_buffer, msg_stgo_receive);
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
                while ((msg_valpo_send[0] != " ") && (msg_stgo_send[0] != " "))
                {
                    
                    if (valpoState == 1)
                    {
                        int seed = getpid();
                        /* send Message */
                        printf("\n\nvalpo sended\n");
                        writePipe(valpo_to_stgo, msg_valpo_send, seed);
                        valpoState = 0;
                    }
                    else
                    {
                        printf("\n\nvalpo recept\n");
                        /* Read the pipe */
                        readPipe(stgo_to_valpo, receive_buffer, msg_valpo_receive);
                        valpoState = 1;
                    }
                }
            }
            else
            {
                /* parent */
                waitpid(pid1, &status1, 0);
                waitpid(pid2, &status2, 0);
                close(valpo_to_stgo[READ_END]);
                close(valpo_to_stgo[WRITE_END]);
                close(stgo_to_valpo[READ_END]);
                close(stgo_to_valpo[WRITE_END]);
            }
        }
        return 0;
    }
}