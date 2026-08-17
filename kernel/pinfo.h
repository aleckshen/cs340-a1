#ifndef _PINFO_H_
#define _PINFO_H_

#include "param.h"

// Info about every process slot, filled in by getpinfo().
// ticks[i][0] = ticks process i has spent RUNNING at priority 1
// ticks[i][1] = ticks process i has spent RUNNING at priority 2
struct pinfo {
  int inuse[NPROC];
  int pid[NPROC];
  int priority[NPROC];
  int ticks[NPROC][2];
};

#endif
