#define _GNU_SOURCE
#include <lpthread.h>

static int nLPthreads = 0;
static char start = 0;
static pid_t ppid;
static pid_t gpid;
static lpthreads_t listLpthreads[MAXLPTHREADS];

int Lpthread_create(lpthreads_t *thread, const lpthread_attr_t *attr, int (*startfunc)(void *), void *arg){
	if (start == 0){ 
		initLpthreads();
		start = 1;
	}
	thread->stack = malloc(STACK);
	if (thread->stack == 0){
		return -1;
	}
	thread->pid = clone(startfunc, (char *)(thread->stack + STACK),SIGCHLD |CLONE_FS |CLONE_FILES |CLONE_SIGHAND 
									|CLONE_VM |CLONE_CHILD_CLEARTID |CLONE_PTRACE,arg);
	if (thread->pid == -1){
		free(thread->stack);
		return -1;
	}
	thread->detached = 0;
	memcpy((void *)&listLpthreads[nLPthreads++], (void *)thread, sizeof(lpthreads_t));
	return 0;
}

int Lpthread_join(lpthreads_t thread, void **retval){
	int i = mapPidI(thread.pid);
	if (listLpthreads[i].detached == 0){
		waitpid(thread.pid, 0, 0);
		return 0;
	}else{
		return 1;
	}
}
int Lpthread_yield(){
	sched_yield();
	return 0;
}

int Lpthread_detach(lpthreads_t thread){
	int i = mapPidI(thread.pid);
	listLpthreads[i].detached = 1;
	return 0;
}

int Lpthread_mutex_init(lpthread_mutex_t *restrict mutex, const lmutex_attr_t *restrict attr){
	mutex->lock = 0;
	mutex->pid = 0;
	return 0;
}
int Lpthread_mutex_destroy(lpthread_mutex_t *mutex){
	mutex->lock = 0;
	mutex->pid = 0;
	return 0;
}
int Lpthread_mutex_unlock(lpthread_mutex_t *mutex){
	mutex->lock = 0;
	mutex->pid = 0;
	return 0;
}
int Lpthread_mutex_trylock(lpthread_mutex_t *mutex){
	if (mutex->lock == 0){ 
		mutex->lock = 1;
		mutex->pid = getpid();
		return 0;
	}
	return 1;
}

void initLpthreads(){
	for (int i = 0; i < MAXLPTHREADS; ++i){
		listLpthreads[i].pid = 0;
		listLpthreads[i].stack = 0;
	}
	signal(SIGINT, Lpthread_end);
	atexit(Lpthread_end); 
	gpid = getpgrp();
	ppid = getpid();
}


int Lpthread_mutex_lock(lpthread_mutex_t *mutex){
LOCK:
	while (mutex->lock);
	pid_t id = getpid();
	mutex->lock = 1;
	mutex->pid = id;
	if (mutex->pid != id){
		goto LOCK;
	}
	return 0;
}

void Lpthread_end(){
	killpg(getpgrp(), SIGKILL);
}
int mapPidI(pid_t id){
	for (int i = 0; i < MAXLPTHREADS; ++i){
		if (listLpthreads[i].pid == id){
			return i;
		}
	}
	return -1;
}
