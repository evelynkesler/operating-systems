#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void EnterpriseGrabaPid(void);
void EnterpriseLeePid_Klingon(void); // No seria necasaria porque el proceso enterprise no le va a enviar seniales al proceso Klingon
void HandlerSIGUSR1(int);
void HandlerSIGUSR2(int);
void HandlerSIGALRM(int);
void HandlerGenerico(int);
void Conjunto_de_seniales();
void Redefine_seniales(); 

char pids[10];
sigset_t set;

int main(int argc, char * argv[])
{
    EnterpriseGrabaPid();
    EnterpriseLeePid_Klingon();
    Conjunto_de_seniales();
    Redefine_seniales();

    while(1)
    {
        if (sigismember(&set, SIGUSR1)) // Preguntamos si llego esta senial
        {
            sigdelset(&set, SIGUSR1); // La quitamos del conjunto
            sigprocmask(SIG_BLOCK, &set, NULL); // Levantamos el escudo
            printf("Enterprise Escudo Activado\n");
        }

        if (sigismember(&set, SIGUSR2))
        {
            sigdelset(&set, SIGUSR2);
            printf("Enterprise Escudo Desactivado\n");
            sigprocmask(SIG_UNBLOCK, &set, NULL);

        }
    }
    exit(0);
}

void EnterpriseGrabaPid(void)
{
    char pidsEnt[10];
    int fd = open("EnterprisePid", O_WRONLY|O_TRUNC|O_CREAT, 0777);
    snprintf(pidsEnt, 6, "%d", getpid());
    printf("Enterprise pid %s\n", pidsEnt);
    write(fd, pidsEnt, 6);
    close(fd);
}

void EnterpriseLeePid_Klingon(void)
{
    int fd;
    while ((fd = open("KLingonPid", O_WRONLY)) == -1);
    read(fd,pids,6);
    printf("Klingon pid %s\n", pids);
    close(fd);
}

void HandlerSIGUSR1(int s)
{
    sigaddset(&set, SIGUSR1);
}

void HandlerSIGUSR2(int)
{
    sigaddset(&set, SIGUSR2); 
}

void HandlerSIGALRM(int)
{
    sigset_t senialesPendientes;
    printf("Enterprise INFORMA disparon recibidos de los klingon que pagaron emmn el escudo...\n");
    sigpending(&senialesPendientes); //Seniales que llegaron al proceso cuando las seniales estaban bloqueadas.
    
    if(sigismember(&senialesPendientes, SIGINT))
    {
        printf("Klingon disparo SIGINT PEGO EN EL ESCUDO\n");
        signal(SIGINT, SIG_IGN); // Ignoramos la senial por lo que no llega al proceso. 
    }

    if(sigismember(&senialesPendientes, SIGCONT))
    {
        printf("Klingon disparo SIGINT PEGO EN EL ESCUDO\n");
        signal(SIGCONT, SIG_IGN); 
    }

    if(sigismember(&senialesPendientes, SIGQUIT))
    {
        printf("Klingon disparo SIGINT PEGO EN EL ESCUDO\n");
        signal(SIGQUIT, SIG_IGN); 
    }

    if(sigismember(&senialesPendientes, SIGXCPU))
    {
        printf("Klingon disparo SIGINT PEGO EN EL ESCUDO\n");
        signal(SIGXCPU, SIG_IGN); 
    }

    signal(SIGINT,(void *)HandlerGenerico); 
    signal(SIGCONT,(void *)HandlerGenerico);
    signal(SIGQUIT,(void *)HandlerGenerico);
    signal(SIGXCPU,(void *)HandlerGenerico);
}

void HandlerGenerico(int s)
{
    if (s == SIGINT) printf("Klingon disparo SIGINT REALIZO AVERIAS EN ENTERPRISE\n");if (s == SIGINT) printf("Klingon disparo SIGINT REALIZO AVERIAS EN ENTERPRISE\n");
    if (s == SIGCONT) printf("Klingon disparo SIGCONT REALIZO AVERIAS EN ENTERPRISE\n");if (s == SIGINT) printf("Klingon disparo SIGINT REALIZO AVERIAS EN ENTERPRISE\n");
    if (s == SIGQUIT) printf("Klingon disparo SIGQUIT REALIZO AVERIAS EN ENTERPRISE\n");if (s == SIGINT) printf("Klingon disparo SIGINT REALIZO AVERIAS EN ENTERPRISE\n");
    if (s == SIGXCPU) printf("Klingon disparo SIGXCPU REALIZO AVERIAS EN ENTERPRISE\n");if (s == SIGINT) printf("Klingon disparo SIGINT REALIZO AVERIAS EN ENTERPRISE\n");

}

void Conjunto_de_seniales()
{
    sigemptyset(&set);

    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGCONT);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGXCPU);
}

void Redefine_seniales()
{
    signal(SIGUSR1, (void *)HandlerSIGUSR1);
    signal(SIGUSR2, (void *)HandlerSIGUSR2);
    signal(SIGALRM, (void *)HandlerSIGALRM);

    signal(SIGINT, (void *)HandlerGenerico);
    signal(SIGCONT, (void *)HandlerGenerico);
    signal(SIGQUIT, (void *)HandlerGenerico);
    signal(SIGXCPU, (void *)HandlerGenerico);
} 