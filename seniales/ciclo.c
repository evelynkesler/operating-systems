#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    while(1)
    {
        printf("Aqui estoy mi pid es %d\n", getpid());
        sleep(1);
    }
    exit(0);
}