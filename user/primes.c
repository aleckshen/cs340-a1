#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void sieve(int rfd)
{
    int prime;
    int n = read(rfd, &prime, sizeof(int));
    if (n == 0)
    {
        // no more numbers, nothing to do
        close(rfd);
        exit(0);
    }

    printf("%d\n", prime);

    int p[2];
    pipe(p);

    int pid = fork();
    if (pid == 0)
    {
        // CHILD: will handle the NEXT prime in the pipeline
        close(p[1]); // child only reads
        close(rfd);  // done with the old input, not needed anymore
        sieve(p[0]); // recurse
    }
    else
    {
        // PARENT: filters numbers and forwards survivors to the child
        close(p[0]); // parent only writes
        int num;
        while (read(rfd, &num, sizeof(int)) > 0)
        {
            if (num % prime != 0)
            {
                write(p[1], &num, sizeof(int));
            }
        }
        close(rfd);
        close(p[1]); // signals EOF to the child
        wait(0);     // wait for the whole rest of the pipeline to finish
        exit(0);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("usage: primes num\n");
        exit(1);
    }
    int limit = atoi(argv[1]);

    int p[2];
    pipe(p);

    int pid = fork();
    if (pid == 0)
    {
        close(p[1]);
        sieve(p[0]);
    }
    else
    {
        close(p[0]);
        for (int i = 2; i <= limit; i++)
        {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);
    }

    exit(0);
}