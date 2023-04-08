#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	char comando[100];
	printf("Ingrese Comando:");
	fgets(comando,100,stdin);
	comando[strlen(comando)-1] = '\0';
	pid_t pid = fork();
	if ( pid == 0 ) {
		// este es un proceso hijo!
		int ret = execl(comando,comando,NULL);
		printf("Si veo esto, significa que execl() fallo y ret = %d\n",ret);
	} else if ( pid > 0 ) {
		// estoy en el proceso padre!
		int estado=0;
		pid_t pid = wait(&estado); // espero la finalizacion del primer hijo que cree
		printf("Finalizo proceso %d y retorno %d\n",pid,estado/256);
	} else {
		// error!!
		printf("Error en fork!\n");
	}
	return 0;
}