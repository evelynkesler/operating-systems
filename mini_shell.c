/* Ejemplo de un minishell que permite ejecutar comandos en foreground sin argumentos.*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

int main (void)
{
    pid_t pid;
    char comando[64];
    printf("MI PROMPT ");
    memset(comando, '\0', 64);
    scanf("%s", comando);
    while(strcmp(comando,"exit")) // Devuleve 1 si es distinto. Queda dentro del ciclo while. 
    {
        pid = fork();
        if(pid == 0) 
        {
            execlp(comando, comando, NULL); // El hijo se convierte en el comando que se ingreso por consola. 
            printf("comando no valido\n");
            exit(0); // Si el hijo no logra ejecutar con exito el exit termina. No quedan hijos huerfanos. 
        }
        else
            if(pid > 0)
            {
                waitpid(pid,0,0); // Espero que termine la ejecucion de mis hijos. No quedan hijos huerfanos. 
                                // Puedo usar wait(int *) por que de todas formas vamos a realizar un bloqueo en el proceso padre.
                printf("MI PROMPT ");
                memset(comando, '\0', 64);
                scanf("%s", comando);
            }
        else
            perror("ERROR FORK\n");
    }
    exit(0); 
}