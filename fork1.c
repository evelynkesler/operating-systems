#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid, finished_son;
    pid = fork();
    int status; 
    
    if (pid == 0)
        {
        printf("I am: %d, my father is: %d\n", getpid(), getppid()); 
        sleep(2); 
        printf("I have finished!\n\n");
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