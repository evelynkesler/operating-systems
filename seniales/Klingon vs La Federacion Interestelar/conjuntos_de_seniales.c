#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void HandlerSIGUSER2(int);
void HandlerSIGUSER1(int); //Handler de la senial SIHUSR1 que deberia levantar el escudo o bloquear las seniales recibidas por los klingons.
void Conjunto_de_seniales(); //Configurar el conjunto de seniales que deberian ser bloqueadas cuando el escudo se active.
void HandlerGenerico(int); //Handler para las seniales SIGINT, SIGCOUNT, SIGXCPU, SIGQUIT son los disparos de los klingons.
void Redefine_seniales(); //Asignar los handlers a las seniales respectivas. 

sigset_t set; //Variable para manejar conjunto de seniales. 

int main(int argc, char **argv[])
{
    Redefine_seniales();
    Conjunto_de_seniales();
    sigprocmask(SIG_BLOCK, &set, NULL); 
    printf("ESCUDO PROTECTOR ACTIVADO\n");

    while(1); //Ciclo infinito. Nave en conbate.
    exit(0); //Nunca deberia ocurrir. 
}

void Conjunto_de_seniales()
{
    sigemptyset(&set);// Inicializa un cjto de seniales vacio. 

    // Agregamos las seniales al cjto.
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGCONT);
    sigaddset(&set, SIGQUIT);
    sigaddset(&set, SIGXCPU);
}

void HandlerSIGUSR2(int s)
{
    sigprocmask(SIG_UNBLOCK, &set, NULL); // La seniales solo van a quedar bloqueadas en el handle
                                        // Luego se vuelven a bloquear ya que tenemos un SIG_BLOCK en el main. 
    printf("ESCUDO PROTECTOR DESACTIVADO\n");
}

void HandlerSIGUSER1(int a)
{
    sigprocmask(SIG_BLOCK, &set, NULL); // Se activa el escudo solo cuando se esta ejecutando el handler. 
                                        // Para que siempre este activo se deberia haber bloqueado el conjunto de seniales destro del main. 
    printf("ESCUDO PROTECTOR ACTIVADO\n");
}

void HandlerGenerico(int s)
// Se ejecuta cuando el escudo esta desactivado, es decir se ejecuto sigprocmask con SIG_UNBLOCK.
{
    if(s == SIGINT) printf("Klingon disparo SIGINT realizando averias en el enterprise\n");
    if(s == SIGCONT) printf("Klingon disparo SIGCONT realizando averias en el enterprise\n");
    if(s == SIGQUIT) printf("Klingon disparo SIGQUIT realizando averias en el enterprise\n");
    if(s == SIGXCPU) printf("Klingon disparo SIGXCPU realizando averias en el enterprise\n");
}   

void Redefine_seniales()
// Asigna la ejecucion de las funciones handler cuando el enterprise recibe cada usa de las seniales. 
{
    //signal(SIGUSR1, (void *)HandlerSIGUSER1);
    signal(SIGUSR2, (void *)HandlerSIGUSR2); 
    signal(SIGINT, (void *)HandlerGenerico);
    signal(SIGCONT, (void *)HandlerGenerico);
    signal(SIGQUIT, (void *)HandlerGenerico);
    signal(SIGXCPU, (void *)HandlerGenerico); 
}

/*
Este código en C define una simulación del manejo de señales en un programa, utilizando como contexto la nave espacial Enterprise del universo Star Trek.

La función Conjunto_de_seniales se utiliza para configurar un conjunto de señales que deberían ser bloqueadas cuando se active el escudo protector de la nave. Para esto, utiliza la biblioteca de señales signal.h y la función sigemptyset para inicializar un conjunto de señales vacío, y luego utiliza la función sigaddset para agregar las señales SIGINT, SIGCONT, SIGQUIT y SIGXCPU al conjunto.

La función HandlerSIGUSER1 se ejecuta cuando se recibe la señal SIGUSR1, que simula el comando para activar el escudo protector. Dentro de esta función, se utiliza la función sigprocmask para bloquear el conjunto de señales configurado previamente mediante Conjunto_de_seniales, lo que significa que estas señales serán ignoradas mientras el escudo protector esté activo.

La función HandlerGenerico es el handler genérico que se ejecuta cuando la nave recibe alguna de las señales configuradas en Conjunto_de_seniales, siempre y cuando el escudo protector esté desactivado. Dependiendo de la señal recibida, se imprimirá un mensaje en la consola indicando que un Klingon ha realizado daños en la nave.

Finalmente, la función Redefine_seniales se encarga de asignar los handlers correspondientes a cada señal. La señal SIGUSR1 utiliza el handler HandlerSIGUSER1, mientras que las señales SIGINT, SIGCONT, SIGQUIT y SIGXCPU utilizan el handler genérico HandlerGenerico.

El programa utiliza un ciclo infinito while(1) para simular que la nave está en combate. El programa nunca debería salir de este ciclo, pero incluye una instrucción exit(0) al final por motivos de buenas prácticas.

*/