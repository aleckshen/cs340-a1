#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  printf("setpri(5) -> %d\n", setpri(5));
  printf("setpri(1) -> %d\n", setpri(1));
  printf("getpinfo(0) -> %d\n", getpinfo(0));
  exit(0);
}
