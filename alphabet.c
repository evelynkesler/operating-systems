#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    pid_t pid;
    int fd = open("my_alphabet", O_CREAT|O_WRONLY|O_TRUNC,0600);
    char letter = 'a';
    pid = fork();
    if (pid > 0) //Father
    {
        while (letter <= 'z')
        {
            write(fd, &letter, 1);
            letter+=2;
        }
    }
    else
    if (pid == 0) //Son
    {
        letter = 'B';
        while (letter <= 'Z')
        {
            write(fd, &letter, 1);
            letter+=2;
        }
    }
    else
        perror("Fork() error\n");
    close(fd);
    return 0;
}