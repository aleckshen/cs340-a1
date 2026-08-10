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