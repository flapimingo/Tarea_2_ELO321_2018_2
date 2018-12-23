#include "Functions.h"

int main(int argc, char const *argv[])
{
    /* Arrays to contain file descriptors for two pipes */
    int pipee[2];

    int stgoState = 0;  /* Starts reading */
    int valpoState = 1; /* Starts writing */

    if (pipe(pipee))
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
        char *msg_stgo_receive[] = {"NULL","NULL","NULL","NULL","NULL"};
        char receive_buffer[MSGSIZE];
        pid1=fork();
        if (pid1== 0)
        {
            /*1st child: Santiago */
            while(1)
            {
                if(strcmp(msg_stgo_receive[0]," ")==0){
                    break;
                }else{
                if (stgoState == 1)
                {
                    printf("\n\nstgo sended\n");
                    int seed = getpid();
                    /* send Message through the pipe */
                    writePipe(pipee, msg_stgo_send, seed);
                    stgoState = 0;
                }
                else
                {
                    printf("\n\nstgo recept\n");
                    /* Read the pipe*/
                    readPipe(pipee, receive_buffer, msg_stgo_receive);
                    stgoState = 1;
                }
                }
            }
        }
        else
        {
            /* parent */
            pid2 = fork();
            if (pid2 == 0)
            {
                /*2nd child: Valparaiso */
                while(1)
                {
                    if(strcmp(msg_valpo_send[0]," ")==0){
                        break;
                    }
                    else{
                    if (valpoState == 1)
                    {
                        int seed = getpid();
                        /* send Message */
                        printf("\n\nvalpo sended\n");
                        writePipe(pipee, msg_valpo_send, seed);
                        valpoState = 0;
                    }
                    else
                    {
                        printf("\n\nvalpo recept\n");
                        /* Read the pipe */
                        readPipe(pipee, receive_buffer, msg_valpo_receive);
                        valpoState = 1;
                    }
                    }
                }
            }
            else
            {
                /* parent */
                waitpid(pid1, &status1, 0);
                waitpid(pid2, &status2, 0);
                close(pipee[READ_END]);
                close(pipee[WRITE_END]);
            }
        }
        return 0;
    }
}