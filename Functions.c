#include "Functions.h"

void writeToFile(char *list[])
{
    /*
    FILE *fp;

    fp = fopen("comm_log_file.txt", "r+");

    if(fp == NULL)
    {
        printf("File doesn't exists.\n");
    }
    

    printf();

    Closes file to save file data
    fclose(fp); 
    */
}

void readPipe(int input_pipe[], char buffer[MSGSIZE], char *receive[])
{
    printf("ah copiao\n");
    //close(input_pipe[WRITE_END]); /*close write end, it's not needed*/
    read(input_pipe[READ_END], buffer, MSGSIZE);
    if (strcmp(buffer, "FINISH") == 0)
    {
        exit(1);
    }
    else
    {
        if (strcmp(buffer, " ") != 0)
        {
            addReceived(buffer, receive);
            printf("message received: %s\n", buffer);
        }
    }
}

void writePipe(int input_pipe[], char *msg_to_send[], int seed)
{
    srand(seed);
    if (strcmp(msg_to_send[0], " ") == 0)
    {
        write(input_pipe[WRITE_END], "FINISH", MSGSIZE);
        abort();
    }
    else
    {
        if ((1 + rand() % 10) < 8)
        {
            if (strcmp(msg_to_send[0], " ") != 0)
            {
                //close(input_pipe[READ_END]); /*close write end, it's not needed*/
                write(input_pipe[WRITE_END], msg_to_send[0], MSGSIZE);
                printf("message sended: %s\n", msg_to_send[0]);
                removeSended(msg_to_send);
            }
            else
            {
                write(input_pipe[WRITE_END], "FINISH", MSGSIZE);
            }
        }
        else
        {
            printf("No message was sended\n");
            write(input_pipe[WRITE_END], " ", MSGSIZE);
        }
    }
}

char **addReceived(char *input, char *list[])
{
    int i;
    for (i = 0; i < sizeof(list) - 1; i++)
    {
        if ((strcmp(list[i], "NULL")) == 0)
        {
            list[i] = input;
            break;
        }
    }

    return (list);
}

char **removeSended(char *list[])
{
    int i;
    for (i = 0; i < sizeof(list) - 1; i++)
    {
        list[i] = list[i + 1];
        if (i >= 4)
            list[i] = " ";
    }

    return (list);
}

int *receivedStatus(char *list[])
{
    int i;
    int *size = 0;
    for (i = 0; i <= sizeof(list); i++)
    {
        if ((strcmp(list[i], "NULL")) == 0)
        {
            size+=1;
        }
    }

    return size;
}

int sendedStatus(char *list[])
{
    int i;
    int size = 0;
    for (i = 0; i < sizeof(list) - 1; i++)
    {
        if ((strcmp(list[i], " ")) == 0)
            size++;
    }

    return size;
}
