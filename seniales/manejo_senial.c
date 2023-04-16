#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void nuevoManejador(int);

int main(void)
{
    signal(SIGINT, (void *)nuevoManejador); //Senial que quiero ignorar y constante figurativa. 
                            // No puedo terminar el proceso con ctrl + c porque la senial que se envia en SIGINT. 
    while(1)
    {
        printf("Aqui estoy mi pid es %d\n", getpid());
        sleep(1);
    }
    exit(0);
}

void nuevoManejador(int s)
{
    printf("****** Recibi la senial --> %d\n", s);
}