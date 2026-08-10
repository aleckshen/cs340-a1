#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void spawn(int remaining)
{
    if (remaining == 0)
    {
        printf("my ID is %d, my parent ID is %d\n", getpid(), getppid());
        exit(0);
    }

    int pid = fork();
    if (pid == 0)
    {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winfinite-recursion"
        spawn(remaining - 1); // child keeps extending the chain
#pragma GCC diagnostic pop
    }
    else
    {
        wait(0); // wait for child (and everything below it) to finish
        printf("my ID is %d, my parent ID is %d\n", getpid(), getppid());
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(2, "usage: findppid num\n");
        exit(1);
    }

    int num = atoi(argv[1]);
    spawn(num);
    exit(0);
}