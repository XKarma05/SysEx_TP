#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define KEY1 4567
#define KEY2 4568
#define PERMS 0660

int main(int argc, char **argv) {
      int id1, id2;
      int a, b;
      int *c, *d;

      id1 = shmget(KEY1, sizeof(int), IPC_CREAT | PERMS);
      id2 = shmget(KEY2, sizeof(int), IPC_CREAT | PERMS);

      c = (int *) shmat(id1, NULL, 0);
      d = (int *) shmat(id2, NULL, 0);

      if (fork() == 0) {

          *c = 7;
          *d = 9;

          exit(0);
      } 
      else {
          wait(NULL);
          a = 3, b = 5;
          
          printf("((%d+%d)-(%d+%d)) = %d\n", a, b, *c, *d, (a+b)-(*c+*d));
          shmctl(id1, IPC_RMID, NULL);
          shmctl(id2, IPC_RMID, NULL);
      }
}

