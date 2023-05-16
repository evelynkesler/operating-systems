// man semop
// Semaforo con nombre: Procesos Independientes.

#include <stdio.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <unistd.h>

void P(int, int); // wait(Sem)
void V(int, int); // signal(Sem)

int main(int argc, char **argv)
{
    int semid = semget(0xa, 0, 0); //Recuperacion del semid
    while(1)
    {
        //Seccion de entrada
        P(semid, 0); //wait(Sa)

        //Seccion critica 
        printf("SC Pa\n"); 
        sleep(1);

        //Seccion de salida 
        V(semid,3); //signal(Sx)
    }

    return 0;
}

void P(int semid, int nsem)
{
    struct sembuf buf;
    buf.sem_num = nsem;
    buf.sem_op = -1; //Le resta uno al semaforo
    buf.sem_flg = 0;
    semop(semid,&buf,1); //El SO ejecuta el wait/
}

void V(int semid, int nsem)
{
    struct sembuf buf;
    buf.sem_num = nsem;
    buf.sem_op = 1; //Le suma uno al semaforo
    buf.sem_flg = 0;
    semop(semid,&buf,1); //El SO ejecuta el wait/
}