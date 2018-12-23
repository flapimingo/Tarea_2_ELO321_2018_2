#include "Functions.h"

void writeToFile(FILE archivo, char* text)
{

    char *wea = "testeanding";
    fprintf(&archivo, "%s\n", text);
}

void readPipe(int input_pipe[], char buffer[MSGSIZE], char *receive[], FILE archivo)
{
    read(input_pipe[READ_END], buffer, MSGSIZE);
    if (strcmp(buffer, " ") != 0)
    {
        addReceived(buffer, receive);
        printf("message received: %s\n", buffer);
        writeToFile(archivo, buffer);
    }
    if (strcmp(buffer, "FINISH") == 0)
    {
        abort();
    }
}

void writePipe(int input_pipe[], char *msg_to_send[], int seed, FILE archivo)
{
    srand(seed);
    if ((1 + rand() % 10) < 8)
    {
        if (strcmp(msg_to_send[0], " ") != 0)
        {
            write(input_pipe[WRITE_END], msg_to_send[0], MSGSIZE);
            printf("message sended: %s\n", msg_to_send[0]);
            removeSended(msg_to_send);
        }
        else
        {
            write(input_pipe[WRITE_END], "FINISH", MSGSIZE);
            abort();
        }
    }
    else
    {
        printf("No message was sended\n");
        write(input_pipe[WRITE_END], " ", MSGSIZE);
    }
    if (strcmp(msg_to_send[0], " ") == 0)
    {
        write(input_pipe[WRITE_END], "FINISH", MSGSIZE);
        abort();
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
