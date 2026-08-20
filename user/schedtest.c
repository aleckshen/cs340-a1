#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
burn(void)
{
  volatile int i;
  for (i = 0; i < 30000000; i++)
    ;
}

int
main(int argc, char *argv[])
{
  int pid_high, pid_low, i;

  pid_high = fork();
  if (pid_high == 0) {
    setpri(2);
    for (i = 1; i <= 5; i++) {
      burn();
      printf("high: %d\n", i);
    }
    exit(0);
  }

  pid_low = fork();
  if (pid_low == 0) {
    for (i = 1; i <= 5; i++) {
      burn();
      printf("low: %d\n", i);
    }
    exit(0);
  }

  wait(0);
  wait(0);
  exit(0);
}
