#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void KlingonGrabaPid();
void KlingonLeePid_Enterprise();
void HandlerSIGUSR1(int);
void Redefine_seniales();

char pids[10];

int main(int argc, char * argv[])
{
    KlingonGrabaPid();
    KlingonLeePid_Enterprise();
    Redefine_seniales();
    while(1);
    exit(0);
}

void Redefine_seniales()
{
    signal(SIGUSR1, (void *)HandlerSIGUSR1);
}

void KlingonGrabaPid()
{
    char pidsKli[10];
    int fd = open("KlingonPid", O_WRONLY|O_TRUNC|O_CREAT, 0777);
    snprintf(pidsKli,5,"%d",getpid());
    printf("Klingon pid %d\n", pidsKli); 
    write(fd, pidsKli, 5);
    close(fd);
}

void KlingonLeePid_Enterprise()
{
    int fd;
    while((fd = open("EnterprisePid", O_RDONLY)) == 1);
    read(fd, pids, 5);
    printf("Enterprise pid %s\n", pids);
    close(fd);
}

void HandlerSIGUSR1(int s)
{
    printf("Klingon DISPARA SIGINT SIGCONT SIGQUIT SIGXCPU al Enterprise\n");
    kill(atoi(pids),SIGINT);
    kill(atoi(pids),SIGCONT);
    kill(atoi(pids),SIGQUIT);
    kill(atoi(pids),SIGXCPU);
}

// Una senial bloqueada llega y permanece ahi a la espera de ser desbloqueada
// Una senial ignorada nunca llega. 