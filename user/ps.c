#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "kernel/pinfo.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  struct pinfo pi;
  int i;

  if (getpinfo(&pi) < 0) {
    fprintf(2, "ps: getpinfo failed\n");
    exit(1);
  }

  printf("PID   PRI  TICKS@1  TICKS@2\n");
  for (i = 0; i < NPROC; i++) {
    if (!pi.inuse[i])
      continue;
    printf("%d\t%d\t%d\t%d\n", pi.pid[i], pi.priority[i], pi.ticks[i][0], pi.ticks[i][1]);
  }

  exit(0);
}
