#ifndef _LPTHREAD_H
#define _LPTHREAD_H
#include <ucontext.h>
#include <sys/syscall.h> // For call to gettid
#include <sys/types.h> /* For pid_t */
#include <sys/wait.h>	 /* For wait */
#include <unistd.h>		 /* For getpid */

#define STACK_SIZE (16*1024)
#define NUM_LOCKS 10
#define CONDITIONS_PER_LOCK 10 

/* The LPthread Structure
*  Contains the information about individual lpthreads.
*/
typedef struct
{
	pid_t pid;		 /* The pid of the child thread as returned by clone */
	void *stack;	 /* The stack pointer */
	char detached; // Detached or not
} lpthread_t;

typedef struct
{
	int id;
} lpthread_attr_t;

typedef struct
{
	char locked;
	pid_t pid;
} lpthread_mutex_t;
typedef struct
{
	int id;
} lpthread_mutexattr_t;

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

#endif