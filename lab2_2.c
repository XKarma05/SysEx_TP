

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define KEY1 4567
#define KEY2 4568
#define KEY3 4569
#define KEY4 4570
#define PERMS 0660

int main(int argc, char **argv) {
      int id1, id2, id3, id4;
      int a, b;
      int *c, *d;
      int *e, *f;

      id1 = shmget(KEY1, sizeof(int), IPC_CREAT | PERMS);
      id2 = shmget(KEY2, sizeof(int), IPC_CREAT | PERMS);
      id3 = shmget(KEY3, sizeof(int), IPC_CREAT | PERMS);
      id4 = shmget(KEY4, sizeof(int), IPC_CREAT | PERMS);

      c = (int *) shmat(id1, NULL, 0);
      d = (int *) shmat(id2, NULL, 0);
      e = (int *) shmat(id3, NULL, 0);
      f = (int *) shmat(id4, NULL, 0);

      if (fork() == 0) {

          *c = 7;
          *d = 9;

 	  if(fork() == 0) {
	  *e = -3;
	   *f = 4;
	  }
      } 
      else {
          wait(NULL);
          a = 3, b = 5;
          
          printf("((%d+%d)*(%d-%d)+(%d+%d)) = %d\n", a, b, *c, *d, *e, *f, (a+b)*(*c-*d)+(*e+*f));
          shmctl(id1, IPC_RMID, NULL);
          shmctl(id2, IPC_RMID, NULL);
      }
}

