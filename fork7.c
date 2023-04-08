#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t padre = getpid();
	fork();
	fork();
	printf("Soy proceso %d , hijo del proceso %d\n",getpid(),getppid());
	pid_t pid1 = wait(0);
	pid_t pid2 = wait(0);
	printf("Soy proceso %d, pid1 = %d , pid2 = %d\n",getpid(),pid1,pid2);
	if ( getpid() == padre ) system("ps -lax");
	printf("Soy proceso %d, a punto de finalizar retornando 0\n",getpid());
	return 0;
}