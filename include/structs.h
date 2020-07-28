#ifndef _STRUCTS_H
#define _STRUCTS_H

#include <sys/time.h>
#include <lpthread.h>
#include <pthread.h>
#include <list.h>

#define ROUND_ROBIN 0
#define PRIORITY 1
#define FIFO 2
#define SJF 3
#define LOTTERY 4

/* structs used for bridge variables */

typedef struct
{
  int weight;
  int length;
  int bridge_type;
  int quantum;
} bridge;

typedef struct
{
  float x;
  float y;
} point;

typedef struct
{
  float priority; // **alien
  float duration; // *(*alien + 4)
  struct timeval work_init_time;
  struct timeval last_update;
  float progress;
  float accumulator;
  short working;
  int lottery_numbers;
  int weight;
  point pos;
  lpthreads_t *thread;
  int type;
  float velocity;
  int id;
  int enterBridge;
  int crossedBridge;
  clock_t elapsed;
  lpthreads_t tid;
} alien;

typedef struct
{
  llist *north;
  llist *south;
  llist *bridge;
  int amount_to_pass;
  int bridge_weight;
  int *weight_now;
  int turn;
  bridge *bridge_struct;
} algs_params;

typedef struct
{
  int y_algorithm_confg;
  int semaphore_north_confg;
  int semaphore_south_confg;
  int quantum_confg;
  int length_confg;
  int weight_confg;
  int scheduler_confg;
  int algorithm_confg;

} configurable;

typedef struct
{
  llist *extremoN;
  llist *extremoS;
  int Y;
  int pesoTot;
  int length;
  int calendarizador;
  int quantum;
} argsBridgeY;


typedef struct
{
  llist *extremoN;
  llist *extremoS;
  int semN;
  int semS;
  int pesoTot;
  int length;
  int calendarizador;
  int quantum;
} argsBridgeSem;

typedef struct
{
  llist *extremoN;
  llist *extremoS;
  int pesoTot;
  int length;
  int calendarizador;
  int quantum;
} argsBridgeS;

typedef struct
{
  alien *alien;
  float pos_en_puente;
} alienCruzando;

typedef struct
{
  llist *comunidadA;
  llist *comunidadB;
  llist* aliens_left_north;
  llist* aliens_left_south;
  llist* aliens_right_north;
  llist* aliens_right_south;
  llist* aliens_center_north;
  llist* aliens_center_south;
}argsCalen;


#endif