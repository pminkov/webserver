#ifndef __THREADPOOL_H_
#define __THREADPOOL_H_

#include <pthread.h>

struct task_data {
  void *(*work_routine)(void *);
  void *arg;
};

struct thread_pool {
  struct task_data* buffer;
  int queued_count;
  int working_on;
  
  // No need to be a pointer.
  pthread_t dispatcher_thread;
  pthread_mutex_t mutex;
  pthread_cond_t work_available;
  pthread_cond_t work_capacity_available;
};

int pool_get_max_threads();
void init_thread_pool(struct thread_pool *);
void destroy_thread_pool(struct thread_pool *);
void queue_work_item(struct thread_pool *, void *(*work_routine)(void *), void *arg);

#endif

