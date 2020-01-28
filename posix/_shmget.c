#include <lib.h>
#define shmget _shmget
#include <signal.h>

PUBLIC int shmget(size)
int size;
{
  message m;

  m.m1_i1 = size;
  return(_syscall(MM, SHMGET, &m));
}
