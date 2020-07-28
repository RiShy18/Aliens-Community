#ifndef lpthreads
#define lpthreads

#include <malloc.h>	
#include <unistd.h>	
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <stdarg.h>	 
#include <signal.h>		
#include <sys/types.h> 
#include <sys/wait.h>
#include <stdlib.h>
#include <sched.h>		
#include <time.h>

#define MAXLPTHREADS 500
#define STACK (2048 * 2048)

typedef struct{
	int id;
} lmutex_attr_t;

typedef struct{
	pid_t pid;		 
	void *stack;	
	char detached; 
} lpthreads_t;

typedef struct{
	char lock;
	pid_t pid;
} lpthread_mutex_t;

typedef struct{
	int id;
} lpthread_attr_t;


int Lpthread_create(lpthreads_t *thread, const lpthread_attr_t *attr, int (*startfunc)(void *), void *arg);
int Lpthread_yield();
int Lpthread_join(lpthreads_t thread, void **retval);
int Lpthread_detach(lpthreads_t thread);
void Lpthread_end();
int Lpthread_mutex_destroy(lpthread_mutex_t *mutex);
int Lpthread_mutex_lock(lpthread_mutex_t *mutex);
int Lpthread_mutex_init(lpthread_mutex_t *restrict mutex, const lmutex_attr_t *restrict attr);
int Lpthread_mutex_unlock(lpthread_mutex_t *mutex);
int Lpthread_mutex_trylock(lpthread_mutex_t *mutex);
void initLpthreads();
int mapPidI(pid_t id);

#endif