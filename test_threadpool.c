#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "threadpool.h"

void *work_routine(void *arg) {
  int arg_v = *(int *) arg;
  printf("Working on %d\n", arg_v);
  sleep(4);
  printf("Work done (%d).\n", arg_v);
  return NULL;
}

int main() {
  printf("Testing threadpool of %d threads.\n", pool_get_max_threads());

  struct thread_pool pool;

  init_thread_pool(&pool);

  for (int i = 1; i <= 8; i++) {
    int *arg = malloc(sizeof(int));
    *arg = i;
    queue_work_item(&pool, work_routine, (void *)arg);
  }


  sleep(20);

  destroy_thread_pool(&pool);

  printf("Done.");
}
