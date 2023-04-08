#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

// Depende de como la CPU planifica los procesos. 

int main(int argc, char *argv[]) // argv[0]: nombre del ejecutable. argv[1]: cant de hijos - 1. 
{
    int i;
    pid_t pid;
    (void)argc; //Agregamos (void)argc para indicar que la variable no se utiliza explícitamente
    for (i=0; i <= atoi(argv[1]); i++)
    {
        pid = fork();
        if (pid == 0) 
            break;
    }
    printf("pid de mi padre:[%d] - mi pid:[%d] - mi valor de i:[%d]\n", getppid(), getpid(), i); 
    exit(0);
    return 0; 
}