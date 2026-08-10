#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void chain(int n)
{
    if (n == 0)
    {
        printf("my ID is %d, my parent ID is %d\n", getpid(), getppid());
        exit(0);
    }

    int pid = fork();
    if (pid == 0)
    {
        chain(n - 1);
    }
    else
    {
        wait(0);
        printf("my ID is %d, my parent ID is %d\n", getpid(), getppid());
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("usage: findppid [num]\n");
        exit(1);
    }

    int num = atoi(argv[1]);
    chain(num);

    exit(0);
}