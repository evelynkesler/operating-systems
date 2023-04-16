#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void nuevoManejador(int);
void nuevoManejadorParaSIGALRM(int);

int main(void)
{
    //Instala los manejadores para las seniales.
    signal(SIGINT, (void *)nuevoManejador); //Senial que quiero ignorar y constante figurativa. 
                            // No puedo terminar el proceso con ctrl + c porque la senial que se envia en SIGINT. 
    signal(SIGALRM, (void *)nuevoManejadorParaSIGALRM); 
    alarm(10); //Cada 10 segundos envio la senial SIGALRM. 

    while(1)
    {
        printf("Aqui estoy mi pid es %d\n", getpid());
        sleep(1);
    }
    exit(0);
}

void nuevoManejador(int s)
{
    printf("------- Recibi la senial --> %d\n", s);
}

void nuevoManejadorParaSIGALRM(int s)
{
    printf("******** Recibi la senial --> %d **\n", s);
    signal(SIGINT, SIG_DFL); //Llamada al sistema que deja sin efecto al nuevo manejador asociado a la recepcion de la senial 
                            // SIGINT y vuelve al comportamiento por defecto (la proxima vez que reciba SIGINT en proceso va a terminar). 
    //alarm(10); //Si quiero que se vuelva a ejecutar el manejador de la senial. 
}