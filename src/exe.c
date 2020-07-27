#include <SDL2/SDL.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <gui.h>
#include <utilities.h>
#include <structs.h>
#include <cfg.h>
#include <list.h>
#include <move.h>
#include <algorithms.h>


const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 720;
const int TILE_SIZE = 30;
const int ALIEN_SIZE = 30;

const int X_TILES = 46;
const int Y_TILES = 24;

int map[24][46];

point routes_a[8][3];
point routes_b[8][3];

llist *aliens_a;
llist *aliens_b;

bridge *bridge_struct_left;
bridge *bridge_struct_right;
bridge *bridge_struct_center;

llist *list_bridge_left;
llist *list_bridge_right;
llist *list_bridge_center;

llist *aliens_left_north;
llist *aliens_left_south;
llist *aliens_right_north;
llist *aliens_right_south;
llist *aliens_center_north;
llist *aliens_center_south;

algs_params *params_left;
algs_params *params_right;
algs_params *params_center;

int *weight_now_left;
int *weight_now_right;
int *weight_now_center;

alien *invader;
int invader_alive;

int list_a_size = 0;
int list_b_size = 0;
int velocity = 0;
int finish = 0;
int alien_mouse_pos = 0;

int percentages[6];

// lpthread_mutex_t lock_a;
// lpthread_mutex_t lock_b;

pthread_t invader_thread_id;

int alien_a_thread(void *param);
int alien_b_thread(void *param);
int automatic_mode_thread(void *param);
int invader_thread(void *param);

int spawn_alien(int community, int type);
int spawn_invader(void);

int calendarizadorA(void *comunidad){
  llist *list = (llist *)comunidad;
  while(1){
    //printf("Calendarizador activo\n");
    //printf("Size colonia: %d\n", llist_get_size(list));
    if(llist_get_size(list) >= 1){
      for(int i = 0; i < llist_get_size(list); i++){
        alien *actual = (alien *) llist_get_by_index(list, i);
        //printf("Posiciones x: %f y:%f\n", actual->pos.x, actual->pos.y);
        if((actual->pos.x >= 325 && actual->pos.x <= 360) && (230 <= actual->pos.y && actual->pos.y <= 285)){
          if(llist_get_size(aliens_left_north) >= 1){
            int insert = 0;
            for(int i = 0; i < llist_get_size(aliens_left_north); i++){
              alien *temp = (alien *) llist_get_by_index(aliens_left_north, i);
              if(actual->id == temp->id){
                insert = 0;
                break;
              }else{
                insert = 1;
              }
            }
            if(insert){
              llist_insert_end(aliens_left_north, actual);
              printf("Inserte en left\n");
              printf("size : %d\n", llist_get_size(aliens_left_north));
            }
          }else{
            llist_insert_end(aliens_left_north, actual);
            printf("Inserte en left\n");
            llist_print(aliens_left_north);
            printf("size : %d\n", llist_get_size(aliens_left_north));
          }
        }
        if((actual->pos.x >= 980 && actual->pos.x <= 1020) && (230 <= actual->pos.y && actual->pos.y <= 285)){
          if(llist_get_size(aliens_right_north) >= 1){
            int insert = 0;
            for(int i = 0; i < llist_get_size(aliens_right_north); i++){
              alien *temp = (alien *) llist_get_by_index(aliens_right_north, i);
              if(actual->id == temp->id){
                insert = 0;
                break;
              }else{
                insert = 1;
              }
            }
            if(insert){
              llist_insert_end(aliens_right_north, actual);
              printf("Inserte en right\n");
              printf("size : %d\n", llist_get_size(aliens_right_north));
            }
          }else{
            llist_insert_end(aliens_right_north, actual);
            printf("Inserte en right\n");
            printf("size : %d\n", llist_get_size(aliens_right_north));
          }
        }
        if((actual->pos.x >= 655 && actual->pos.x <= 695) && (230 <= actual->pos.y && actual->pos.y <= 285)){
          if(llist_get_size(aliens_center_north) >= 1){
            int insert = 0;
            for(int i = 0; i < llist_get_size(aliens_center_north); i++){
              alien *temp = (alien *) llist_get_by_index(aliens_center_north, i);
              if(actual->id == temp->id){
                insert = 0;
                break;
              }else{
                insert = 1;
              }
            }
            if(insert){
              llist_insert_end(aliens_center_north, actual);
              printf("Inserte en center\n");
              printf("size : %d\n", llist_get_size(aliens_center_north));
            }
          }else{
            llist_insert_end(aliens_center_north, actual);
            printf("Inserte en center\n");
            printf("size : %d\n", llist_get_size(aliens_center_north));
          }
        }
      }
    }
    sleep(5);
  }
}



int calendarizadorB(void *comunidad){
  llist *list = (llist *)comunidad;
  while(1){
    //printf("Calendarizador activo\n");
    //printf("Size colonia: %d\n", llist_get_size(list));
    if(llist_get_size(list) >= 1){
      for(int i = 0; i < llist_get_size(list); i++){
        alien *actual = (alien *) llist_get_by_index(list, i);
        //printf("Posiciones x: %f y:%f\n", actual->pos.x, actual->pos.y);
        if((actual->pos.x >= 350 && actual->pos.x <= 365) && (360 <= actual->pos.y && actual->pos.y <= 445)){
          if(llist_get_size(aliens_left_south) >= 1){
            int insert = 0;
            for(int i = 0; i < llist_get_size(aliens_left_south); i++){
              alien *temp = (alien *) llist_get_by_index(aliens_left_south, i);
              if(actual->id == temp->id){
                insert = 0;
                break;
              }else{
                insert = 1;
              }
            }
            if(insert){
              llist_insert_end(aliens_left_south, actual);
              printf("Inserte en left\n");
              printf("size : %d\n", llist_get_size(aliens_left_south));
            }
          }else{
            llist_insert_end(aliens_left_south, actual);
            printf("Inserte en left\n");
            llist_print(aliens_left_south);
            printf("size : %d\n", llist_get_size(aliens_left_south));
          }
        }
        if((actual->pos.x >= 1020 && actual->pos.x <= 1025) && (384 <= actual->pos.y && actual->pos.y <= 445)){
          if(llist_get_size(aliens_right_south) >= 1){
            int insert = 0;
            for(int i = 0; i < llist_get_size(aliens_right_south); i++){
              alien *temp = (alien *) llist_get_by_index(aliens_right_south, i);
              if(actual->id == temp->id){
                insert = 0;
                break;
              }else{
                insert = 1;
              }
            }
            if(insert){
              llist_insert_end(aliens_right_south, actual);
              printf("Inserte en right\n");
              printf("size : %d\n", llist_get_size(aliens_right_south));
            }
          }else{
            llist_insert_end(aliens_right_south, actual);
            printf("Inserte en right\n");
            printf("size : %d\n", llist_get_size(aliens_right_south));
          }
        }
        if((actual->pos.x >= 690 && actual->pos.x <= 695) && (384 <= actual->pos.y && actual->pos.y <= 445)){
          if(llist_get_size(aliens_center_south) >= 1){
            int insert = 0;
            for(int i = 0; i < llist_get_size(aliens_center_south); i++){
              alien *temp = (alien *) llist_get_by_index(aliens_center_south, i);
              if(actual->id == temp->id){
                insert = 0;
                break;
              }else{
                insert = 1;
              }
            }
            if(insert){
              llist_insert_end(aliens_center_south, actual);
              printf("Inserte en center\n");
              printf("size : %d\n", llist_get_size(aliens_center_south));
            }
          }else{
            llist_insert_end(aliens_center_south, actual);
            printf("Inserte en center\n");
            printf("size : %d\n", llist_get_size(aliens_center_south));
          }
        }
      }
    }
    sleep(5);
  }
}

alien *calen_prioridad(llist *extremo){
  alien *max = (alien *) malloc(sizeof(alien));
  max->priority = -1;
  int index = -1;
  for(int i = 0; i < llist_get_size(extremo); i++){
    alien *temp = llist_get_by_index(extremo, i);
    if(temp->priority > max->priority){
      max = temp;
      index = i;
    }
  }
  llist_remove_by_index(extremo, index);
  return max;
}

alien *calen_FIFO(llist *extremo){
  alien *max = (alien *) llist_get_by_index(extremo, 0);
  llist_remove_by_index(extremo, 0);
  return max;
}


alien *calen_mascorto(llist *extremo, int bLength){
  alien *max = (alien *) malloc(sizeof(alien));
  max->priority = -1;
  int index = -1;
  for(int i = 0; i < llist_get_size(extremo); i++){
    float tiempo1 = 0;
    float tiempo2 = 0;
    alien *temp = llist_get_by_index(extremo, i);
    if(max->priority == -1){
      max = temp;
      index = i;
    }else{
      tiempo1 = bLength / max->velocity;
      tiempo2 = bLength / temp->velocity;
      if(tiempo2 < tiempo1){
        max = temp;
        index = i;
      }
    }
  }
  llist_remove_by_index(extremo, index);
  return max;
}

alien *calen_lotterry(llist *extremo){
  llist *assign = llist_create(NULL);
  llist *priority = llist_create(NULL);
  for(int i = 0; i < llist_get_size(extremo); i++){
    alien *temp = llist_get_by_index(extremo, i);
    llist_insert_end(assign, temp);
  }
  while(llist_get_size(assign) > 0){
    alien *prior = calen_prioridad(assign);
    if(prior->priority == 2){
      prior->lottery_numbers = 10;
    }else if(prior->priority == 1){
      prior->lottery_numbers = 5;
    }else if(prior->priority == 0){
      prior->lottery_numbers = 3;
    }
    llist_insert_end(priority, prior);
  }
  int maxLot = 0;
  for(int i = 0;  i < llist_get_size(priority); i++){
    alien *temp = (alien *) llist_get_by_index(priority, i);
    maxLot += temp->lottery_numbers;
  }

  int lot = generate_random(maxLot, 1);

  int maxL = 0;
  int downLimit = 0;
  int index = -1;
  alien *winner;
  for(int i = 0; i < llist_get_size(priority); i++){
    winner = (alien *) llist_get_by_index(priority, i);
    maxL = downLimit;
    downLimit += winner->lottery_numbers;
      printf("maxL: %d lot: %d downLimit: %d\n", maxL , lot, downLimit);
    if(maxL < lot && lot < downLimit + 1){
      index = i; 
      break;
    }
  }
  llist_remove_by_index(extremo, index);
  printf("Ya alguien gano la loteria\n");
  return winner;
}

alien *calen_RR(llist *extremo){
  alien *max = (alien *) llist_get_by_index(extremo, 0);
  llist_remove_by_index(extremo, 0);
  return max;
}


void *bridgeY(void *arguments){
  argsBridgeY *args = (argsBridgeY *) arguments;
  llist *aliens_en_puente = llist_create(NULL);
  //printf("PesoTot: %d, Algoritmo: %d\n", args->pesoTot, args->calendarizador);
  
  llist *extremoAct;

  int sentido = 0;

  int pasados = 0;

  while(1){
    if(pasados >= args->Y && llist_get_size(aliens_en_puente) == 0){
      sentido = !sentido;
      pasados = 0;
      printf("Caambio Sentido\n");
    }else{
      if(llist_get_size(aliens_en_puente) == 0){
        int sizeN = llist_get_size(args->extremoN);
        int sizeS = llist_get_size(args->extremoS);
        if((0 <= sizeN  && sizeN < args->Y ) || (0 <= sizeS  && sizeS < args->Y)){
          if(sizeN < sizeS){
            sentido = 1;
            pasados = 0;
          }else{
            sentido = 0;
            pasados = 0;
          }
        }
      }
    }

    if(sentido == 0){
      extremoAct = args->extremoN;
    }else{
      extremoAct = args->extremoS;
    }

    if(llist_get_size(extremoAct) >= 1){
      int pesoActual = 0;
      for(int i = 0; i < llist_get_size(aliens_en_puente); i++){
        alienCruzando *temp = (alienCruzando *) llist_get_by_index(aliens_en_puente, i);
        pesoActual += temp->alien->weight;
      }
      printf("Peso actual: %d size: %d, peso_tot: %d\n", pesoActual, llist_get_size(aliens_en_puente), args->pesoTot);
      alien *go;
      switch (args->calendarizador)
      {
      case 0:
        go = calen_RR(extremoAct);
        break;
      case 1:
        go = calen_prioridad(extremoAct);
        break;

      case 2:
        go = calen_mascorto(extremoAct, args->length);
        break;

      case 3:
        go = calen_FIFO(extremoAct);
        break;

      case 4:
        go = calen_lotterry(extremoAct);
        break;

      default:
        go = calen_prioridad(extremoAct);
        break;
      }
      if((pesoActual + go->weight) < args->pesoTot){
        alienCruzando *repetido;
        int insert = 0;
        for(int i = 0; i < llist_get_size(aliens_en_puente); i++){
          repetido = (alienCruzando *) llist_get_by_index(aliens_en_puente, i);
          if(repetido->alien == go){
            insert = 0;
            break;
          }else{
            insert = 1;
          }
        }
        if(insert || llist_get_size(aliens_en_puente) == 0){
          usleep(16666 * 2);
          go->enterBridge = 1;
          alienCruzando *insert = (alienCruzando *)malloc(sizeof(alienCruzando));
          if(go->elapsed != NULL && args->calendarizador == 0){
            if(sentido){
              go->pos.x -= 100;
            }else{
              go->pos.x += 100;
            }
          }
          go->elapsed = clock();
          insert->alien = go;
          insert->pos_en_puente = 0;
          printf("Me cai\n");
          llist_insert_end(aliens_en_puente, insert);
          pasados++;
        }
      }
    }
    if(llist_get_size(aliens_en_puente) > 0){
      for(int i = 0; i < llist_get_size(aliens_en_puente); i++){
        alienCruzando *temp = (alienCruzando *) llist_get_by_index(aliens_en_puente, i);
        if(args->calendarizador == 0){
          temp->pos_en_puente = temp->alien->progress;
        }
        temp->pos_en_puente += temp->alien->velocity;
        temp->alien->progress = temp->pos_en_puente;
        printf("Posicion en puente: %f\n", temp->pos_en_puente);
        float elapsed = (float) (clock() - temp->alien->elapsed) / CLOCKS_PER_SEC;
        if(temp->pos_en_puente >= args->length){
          temp->alien->crossedBridge = 1;
          llist_remove_by_index(aliens_en_puente, i);
          break;
        }
        if(elapsed >= args->quantum && args->calendarizador == 0){
          llist_remove_by_index(aliens_en_puente, i);
          if(sentido){
            temp->alien->pos.x += 100;
          }else{
            temp->alien->pos.x -= 100;
          }
          llist_insert_end(extremoAct, temp->alien);
          break;
        }
      }
    }
    sleep(1);
  }
}

void *bridgeSurv(void *arguments){
  argsBridgeS *args = (argsBridgeS *) arguments;
  llist *aliens_en_puente = llist_create(NULL);
  
  llist *extremoAct;

  int sentido = 0;

  int pasados = 0;
  printf("PesoTot: %d, Algoritmo: %d\n", args->pesoTot, args->calendarizador);

  clock_t start;


  while(1){

    if(llist_get_size(args->extremoN) > 0 && llist_get_size(aliens_en_puente) == 0){
      sentido = 0;
    }else if(llist_get_size(aliens_en_puente) == 0){
      sentido = 1;
    }

    if(sentido == 0){
      extremoAct = args->extremoN;
    }else{
      extremoAct = args->extremoS;
    }
    if(llist_get_size(extremoAct) >= 1){
      int pesoActual = 0;
      for(int i = 0; i < llist_get_size(aliens_en_puente); i++){
        alienCruzando *temp = (alienCruzando *) llist_get_by_index(aliens_en_puente, i);
        pesoActual += temp->alien->weight;
      }
      alien *go;
      switch (args->calendarizador)
      {
      case 0:
        go = calen_RR(extremoAct);
        break;
      case 1:
        go = calen_prioridad(extremoAct);
        break;

      case 2:
        go = calen_mascorto(extremoAct, args->length);
        break;

      case 3:
        go = calen_FIFO(extremoAct);
        break;

      case 4:
        go = calen_lotterry(extremoAct);
        break;

      default:
        go = calen_prioridad(extremoAct);
        break;
      }
      if((pesoActual + go->weight) < args->pesoTot){
        alienCruzando *repetido;
        int insert = 0;
        for(int i = 0; i < llist_get_size(aliens_en_puente); i++){
          repetido = (alienCruzando *) llist_get_by_index(aliens_en_puente, i);
          if(repetido->alien == go){
            insert = 0;
            break;
          }else{
            insert = 1;
          }
        }
        if(insert || llist_get_size(aliens_en_puente) == 0){
          usleep(16666 * 2);
          go->enterBridge = 1;
          if(go->elapsed != NULL && args->calendarizador == 0){
            if(sentido){
              go->pos.x -= 100;
            }else{
              go->pos.x += 100;
            }
          }
          go->elapsed = clock();
          alienCruzando *insert = (alienCruzando *)malloc(sizeof(alienCruzando));
          insert->alien = go;
          insert->pos_en_puente = 0;
          llist_insert_end(aliens_en_puente, insert);
          pasados++;
        }
      }
    }
    if(llist_get_size(aliens_en_puente) > 0){
      for(int i = 0; i < llist_get_size(aliens_en_puente); i++){
        alienCruzando *temp = (alienCruzando *) llist_get_by_index(aliens_en_puente, i);
        if(args->calendarizador == 0){
          temp->pos_en_puente = temp->alien->progress;
        }
        temp->pos_en_puente += temp->alien->velocity;
        temp->alien->progress = temp->pos_en_puente;
        printf("Posicion en puente: %f\n", temp->pos_en_puente);
        float elapsed = (float) (clock() - temp->alien->elapsed) / CLOCKS_PER_SEC;
        if(temp->pos_en_puente >= args->length){
          temp->alien->crossedBridge = 1;
          llist_remove_by_index(aliens_en_puente, i);
          break;
        }
        if(elapsed >= args->quantum && args->calendarizador == 0){
          llist_remove_by_index(aliens_en_puente, i);
          if(sentido){
            temp->alien->pos.x += 100;
          }else{
            temp->alien->pos.x -= 100;
          }
          llist_insert_end(extremoAct, temp->alien);
          break;
        }
      }
    }
    sleep(1);
  }
}

void *bridgeSem(void *arguments){
  argsBridgeSem *args = (argsBridgeSem *) arguments;
  llist *aliens_en_puente = llist_create(NULL);
  
  llist *extremoAct;

  int sentido = 0;

  int pasados = 0;

  clock_t start, end;

  int tiempoSemaforo = 0;

  //printf("PesoTot: %d, Algoritmo: %d\n", args->pesoTot, args->calendarizador);

  start = clock();

  while(1){
    
    end = clock();

    float elapsed = (float) (end - start) / CLOCKS_PER_SEC;

    printf("Elapsed time: %f, Sentido: %d\n", elapsed, sentido);
    if(sentido == 0){
      if(elapsed >= args->semN && llist_get_size(aliens_en_puente) == 0){
        sentido = 1;
        tiempoSemaforo = args->semS;
        start = clock();
      }
    }else{
      if(elapsed >= args->semS && llist_get_size(aliens_en_puente) == 0){
        sentido = 0;
        tiempoSemaforo = args->semN;
        start = clock();
      }
    }

    if(sentido == 0){
      extremoAct = args->extremoN;
    }else{
      extremoAct = args->extremoS;
    }

    if(llist_get_size(extremoAct) >= 1 && elapsed < tiempoSemaforo){
      int pesoActual = 0;
      for(int i = 0; i < llist_get_size(aliens_en_puente); i++){
        alienCruzando *temp = (alienCruzando *) llist_get_by_index(aliens_en_puente, i);
        pesoActual += temp->alien->weight;
      }
      printf("Peso actual: %d size: %d, peso_tot: %d\n", pesoActual, llist_get_size(aliens_en_puente), args->pesoTot);
      alien *go;
      switch (args->calendarizador)
      {
      case 0:
        go = calen_prioridad(extremoAct);
        break;

      case 1:
        go = calen_prioridad(extremoAct);
        break;

      case 2:
        go = calen_mascorto(extremoAct, args->length);
        break;

      case 3:
        go = calen_FIFO(extremoAct);
        break;

      case 4:
        go = calen_lotterry(extremoAct);
      break;

      default:
        go = calen_prioridad(extremoAct);
        break;
      }
      if((pesoActual + go->weight) < args->pesoTot){
        alienCruzando *repetido;
        int insert = 0;
        for(int i = 0; i < llist_get_size(aliens_en_puente); i++){
          repetido = (alienCruzando *) llist_get_by_index(aliens_en_puente, i);
          if(repetido->alien == go){
            insert = 0;
            break;
          }else{
            insert = 1;
          }
        }
        if(insert || llist_get_size(aliens_en_puente) == 0){
          go->enterBridge = 1;
          alienCruzando *insert = (alienCruzando *)malloc(sizeof(alienCruzando));
          if(go->elapsed != NULL && args->calendarizador == 0){
            if(sentido){
              go->pos.x -= 100;
            }else{
              go->pos.x += 100;
            }
          }
          go->elapsed = clock();
          insert->alien = go;
          insert->pos_en_puente = 0;
          printf("Me cai\n");
          llist_insert_end(aliens_en_puente, insert);
          pasados++;
          usleep(166666 * 2);
        }
      }
    }
    if(llist_get_size(aliens_en_puente) > 0){
      for(int i = 0; i < llist_get_size(aliens_en_puente); i++){
        alienCruzando *temp = (alienCruzando *) llist_get_by_index(aliens_en_puente, i);
        if(args->calendarizador == 0){
          temp->pos_en_puente = temp->alien->progress;
        }
        temp->pos_en_puente += temp->alien->velocity;
        temp->alien->progress = temp->pos_en_puente;
        printf("Posicion en puente: %f\n", temp->pos_en_puente);
        float elapsed = (float) (clock() - temp->alien->elapsed) / CLOCKS_PER_SEC;
        if(temp->pos_en_puente >= args->length){
          temp->alien->crossedBridge = 1;
          llist_remove_by_index(aliens_en_puente, i);
          break;
        }
        if(elapsed >= args->quantum && args->calendarizador == 0){
          llist_remove_by_index(aliens_en_puente, i);
          if(sentido){
            temp->alien->pos.x += 100;
          }else{
            temp->alien->pos.x -= 100;
          }
          llist_insert_end(extremoAct, temp->alien);
          break;
        }
      }
    }
    sleep(1);
  }
}

int main(int argc, char *argv[])
{
  int medium = 0;
  int manual = 0;

  if (!valdite_args(argc, argv, &medium))
  {
    return 1;
  }

  if (init_graphics() != 0)
  {
    return 1;
  }

  if (!check_bin_dir())
  {
    printf("Please execute this program from the bin directory\n");
    return 1;
  }

  if (!load_map(map))
  {
    printf("Can't read map\n");
    return 1;
  }

  if (!init_cfg())
  {
    printf("Can't read configuration file\n");
    return 1;
  }

  // if (Lmutex_init(&lock_a, NULL) != 0)
  // {
  //   printf("\n Mutex for aliens A init has failed\n");
  //   return 1;
  // }

  // if (Lmutex_init(&lock_b, NULL) != 0)
  // {
  //   printf("\n Mutex for aliens B init has failed\n");
  //   return 1;
  // }

  srand(time(NULL));

  aliens_a = llist_create(NULL);
  aliens_b = llist_create(NULL);

  list_bridge_left = llist_create(NULL);
  list_bridge_right = llist_create(NULL);
  list_bridge_center = llist_create(NULL);

  aliens_left_north = llist_create(NULL);
  aliens_left_south = llist_create(NULL);
  aliens_right_north = llist_create(NULL);
  aliens_right_south = llist_create(NULL);
  aliens_center_north = llist_create(NULL);
  aliens_center_south = llist_create(NULL);

  bridge_struct_left = (bridge *)malloc(sizeof(bridge));

  bridge_struct_right = (bridge *)malloc(sizeof(bridge));

  bridge_struct_center = (bridge *)malloc(sizeof(bridge));

  configurable *test = (configurable *)malloc(sizeof(configurable));
  load_bridge_center(test);

  printf("WEIGHT = %d\n", test->weight_confg);
  printf("LENGTH = %d\n", test->length_confg);
  printf("QUANTUM = %d\n", test->quantum_confg);
  printf("SCHEDULER = %d\n", test->scheduler_confg);
  printf("ALGORITHM = %d\n", test->algorithm_confg);
  printf("Y = %d\n", test->y_algorithm_confg);
  printf("SEMAPHORE N = %d\n", test->semaphore_south_confg);
  printf("SEMAPHORE S = %d\n", test->semaphore_south_confg);

  bridge_struct_left->weight = 20;
  bridge_struct_left->length = 50;
  bridge_struct_left->bridge_type = ROUND_ROBIN;
  bridge_struct_left->quantum = 30;

  weight_now_left = (int *)malloc(sizeof(int));
  *weight_now_left = 0;

  params_left = (algs_params *)malloc(sizeof(algs_params));
  params_left->north = aliens_left_north;
  params_left->south = aliens_left_south;
  params_left->bridge = list_bridge_left;
  params_left->amount_to_pass = 5;
  params_left->bridge_weight = 50;
  params_left->weight_now = weight_now_left;
  params_left->bridge_struct = bridge_struct_left;

  pthread_t algorithms;

  //Lthread_create(&algorithms, NULL, &semaphore_algorithm, params_left);

  invader_alive = 0;

  memset(percentages, 0, 6);
  load_alien(&velocity, percentages);

  pthread_t automatic_mode;

  if (medium != 0)
  {
    printf("Automatic Mode Selected\n");

    double *arg = malloc(sizeof(*arg));
    *arg = (float)medium / 100;

    pthread_t tid1, tid2 ,tBridgeL, tBridgeC, tBridgeR;
    pthread_create(&automatic_mode, NULL, &automatic_mode_thread, arg);

    pthread_create(&tid1, NULL, &calendarizadorB, aliens_b);
    pthread_create(&tid2, NULL, &calendarizadorA, aliens_a);

    configurable *bridgeLeft = (configurable *)malloc(sizeof(configurable));

    load_bridge_left(bridgeLeft);

    argsBridgeY *bridgeYL = (argsBridgeY *) malloc(sizeof(argsBridgeY));

    argsBridgeSem *bridgeSemL = (argsBridgeSem *) malloc(sizeof(argsBridgeSem));

    argsBridgeS *bridgeSL = (argsBridgeS *) malloc(sizeof(argsBridgeS));



    switch (bridgeLeft->algorithm_confg)
    {
    case 0:

      bridgeYL->extremoS = aliens_left_south;
      bridgeYL->extremoN = aliens_left_north;
      bridgeYL->Y = bridgeLeft->y_algorithm_confg;
      bridgeYL->pesoTot = bridgeLeft->weight_confg;
      bridgeYL->length = bridgeLeft->length_confg;
      bridgeYL->calendarizador = bridgeLeft->scheduler_confg;
      bridgeYL->quantum = bridgeLeft->quantum_confg;

      pthread_create(&tBridgeL, NULL, &bridgeY, bridgeYL);
      break;
    
    case 1:
      
      bridgeSemL->extremoS = aliens_left_south;
      bridgeSemL->extremoN = aliens_left_north;
      bridgeSemL->pesoTot = bridgeLeft->weight_confg;
      bridgeSemL->length = bridgeLeft->length_confg;
      bridgeSemL->semN = bridgeLeft->semaphore_north_confg;
      bridgeSemL->semS = bridgeLeft->semaphore_south_confg;
      bridgeSemL->calendarizador = bridgeLeft->scheduler_confg;
      bridgeSemL->quantum = bridgeLeft->quantum_confg;

      pthread_create(&tBridgeL, NULL, &bridgeSem, bridgeSemL);
      break;
      

    case 2:

      bridgeSL->extremoS = aliens_left_south;
      bridgeSL->extremoN = aliens_left_north;
      bridgeSL->pesoTot = bridgeLeft->weight_confg;
      bridgeSL->length = bridgeLeft->length_confg;
      bridgeSL->calendarizador = bridgeLeft->scheduler_confg;
      bridgeSL->quantum = bridgeLeft->quantum_confg;

      pthread_create(&tBridgeL, NULL, &bridgeSurv, bridgeSL);
      break;

    default:
      bridgeSL->extremoS = aliens_left_south;
      bridgeSL->extremoN = aliens_left_north;
      bridgeSL->pesoTot = bridgeLeft->weight_confg;
      bridgeSL->length = bridgeLeft->length_confg;
      bridgeSL->calendarizador = bridgeLeft->scheduler_confg;
      bridgeSL->quantum = bridgeLeft->quantum_confg;

      pthread_create(&tBridgeL, NULL, &bridgeSurv, bridgeSL);
      break;
    }

    configurable *bridgeRight = (configurable *)malloc(sizeof(configurable));

    load_bridge_right(bridgeRight);

    argsBridgeY *bridgeYR = (argsBridgeY *) malloc(sizeof(argsBridgeY));

    argsBridgeSem *bridgeSemR = (argsBridgeSem *) malloc(sizeof(argsBridgeSem));

    argsBridgeS *bridgeSR = (argsBridgeS *) malloc(sizeof(argsBridgeS));

    switch (bridgeRight->algorithm_confg)
    {
    case 0:

      bridgeYR->extremoS = aliens_right_south;
      bridgeYR->extremoN = aliens_right_north;
      bridgeYR->Y = bridgeRight->y_algorithm_confg;
      bridgeYR->pesoTot = bridgeRight->weight_confg;
      bridgeYR->length = bridgeRight->length_confg;
      bridgeYR->calendarizador = bridgeRight->scheduler_confg;
      bridgeYR->quantum = bridgeRight->quantum_confg;

      pthread_create(&tBridgeR, NULL, &bridgeY, bridgeYR);
      break;
    
    case 1:

      bridgeSemR->extremoS = aliens_right_south;
      bridgeSemR->extremoN = aliens_right_north;
      bridgeSemR->pesoTot = bridgeRight->weight_confg;
      bridgeSemR->length = bridgeRight->length_confg;
      bridgeSemR->semN = bridgeRight->semaphore_north_confg;
      bridgeSemR->semS = bridgeRight->semaphore_south_confg;
      bridgeSemR->calendarizador = bridgeRight->scheduler_confg;
      bridgeSemR->quantum = bridgeRight->quantum_confg;


      pthread_create(&tBridgeR, NULL, &bridgeSem, bridgeSemR);
      break;
      

    case 2:

      bridgeSR->extremoS = aliens_right_south;
      bridgeSR->extremoN = aliens_right_north;
      bridgeSR->pesoTot = bridgeRight->weight_confg;
      bridgeSR->length = bridgeRight->length_confg;
      bridgeSR->calendarizador = bridgeRight->scheduler_confg;
      bridgeSR->quantum = bridgeRight->quantum_confg;

      pthread_create(&tBridgeR, NULL, &bridgeSurv, bridgeSR);
      break;

    default:

      bridgeSR->extremoS = aliens_right_south;
      bridgeSR->extremoN = aliens_right_north;
      bridgeSR->pesoTot = bridgeRight->weight_confg;
      bridgeSR->length = bridgeRight->length_confg;
      bridgeSR->calendarizador = bridgeRight->scheduler_confg;
      bridgeSR->quantum = bridgeRight->quantum_confg;

      pthread_create(&tBridgeR, NULL, &bridgeSurv, bridgeSR);
      break;
    }

    configurable *bridgeCenter = (configurable *)malloc(sizeof(configurable));

    load_bridge_center(bridgeCenter);

    argsBridgeY *bridgeYC = (argsBridgeY *) malloc(sizeof(argsBridgeY));

    argsBridgeSem *bridgeSemC = (argsBridgeSem *) malloc(sizeof(argsBridgeSem));

    argsBridgeS *bridgeSC = (argsBridgeS *) malloc(sizeof(argsBridgeS));


    switch (bridgeCenter->algorithm_confg)
    {
    case 0:

      bridgeYC->extremoS = aliens_center_south;
      bridgeYC->extremoN = aliens_center_north;
      bridgeYC->Y = bridgeCenter->y_algorithm_confg;
      bridgeYC->pesoTot = bridgeCenter->weight_confg;
      bridgeYC->length = bridgeCenter->length_confg;
      bridgeYC->calendarizador = bridgeCenter->scheduler_confg;
      bridgeYC->quantum = bridgeCenter->quantum_confg;


      pthread_create(&tBridgeC, NULL, &bridgeY, bridgeYC);
      break;
    
    case 1:

      bridgeSemC->extremoS = aliens_center_south;
      bridgeSemC->extremoN = aliens_center_north;
      bridgeSemC->pesoTot = bridgeCenter->weight_confg;
      bridgeSemC->length = bridgeCenter->length_confg;
      bridgeSemC->semN = bridgeCenter->semaphore_north_confg;
      bridgeSemC->semS = bridgeCenter->semaphore_south_confg;
      bridgeSemC->calendarizador = bridgeCenter->scheduler_confg;
      bridgeSemC->quantum = bridgeCenter->quantum_confg;


      pthread_create(&tBridgeC, NULL, &bridgeSem, bridgeSemC);
      break;
      

    case 2:

      bridgeSC->extremoS = aliens_center_south;
      bridgeSC->extremoN = aliens_center_north;
      bridgeSC->pesoTot = bridgeCenter->weight_confg;
      bridgeSC->length = bridgeCenter->length_confg;
      bridgeSC->calendarizador = bridgeCenter->scheduler_confg;
      bridgeSC->quantum = bridgeCenter->quantum_confg;


      pthread_create(&tBridgeC, NULL, &bridgeSurv, bridgeSC);
      break;

    default:
      bridgeSC->extremoS = aliens_center_south;
      bridgeSC->extremoN = aliens_center_north;
      bridgeSC->pesoTot = bridgeCenter->weight_confg;
      bridgeSC->length = bridgeCenter->length_confg;
      bridgeSC->calendarizador = bridgeCenter->scheduler_confg;
      bridgeSC->quantum = bridgeCenter->quantum_confg;
      
      pthread_create(&tBridgeC, NULL, &bridgeSurv, bridgeSC);
      break;
    }

  }
  else
  {
    printf("Manual Mode Selected\n");
    manual = 1;
    pthread_t tid1, tid2 ,tBridgeL, tBridgeC, tBridgeR;

    pthread_create(&tid1, NULL, &calendarizadorB, aliens_b);
    pthread_create(&tid2, NULL, &calendarizadorA, aliens_a);

    configurable *bridgeLeft = (configurable *)malloc(sizeof(configurable));

    load_bridge_left(bridgeLeft);

    argsBridgeY *bridgeYL = (argsBridgeY *) malloc(sizeof(argsBridgeY));

    argsBridgeSem *bridgeSemL = (argsBridgeSem *) malloc(sizeof(argsBridgeSem));

    argsBridgeS *bridgeSL = (argsBridgeS *) malloc(sizeof(argsBridgeS));



    switch (bridgeLeft->algorithm_confg)
    {
    case 0:

      bridgeYL->extremoS = aliens_left_south;
      bridgeYL->extremoN = aliens_left_north;
      bridgeYL->Y = bridgeLeft->y_algorithm_confg;
      bridgeYL->pesoTot = bridgeLeft->weight_confg;
      bridgeYL->length = bridgeLeft->length_confg;
      bridgeYL->calendarizador = bridgeLeft->scheduler_confg;
      bridgeYL->quantum = bridgeLeft->quantum_confg;

      pthread_create(&tBridgeL, NULL, &bridgeY, bridgeYL);
      break;
    
    case 1:
      
      bridgeSemL->extremoS = aliens_left_south;
      bridgeSemL->extremoN = aliens_left_north;
      bridgeSemL->pesoTot = bridgeLeft->weight_confg;
      bridgeSemL->length = bridgeLeft->length_confg;
      bridgeSemL->semN = bridgeLeft->semaphore_north_confg;
      bridgeSemL->semS = bridgeLeft->semaphore_south_confg;
      bridgeSemL->calendarizador = bridgeLeft->scheduler_confg;
      bridgeSemL->quantum = bridgeLeft->quantum_confg;

      pthread_create(&tBridgeL, NULL, &bridgeSem, bridgeSemL);
      break;
      

    case 2:

      bridgeSL->extremoS = aliens_left_south;
      bridgeSL->extremoN = aliens_left_north;
      bridgeSL->pesoTot = bridgeLeft->weight_confg;
      bridgeSL->length = bridgeLeft->length_confg;
      bridgeSL->calendarizador = bridgeLeft->scheduler_confg;
      bridgeSL->quantum = bridgeLeft->quantum_confg;

      pthread_create(&tBridgeL, NULL, &bridgeSurv, bridgeSL);
      break;

    default:
      bridgeSL->extremoS = aliens_left_south;
      bridgeSL->extremoN = aliens_left_north;
      bridgeSL->pesoTot = bridgeLeft->weight_confg;
      bridgeSL->length = bridgeLeft->length_confg;
      bridgeSL->calendarizador = bridgeLeft->scheduler_confg;
      bridgeSL->quantum = bridgeLeft->quantum_confg;

      pthread_create(&tBridgeL, NULL, &bridgeSurv, bridgeSL);
      break;
    }

    configurable *bridgeRight = (configurable *)malloc(sizeof(configurable));

    load_bridge_right(bridgeRight);

    argsBridgeY *bridgeYR = (argsBridgeY *) malloc(sizeof(argsBridgeY));

    argsBridgeSem *bridgeSemR = (argsBridgeSem *) malloc(sizeof(argsBridgeSem));

    argsBridgeS *bridgeSR = (argsBridgeS *) malloc(sizeof(argsBridgeS));

    switch (bridgeRight->algorithm_confg)
    {
    case 0:

      bridgeYR->extremoS = aliens_right_south;
      bridgeYR->extremoN = aliens_right_north;
      bridgeYR->Y = bridgeRight->y_algorithm_confg;
      bridgeYR->pesoTot = bridgeRight->weight_confg;
      bridgeYR->length = bridgeRight->length_confg;
      bridgeYR->calendarizador = bridgeRight->scheduler_confg;
      bridgeYR->quantum = bridgeRight->quantum_confg;

      pthread_create(&tBridgeR, NULL, &bridgeY, bridgeYR);
      break;
    
    case 1:

      bridgeSemR->extremoS = aliens_right_south;
      bridgeSemR->extremoN = aliens_right_north;
      bridgeSemR->pesoTot = bridgeRight->weight_confg;
      bridgeSemR->length = bridgeRight->length_confg;
      bridgeSemR->semN = bridgeRight->semaphore_north_confg;
      bridgeSemR->semS = bridgeRight->semaphore_south_confg;
      bridgeSemR->calendarizador = bridgeRight->scheduler_confg;
      bridgeSemR->quantum = bridgeRight->quantum_confg;


      pthread_create(&tBridgeR, NULL, &bridgeSem, bridgeSemR);
      break;
      

    case 2:

      bridgeSR->extremoS = aliens_right_south;
      bridgeSR->extremoN = aliens_right_north;
      bridgeSR->pesoTot = bridgeRight->weight_confg;
      bridgeSR->length = bridgeRight->length_confg;
      bridgeSR->calendarizador = bridgeRight->scheduler_confg;
      bridgeSR->quantum = bridgeRight->quantum_confg;

      pthread_create(&tBridgeR, NULL, &bridgeSurv, bridgeSR);
      break;

    default:

      bridgeSR->extremoS = aliens_right_south;
      bridgeSR->extremoN = aliens_right_north;
      bridgeSR->pesoTot = bridgeRight->weight_confg;
      bridgeSR->length = bridgeRight->length_confg;
      bridgeSR->calendarizador = bridgeRight->scheduler_confg;
      bridgeSR->quantum = bridgeRight->quantum_confg;

      pthread_create(&tBridgeR, NULL, &bridgeSurv, bridgeSR);
      break;
    }

    configurable *bridgeCenter = (configurable *)malloc(sizeof(configurable));

    load_bridge_center(bridgeCenter);

    argsBridgeY *bridgeYC = (argsBridgeY *) malloc(sizeof(argsBridgeY));

    argsBridgeSem *bridgeSemC = (argsBridgeSem *) malloc(sizeof(argsBridgeSem));

    argsBridgeS *bridgeSC = (argsBridgeS *) malloc(sizeof(argsBridgeS));


    switch (bridgeCenter->algorithm_confg)
    {
    case 0:

      bridgeYC->extremoS = aliens_center_south;
      bridgeYC->extremoN = aliens_center_north;
      bridgeYC->Y = bridgeCenter->y_algorithm_confg;
      bridgeYC->pesoTot = bridgeCenter->weight_confg;
      bridgeYC->length = bridgeCenter->length_confg;
      bridgeYC->calendarizador = bridgeCenter->scheduler_confg;
      bridgeYC->quantum = bridgeCenter->quantum_confg;


      pthread_create(&tBridgeC, NULL, &bridgeY, bridgeYC);
      break;
    
    case 1:

      bridgeSemC->extremoS = aliens_center_south;
      bridgeSemC->extremoN = aliens_center_north;
      bridgeSemC->pesoTot = bridgeCenter->weight_confg;
      bridgeSemC->length = bridgeCenter->length_confg;
      bridgeSemC->semN = bridgeCenter->semaphore_north_confg;
      bridgeSemC->semS = bridgeCenter->semaphore_south_confg;
      bridgeSemC->calendarizador = bridgeCenter->scheduler_confg;
      bridgeSemC->quantum = bridgeCenter->quantum_confg;


      pthread_create(&tBridgeC, NULL, &bridgeSem, bridgeSemC);
      break;
      

    case 2:

      bridgeSC->extremoS = aliens_center_south;
      bridgeSC->extremoN = aliens_center_north;
      bridgeSC->pesoTot = bridgeCenter->weight_confg;
      bridgeSC->length = bridgeCenter->length_confg;
      bridgeSC->calendarizador = bridgeCenter->scheduler_confg;
      bridgeSC->quantum = bridgeCenter->quantum_confg;


      pthread_create(&tBridgeC, NULL, &bridgeSurv, bridgeSC);
      break;

    default:
      bridgeSC->extremoS = aliens_center_south;
      bridgeSC->extremoN = aliens_center_north;
      bridgeSC->pesoTot = bridgeCenter->weight_confg;
      bridgeSC->length = bridgeCenter->length_confg;
      bridgeSC->calendarizador = bridgeCenter->scheduler_confg;
      bridgeSC->quantum = bridgeCenter->quantum_confg;

      pthread_create(&tBridgeC, NULL, &bridgeSurv, bridgeSC);
      break;
    }


  }

  init_routes(routes_a, routes_b);

  SDL_Window *win = SDL_CreateWindow("Alien's Community", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                                     SDL_WINDOW_SHOWN);
  if (win == NULL)
  {
    log_error("SDL Create Window Error");
    SDL_Quit();
    return 1;
  }

  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == NULL)
  {
    SDL_DestroyWindow(win);
    log_error("SDL Create Renderer Error");
    SDL_Quit();
    return 1;
  }

  //Load Textures & Fonts
char *bgPath = "../assets/images/map.png";
char *roadPath = "../assets/images/tile.png";
char *biroadPath = "../assets/images/tile4.png";
char *bridgePath = "../assets/images/tile3.png"; //Tile3.jpg
char *alienAPath = "../assets/images/alienA.png";
char *alienA2Path = "../assets/images/alienA2.png";
char *alienA3Path = "../assets/images/alienA3.png";
char *alienBPath = "../assets/images/alienB.png";
char *alienB2Path = "../assets/images/alienB2.png";
char *alienB3Path = "../assets/images/alienB3.png";

char *comAPath = "../assets/images/community.png";
char *comBPath = "../assets/images/community.png";
char *invaderPath = "../assets/images/invader.png";
char *fontPath = "../assets/fonts/font.ttf";
char *iconPath = "../assets/images/icon.png";

  SDL_Texture *alien_a = load_texture(alienAPath, ren);
  SDL_Texture *alien_b = load_texture(alienBPath, ren);
  SDL_Texture *alien_a_alpha = load_texture(alienA2Path, ren);
  SDL_Texture *alien_b_alpha = load_texture(alienB2Path, ren);
  SDL_Texture *alien_a_beta = load_texture(alienA3Path, ren);
  SDL_Texture *alien_b_beta = load_texture(alienB3Path, ren);
  SDL_Texture *invader_img = load_texture(invaderPath, ren);

  SDL_Texture *brigde_road = load_texture(biroadPath, ren);
  SDL_Texture *bridge = load_texture(bridgePath, ren);
  SDL_Texture *road = load_texture(roadPath, ren);
  SDL_Texture *background = load_texture(bgPath, ren);
  SDL_Texture *base_a = load_texture(comAPath, ren);
  SDL_Texture *base_b = load_texture(comBPath, ren);

  int quit = 0;

  SDL_Event e;

  SDL_Rect mouse_rect;
  SDL_Rect img_rect;
  mouse_rect.w = mouse_rect.h = 1;

  int aliens_a_size = 0;
  int aliens_b_size = 0;

  while (!quit)
  {
    aliens_a_size = llist_get_size(aliens_a);
    aliens_b_size = llist_get_size(aliens_b);

    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_QUIT)
      {
        quit = 1;
        finish = 1;
      }

      if (e.type == SDL_KEYDOWN && manual)
      {
        switch (e.key.keysym.sym)
        {
        case SDLK_a:
          spawn_alien(0, 0);
          break;

        case SDLK_s:
          spawn_alien(0, 1);
          break;

        case SDLK_d:
          spawn_alien(0, 2);
          break;

        case SDLK_b:
          spawn_alien(1, 0);
          break;

        case SDLK_n:
          spawn_alien(1, 1);
          break;

        case SDLK_m:
          spawn_alien(1, 2);
          break;

        case SDLK_x:
          spawn_invader();
          break;

        default:
          break;
        }
      }

      if ((e.type == SDL_MOUSEBUTTONDOWN) & SDL_BUTTON(SDL_BUTTON_LEFT))
      {
        printf("OK");
        SDL_GetMouseState(&mouse_rect.x, &mouse_rect.y);

        if (aliens_a_size != 0)
        {
          for (int i = 0; i < aliens_a_size; ++i)
          {
            printf("OK_A /n");
            alien *curr = llist_get_by_index(aliens_a, i);

            if (curr == NULL)
            {
              printf("INDEX OUT OF RANGE ERROR. BREAKING LOOP\n");
              break;
            }

            img_rect = get_texture_rect_wh(alien_a, curr->pos.x, curr->pos.y, 32, 32);

            if (SDL_HasIntersection(&mouse_rect, &img_rect))
            {
              printf("Quitando Alien\n");
              //lpthread_t *thread = curr->thread;
              //pthread_exit(thread->pid);
              printf("Alien Eliminado\n");

              llist_remove_by_index(aliens_a, i);
              list_a_size--;
              aliens_a_size--;
              //alien_mouse_pos=llist_get_alien_index(aliens_left_north, curr->id);
              /*
              if (alien_mouse_pos != -1)
              {
                llist_remove_by_index(aliens_left_north, alien_mouse_pos);
              }
              else{
                alien_mouse_pos = llist_get_alien_index(aliens_center_north, curr->id);
                if (alien_mouse_pos != -1)
                {
                  llist_remove_by_index(aliens_center_north, alien_mouse_pos);
                }
                else{
                  alien_mouse_pos = llist_get_alien_index(aliens_right_north, curr->id);
                  if (alien_mouse_pos != -1)
                  {
                    llist_remove_by_index(aliens_right_north, alien_mouse_pos);
                  }
                  else{
                    alien_mouse_pos = llist_get_alien_index(list_bridge_left, curr->id);
                    if (alien_mouse_pos != -1)
                    {
                      *weight_now_left -= curr->weight;
                      llist_remove_by_index(list_bridge_left, alien_mouse_pos);
                    }
                    else{
                      alien_mouse_pos = llist_get_alien_index(list_bridge_center, curr->id);
                      if (alien_mouse_pos != -1)
                      {
                        *weight_now_center -= curr->weight;
                        llist_remove_by_index(list_bridge_center, alien_mouse_pos);
                      }
                      else{
                        alien_mouse_pos = llist_get_alien_index(list_bridge_right, curr->id);
                        if (alien_mouse_pos != -1)
                        {
                          *weight_now_right -= curr->weight;
                          llist_remove_by_index(list_bridge_right, alien_mouse_pos);
                        }
                      }
                    }
                  }
                }
              }
*/
            
            }
          }
        }

        if (aliens_b_size != 0)
        {
          for (int i = 0; i < aliens_b_size; ++i)
          {
            alien *curr = llist_get_by_index(aliens_b, i);

            if (curr == NULL)
            {
              printf("INDEX OUT OF RANGE ERROR. BREAKING LOOP\n");
              break;
            }

            img_rect = get_texture_rect_wh(alien_b, curr->pos.x, curr->pos.y, 32, 32);

            if (SDL_HasIntersection(&mouse_rect, &img_rect))
            {
              //lpthread_t *thread = curr->thread;
              //pthread_exit(thread->pid);

              llist_remove_by_index(aliens_b, i);
              list_b_size--;
              aliens_b_size--;
            }
          }
        }

        if (invader_alive)
        {
          img_rect = get_texture_rect_wh(invader_img, invader->pos.x, invader->pos.y, 32, 32);

          if (SDL_HasIntersection(&mouse_rect, &img_rect))
          {
            invader_alive = 0;
            free(invader);
          }
        }
      }
    }

    SDL_RenderClear(ren);

    render_scale_texture(background, ren, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    for (int i = 0; i < Y_TILES; ++i)
    {
      for (int j = 0; j < X_TILES; ++j)
      {
        if (map[i][j] == 1)
        {
          render_scale_texture(road, ren, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }
        else if (map[i][j] == 2)
        {
          render_scale_texture(brigde_road, ren, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }
        else if (map[i][j] == 3)
        {
          render_scale_texture(bridge, ren, 15 + j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }
      }
    }

    render_scale_texture(base_a, ren, 10, 200, 170, 170);
    render_scale_texture(base_b, ren, SCREEN_WIDTH - 180, 235, 170, 170);

    aliens_a_size = llist_get_size(aliens_a);

    if (aliens_a_size != 0)
    {
      for (int i = 0; i < aliens_a_size; ++i)
      {
        alien *curr = llist_get_by_index(aliens_a, i);
        if (curr == NULL)
        {
          printf("INDEX OUT OF RANGE ERROR. BREAKING LOOP\n");
          break;
        }
        switch (curr->type)
        {
        case 0:
          render_scale_texture(alien_a, ren, curr->pos.x, curr->pos.y, ALIEN_SIZE, ALIEN_SIZE);
          break;

        case 1:
          render_scale_texture(alien_a_alpha, ren, curr->pos.x, curr->pos.y, ALIEN_SIZE, ALIEN_SIZE);
          break;

        case 2:
          render_scale_texture(alien_a_beta, ren, curr->pos.x, curr->pos.y, ALIEN_SIZE, ALIEN_SIZE);
          break;

        default:
          break;
        }
      }
    }

    aliens_b_size = llist_get_size(aliens_b);

    if (aliens_b_size != 0)
    {
      for (int i = 0; i < aliens_b_size; ++i)
      {
        alien *curr = llist_get_by_index(aliens_b, i);
        if (curr == NULL)
        {
          printf("INDEX OUT OF RANGE ERROR. BREAKING LOOP\n");
          break;
        }
        switch (curr->type)
        {
        case 0:
          render_scale_texture(alien_b, ren, curr->pos.x, curr->pos.y, ALIEN_SIZE, ALIEN_SIZE);
          break;

        case 1:
          render_scale_texture(alien_b_alpha, ren, curr->pos.x, curr->pos.y, ALIEN_SIZE, ALIEN_SIZE);
          break;

        case 2:
          render_scale_texture(alien_b_beta, ren, curr->pos.x, curr->pos.y, ALIEN_SIZE, ALIEN_SIZE);
          break;

        default:
          break;
        }
      }
    }

    if (invader_alive)
    {
      render_scale_texture(invader_img, ren, invader->pos.x, invader->pos.y, ALIEN_SIZE, ALIEN_SIZE);
    }

    SDL_RenderPresent(ren);

    SDL_Delay(16.666667 * 2);
  }

  SDL_DestroyTexture(alien_a);
  SDL_DestroyTexture(alien_b);
  SDL_DestroyTexture(brigde_road);
  SDL_DestroyTexture(bridge);
  SDL_DestroyTexture(road);
  SDL_DestroyTexture(background);
  SDL_DestroyTexture(base_a);
  SDL_DestroyTexture(base_b);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);

  quit_graphics();
  quit_cfg();

  aliens_a_size = llist_get_size(aliens_a);
  aliens_b_size = llist_get_size(aliens_b);

  /* Free Memory */
  llist_free(list_bridge_left);
  llist_free(list_bridge_center);
  llist_free(list_bridge_right);

  llist_free(aliens_left_north);
  llist_free(aliens_left_south);
  llist_free(aliens_right_north);
  llist_free(aliens_right_south);
  llist_free(aliens_center_north);
  llist_free(aliens_center_south);

  free(bridge_struct_left);
  free(bridge_struct_right);
  free(bridge_struct_center);

  free(test);

  free(weight_now_left);

  free(params_left);

  /* JOIN THREADS */
  if (aliens_a_size != 0)
  {
    for (int i = 0; i < aliens_a_size; ++i)
    {
      alien *curr = llist_get_by_index(aliens_a, i);
      if (curr == NULL)
      {
        printf("INDEX OUT OF RANGE ERROR. BREAKING LOOP\n");
        break;
      }
      pthread_join((curr->thread), NULL);
      printf("THREAD FOR ALIEN A INDEX %d JOINED\n", i);
    }
  }

  printf("ALIENS A JOINED\n");

  if (aliens_b_size != 0)
  {
    for (int i = 0; i < aliens_b_size; ++i)
    {
      alien *curr = llist_get_by_index(aliens_b, i);
      if (curr == NULL)
      {
        printf("INDEX OUT OF RANGE ERROR. BREAKING LOOP\n");
        break;
      }
      pthread_join((curr->thread), NULL);
      printf("THREAD FOR ALIEN B INDEX %d JOINED\n", i);
    }
  }

  printf("ALIENS B JOINED\n");

  pthread_join(automatic_mode, NULL);

  llist_free(aliens_a);
  llist_free(aliens_b);

  return 0;
}

int spawn_alien(int community, int type)
{
  int iret1;

  int *arg = malloc(sizeof(*arg));

  alien *entity = (alien *)malloc(sizeof(alien));
  pthread_t *thread = (pthread_t *)malloc(sizeof(pthread_t));

  entity->thread = thread;
  entity->type = type;
  gettimeofday(&entity->work_init_time, NULL);
  entity->last_update = entity->work_init_time;
  entity->progress = 0;
  entity->duration = 10;
  entity->working = 0;
  entity->accumulator = 0;
  entity->priority = type;
  entity->weight = 15;
  entity->enterBridge = 0;
  entity->crossedBridge = 0;
  entity->elapsed = NULL;

  int percentage = (rand() % (200 - 50 + 1)) + 50;
  entity->velocity = generate_alien_velocity(entity->type, velocity, percentage);

  if (community == 0)
  {
    entity->pos.x = 90;
    entity->pos.y = 180;

    *arg = list_a_size;

    llist_insert_by_index(aliens_a, entity, list_a_size);

    iret1 = pthread_create(&entity->tid, NULL, &alien_a_thread, arg);

    list_a_size++;
  }
  else if (community == 1)
  {
    entity->pos.x = 1290;
    entity->pos.y = 390;

    *arg = list_b_size;

    llist_insert_by_index(aliens_b, entity, list_b_size);

    iret1 = pthread_create(entity->thread, NULL, &alien_b_thread, arg);

    list_b_size++;
  }

  if (iret1)
  {
    fprintf(stderr, "Error - pthread_create() return code: %d\n", iret1);
    return -1;
  }

  return 0;
}

int spawn_invader(void)
{
  if (invader_alive == 0)
  {
    invader_alive = 1;
    invader = (alien *)malloc(sizeof(alien));

    pthread_create(&invader_thread_id, NULL, &invader_thread, NULL);
  }
}

int alien_a_thread(void *param)
{
  int index = *((int *)param);

  //int hola = generate_random(3, 1);
  int hola = 1;

  printf("creando alien\n");
  alien *my_alien = llist_get_by_index(aliens_a, index);
  printf("Alien en mapa\n");

  int id = my_alien->thread->pid;
  my_alien->id = id;

  for (int i = 0; i < 3; ++i)
  {
    move(&my_alien->pos, routes_a[0][i], my_alien->velocity, aliens_a, my_alien->id, 0, my_alien->crossedBridge);
  }

  /* PARTE ROSADA */
  //FIFO_scheduler(aliens_left_north, (void *)my_alien);

  for (int i = 0; i < 3; ++i)
  {
    move(&my_alien->pos, routes_a[hola][i], my_alien->velocity, aliens_a, my_alien->id, 0, my_alien->crossedBridge);
  }

  while(my_alien->enterBridge == 0);

  //printf("XAct: %f, YAct: %f\n", my_alien->pos.y, my_alien->pos.x);


  point jump;
  jump.y = my_alien->pos.y;
  jump.x = my_alien->pos.x + 30;


  move(&my_alien->pos, jump, my_alien->velocity, aliens_a, my_alien->id, 0, my_alien->crossedBridge);

  move_bridge(&my_alien->pos, &my_alien->progress, -1, my_alien->velocity, aliens_a, my_alien->id, 0, my_alien->crossedBridge);

  while(my_alien->crossedBridge == 0);

  for (int i = 0; i < 3; ++i)
  {
    move(&my_alien->pos, routes_a[hola + 3][i], my_alien->velocity, aliens_a, my_alien->id, 0, my_alien->crossedBridge);
    my_alien->crossedBridge = 0;
  }

  /* FIN PARTE ROSADA */

  for (int i = 0; i < 3; ++i)
  {
    move(&my_alien->pos, routes_a[7][i], my_alien->velocity, aliens_a, my_alien->id, 0, my_alien->crossedBridge);
  }

  //free(param);

  int curr_index = llist_get_alien_index(aliens_a, my_alien->id);

  printf("CURR INDEX = %d\n", curr_index);

  int delete = -1;
  
  for(int i = 0; i < llist_get_size(aliens_a); i++){
    alien *temp = llist_get_by_index(aliens_a, i);
    if(temp->id == my_alien->id){
      delete = i;
    }
  }

  if(delete != -1){
    llist_remove_by_index(aliens_a, delete);
  }

  list_a_size--;

  printf("Thread end\n");

  return 0;
}

int alien_b_thread(void *param)
{
  int index = *((int *)param);

  //int hola = generate_random(3, 1);

  int hola = 1;

  printf("creando alien\n");
  alien *my_alien = llist_get_by_index(aliens_b, index);
  printf("alien en el mapa\n");

  int id = my_alien->thread->pid;
  my_alien->id = id;

  for (int i = 0; i < 3; ++i)
  {
    move(&my_alien->pos, routes_b[0][i], my_alien->velocity, aliens_b, my_alien->id, 1, my_alien->crossedBridge);
  }

  for (int i = 0; i < 3; ++i)
  {
    move(&my_alien->pos, routes_b[hola][i], my_alien->velocity, aliens_b, my_alien->id, 1, my_alien->crossedBridge);
  }

  printf("Espero puente\n");

  while(my_alien->enterBridge == 0);

  point jump;
  jump.y = my_alien->pos.y;
  jump.x = my_alien->pos.x - 30;

  //printf("XAct: %f, YAct: %f, JX: %f, JY:%f", my_alien->pos.y, my_alien->pos.x, jump.x, jump.y);

  move(&my_alien->pos, jump, my_alien->velocity, aliens_b, my_alien->id, 1, my_alien->crossedBridge);

  move_bridge(&my_alien->pos, &my_alien->progress, -1, my_alien->velocity, aliens_b, my_alien->id, 1, my_alien->crossedBridge);

  while(my_alien->crossedBridge == 0);


  for (int i = 0; i < 3; ++i)
  {
    move(&my_alien->pos, routes_b[hola + 3][i], my_alien->velocity, aliens_b, my_alien->id, 1, my_alien->crossedBridge);
    my_alien->crossedBridge = 0;

  }

  for (int i = 0; i < 3; ++i)
  {
    move(&my_alien->pos, routes_b[7][i], my_alien->velocity, aliens_b, my_alien->id, 1, my_alien->crossedBridge);
  }

  //free(param);

  int curr_index = llist_get_alien_index(aliens_b, my_alien->id);

  printf("CURR INDEX = %d\n", curr_index);

  int delete = -1;
  
  for(int i = 0; i < llist_get_size(aliens_b); i++){
    alien *temp = llist_get_by_index(aliens_b, i);
    if(temp->id == my_alien->id){
      delete = i;
    }
  }

  if(delete != -1){
    llist_remove_by_index(aliens_b, delete);
  }

  list_b_size--;

  printf("Thread end\n");

  return 0;
}

int automatic_mode_thread(void *param)
{
  double lambda = *((double *)param);
  double wait = ran_expo(lambda);

  int a_probability[10];
  int b_probability[10];

  for (int i = 0; i < 10; ++i)
  {
    a_probability[i] = 0;
    b_probability[i] = 0;
  }

  printf("AUTOMATIC THREAD WAITING TIME = %f\n", wait);

  generate_probability(a_probability, b_probability, percentages);

  while (!finish)
  {
    int index_a = generate_random(9, 0);
    int index_b = generate_random(9, 0);

    printf("SPAWNED A ALIEN, TYPE = %d\n", a_probability[index_a]);
    printf("SPAWNED B ALIEN, TYPE = %d\n", b_probability[index_b]);

    spawn_alien(0, a_probability[index_a]);
    spawn_alien(1, b_probability[index_b]);

    sleep(wait);
  }

  return 0;
}

int invader_thread(void *param)
{
  int a_b = generate_random(1, 0);
  point route[8][3];

  if (a_b == 0)
  {
    memcpy(route, routes_a, sizeof(route));
    invader->pos.x = 630;
    invader->pos.y = 120;
  }
  else
  {
    memcpy(route, routes_b, sizeof(route));
    invader->pos.x = 630;
    invader->pos.y = 530;
  }

  int rand_route = generate_random(3, 1);

  for (int i = 0; i < 3; ++i)
  {
    move_invader(&invader->pos, route[rand_route][i], velocity * 2);
  }

  for (int i = 0; i < 3; ++i)
  {
    move_invader(&invader->pos, route[rand_route + 3][i], velocity * 2);
  }

  for (int i = 0; i < 3; ++i)
  {
    move_invader(&invader->pos, route[7][i], velocity * 2);
  }

  invader_alive = 0;
}