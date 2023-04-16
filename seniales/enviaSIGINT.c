// man 2 kill

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main (int argc, char * argv[])
{
    int res;
    kill(atoi(argv[1]), SIGINT); //kill dentro de una funcion recibe el pid del proceso que va a recibir la senial y la senial 
    if (errno == ESRCH) //si kill retorna un error. El proceso al cual fue enviada la senial no existe. 
        printf("Proceso receptor senial no existee\n");
    exit(0);
}