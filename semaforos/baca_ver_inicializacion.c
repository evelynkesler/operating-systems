#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int semid = semget(0xa, 0, 0);//Recupera el ID del semaforo cuya clave de usuario es 0xa.  
 
    if (semid != -1) 
    { //vemos la inicializacion 
        printf("Sa = %d\n", semctl(semid, 0, GETVAL));
        printf("Sb = %d\n", semctl(semid, 1, GETVAL));
        printf("Sc = %d\n", semctl(semid, 2, GETVAL));
        printf("Sx = %d\n", semctl(semid, 3, GETVAL));
    }
    else
        printf("Error de semget\n");
    return 0;
}