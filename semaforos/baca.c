#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int semid = semget(0xa, 4, IPC_CREAT|IPC_EXCL|0660); //CREA SEMAFOROS. 0xa hexa que identifica al array de sem a nivel de programador. 
 
    if (semid != -1) 
    { // Se pudieron crear los semaforos. INICIALIZA SEMAFOROS. 
        semctl(semid, 0, SETVAL, 0);  // Sa = 0
        semctl(semid, 1, SETVAL, 1);  // Sb = 1  
        semctl(semid, 2, SETVAL, 0);  // Sc = 0
        semctl(semid, 3, SETVAL, 1);  // Sx = 1
    }
    else
        printf("Error de creacion de recursos\n");
    return 0;
}