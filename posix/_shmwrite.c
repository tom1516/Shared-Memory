#include <lib.h>
#define shmwrite _shmwrite
#include <signal.h>

PUBLIC int shmwrite(shmid, private_buffer, shm_offset, length)
int shmid;
char *private_buffer;
int shm_offset;
int length;
{
  message m;

  m.m1_i1 = shmid;
  m.m1_i2 = shm_offset;
  m.m1_i3 = length;
  m.m1_p1 = private_buffer;

  return(_syscall(MM, SHMWRITE, &m));
}
