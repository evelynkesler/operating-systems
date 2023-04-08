#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char * argv[])
{
    pid_t pid, finished_son;
    pid = fork();
    int status; 
    (void)argc; // agregamos (void)argc para indicar que la variable no se utiliza explícitamente

    
    if (pid == 0)
        {
        printf("I am: %d, my father is: %d\n", getpid(), getppid()); 
        //printf("I became a hello_world program\n");
        //execl("./hello_world", "./hello_world", 0); // Son is not more a clon on his father.
        execl(argv[1], argv[1], 0); // Son becomes the program entered in command line.
        exit(22);
        }
    else
        if (pid > 0)
        {
            printf("I am: %d, my son is: %d. My father (shell) is: %d\n", getpid(), pid, getppid());
            printf("I am waiting for my son...\n\n");
            finished_son = wait(&status);
            printf("My son %d has ended sending me the number %d\n", finished_son, status/256);
        }
        else  
            printf("fork failed\n");
    exit(6);
}