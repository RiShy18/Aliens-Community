#include <ucontext.h>

#define STACK_SIZE (16*1024)
#define NUM_LOCKS 10
#define CONDITIONS_PER_LOCK 10 

//the type of function used to run your threads

extern void Lmutex_init();
extern int Lthread_create( void* (*func) (void *), void *argPtr); 
extern void Lthread_yield(); 
extern void Lthread_join(int thread_id, void **result);

//exits the current thread -- closing the main thread, will terminate the program
extern void Lthread_end(void *result); 

extern void Lmutex_trylock(int lockNum); 
extern void Lmutex_unlock(int lockNum); 
extern void threadWait(int lockNum, int conditionNum); 
extern void threadSignal(int lockNum, int conditionNum); 

//this 
extern int interruptsAreDisabled;