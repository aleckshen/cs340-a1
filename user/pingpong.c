#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int p2c0[2]; // parent -> child 0
  int p2c1[2]; // parent -> child 1
  int c2p0[2]; // child 0 -> parent
  int c2p1[2]; // child 1 -> parent

  pipe(p2c0);
  pipe(p2c1);
  pipe(c2p0);
  pipe(c2p1);

  char buf[16]; // small buffer for reading messages into

  // fork child 0
  int pid0 = fork();
  if (pid0 == 0)
  {
    // close pipe ends this child doesn't use
    close(p2c0[1]);
    close(c2p0[0]);
    close(p2c1[0]);
    close(p2c1[1]);
    close(c2p1[0]);
    close(c2p1[1]);

    read(p2c0[0], buf, 4); // read "ping" from parent
    printf("%d: pong\n", getpid());
    write(c2p0[1], "ACK", 3); // send ACK back to parent

    exit(0); // child 0 is done
  }

  // fork child 1
  int pid1 = fork();
  if (pid1 == 0)
  {
    close(p2c1[1]);
    close(c2p1[0]);
    close(p2c0[0]);
    close(p2c0[1]);
    close(c2p0[0]);
    close(c2p0[1]);

    read(p2c1[0], buf, 4); // read "ping" from parent
    printf("%d: pong\n", getpid());
    write(c2p1[1], "ACK", 3); // send ACK back to parent

    exit(0); // child 1 is done
  }

  // close ends the parent doesn't use
  close(p2c0[0]);
  close(p2c1[0]);
  close(c2p0[1]);
  close(c2p1[1]);

  // send "ping" to both children
  write(p2c0[1], "ping", 4);
  write(p2c1[1], "ping", 4);

  // wait for both ACKs
  read(c2p0[0], buf, 3);
  read(c2p1[0], buf, 3);

  // make sure both children have fully exited
  wait(0);
  wait(0);

  exit(0);
}
