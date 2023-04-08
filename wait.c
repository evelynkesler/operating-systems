#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h> 
#include <unistd.h>

int main(void)
{
    printf("int %zu bytes\n", sizeof(int)); // Cant de bytes que va a utilizar el SO para un entero corto. 
    pid_t pidhijo, pidtermi __attribute__((unused));
    int status;
    pidhijo = fork();
    if (pidhijo > 0)
    {
        pidtermi = wait(&status);
        printf("WEXITSTATUS = %d\n", WEXITSTATUS(status)); // Macro para ver el contenido de status.
        printf("status/256 = %d\n", status/256);
        printf("status >> 8 = %d \n", status >> 8); // Corrimiento hacia la derecha de 8 bits. 
        printf("-----------------------------------\n");
        printf("status en decimal %d \n", status);
        printf("status en hexa %x \n", status);
        printf("-----------------------------------\n");
    }
    else
    {
        // prueba 1
        // raise(SIGINT);

        // prueba 2
        // alarm(4);
        // sleep(6);

        // prueba 3 // El proceso recibe una senial por violacion de segmento.
        // int * p = (int *)0xfffff; // Le asigno a un puntero a direccion de memoria una muy alta para asegurarme de que este fuera de las direcciones del proceso. 
        // *p = 1;

        exit(7); 
    }
    exit(0);
}