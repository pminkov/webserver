#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "threadpool.h"
#include "threads.h"

//#define DEBUG

#ifdef DEBUG
  #define DEB printf
#else
  #define DEB(...)
#endif

const int BUFFER_MAX = 1000;
const int MAX_THREADS = 4;

int pool_get_max_threads() {
  return MAX_THREADS;
}


struct task_thread_args {
  struct thread_pool* pool;
  struct task_data td;
};

void* task_worker_thread(void *args_param) {
  struct task_thread_args *args = (struct task_thread_args *) args_param;

  args->td.work_routine(args->td.arg);

  Pthread_mutex_lock(&args->pool->mutex);
  args->pool->working_on--;
  Pthread_cond_signal(&args->pool->work_capacity_available);
  Pthread_mutex_unlock(&args->pool->mutex);

  free(args_param);

  return NULL;
}

void launch_work_task(struct thread_pool *pool, struct task_data td) {
  pool->working_on++;

  pthread_t thread;

  struct task_thread_args *args = malloc(sizeof(struct task_thread_args));
  args->pool = pool;
  args->td = td;

  Pthread_create(&thread, NULL, task_worker_thread, (void *)args);
}

void *dispatcher_thread_func(void *pool_arg) {
  struct thread_pool *pool = (struct thread_pool *)pool_arg;

  while (1) {
    Pthread_mutex_lock(&pool->mutex);

    // Wait for the right conditions that allow scheduling a new piece of work.
    while (pool->queued_count == 0 || pool->working_on == MAX_THREADS) {
      if (pool->queued_count == 0) {
        DEB("[W] Empty queue. Waiting...\n");
        Pthread_cond_wait(&pool->work_available, &pool->mutex);
      }

      if (pool->working_on == MAX_THREADS) {
        DEB("[W] Full thread capacity. Waiting ...\n");
        Pthread_cond_wait(&pool->work_capacity_available, &pool->mutex);
      }
    }

    DEB("[W] Picking item from queue:\n");

    assert(pool->queued_count > 0);
    assert(pool->working_on < MAX_THREADS);
    
    pool->queued_count--;
    launch_work_task(pool, pool->buffer[pool->queued_count]);

    Pthread_mutex_unlock(&pool->mutex);
  }
  return NULL;
}



void queue_work_item(struct thread_pool *pool, void *(*work_routine)(void*), void *arg) {
  Pthread_mutex_lock(&pool->mutex);
  DEB("[Q] Queueing one item.\n");
  if (pool->queued_count == 0) {
    Pthread_cond_signal(&pool->work_available);
  }
  struct task_data td;
  td.work_routine = work_routine;
  td.arg = arg;
  pool->buffer[pool->queued_count++] = td;

  Pthread_mutex_unlock(&pool->mutex);
}

void init_thread_pool(struct thread_pool *pool) {
  pool->queued_count = 0;
  pool->working_on = 0;
  pool->buffer = malloc(sizeof(struct task_data) * BUFFER_MAX);

  Pthread_mutex_init(&pool->mutex);
  Pthread_cond_init(&pool->work_available);
  Pthread_cond_init(&pool->work_capacity_available);

  Pthread_create(&pool->dispatcher_thread, NULL, dispatcher_thread_func, pool);
}

void destroy_thread_pool(struct thread_pool *pool) {
  Pthread_detach(pool->dispatcher_thread);

  free(pool->buffer);
}
