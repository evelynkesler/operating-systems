//El programa toma como parametro la cantidad de hijos que se van 
//a crear en abanico

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

void FuncionAlarma(void);

int numproces; //Cant de procesos hijos.
pid_t vecpid[100]; //Vector de pids de procesos.
int ent; //Indice del vector de pids de procesos

int main(int argc, char **argv) //Cant string que se tipearon en la linea de comando y vector de punteros a char. 
{
    pid_t pid;
    int i;
    numproces = atoi(argv[1]); //Convierto a entero el string que recibo desde la linea de comandos. 
    for (i = 0; i < numproces; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            printf("...hijo i=%d, pid=%d se detiene esperando planificacion\n", i, getpid());
            raise(SIGSTOP); //Hijo ceardo se envia a si mismo SIGSTOP
            break;
        }
        vecpid[i] = pid;
        sleep(1);
    }
    if (i == numproces) //Estoy en el padre con todos los hijos creados
    {
        signal(SIGALRM, (void *) FuncionAlarma); //El padre instala el nuevo manejador paara la senial SIGALRM.
        printf("\n------Padre i=%d, pid=%d Planificando\n\n", i, getpid());
        ent = 0;
        while(1)
        {
            printf("Padre reanuda al hijo %d, pid=%d", ent, vecpid[ent]);
            kill(vecpid[ent], SIGCONT); //El padre le da continuacion de ejecucion al hijo vecpid[ent]
            alarm(5); 
            printf("---> Padre pausado\n");
            pause(); //El padre se pausa esperando recibir una senial (en este caso vamos a mandarle SIGALRM)
            ent = (ent+1) % numproces; //ent queda apuntando al proximo proceso.
        }
    }
    else 
    {
        while(1)
        {
            printf("....hijo=%d, pid=%d ejecutando, valor de i=%d\n", i, getpid(), i);
            int i;
            for(i=1; i<6; i++) {printf("%d\n", getpid()); sleep(1);}
        }
    }
    exit(0);
}

void FuncionAlarma(void)
{
    printf("Padre detiene al hijo=%d, pid=%d\n\n", ent, vecpid[ent]);
    kill(vecpid[ent], SIGSTOP); //El padre detiene al hijo vecpid[ent]
}