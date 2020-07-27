#include <structs.h>
#include <list.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int calendarizadorA(void *comunidad){
  argsCalen *args = (argsCalen *) comunidad;
  llist *list = args->comunidadA;
  llist* aliens_left_north = args->aliens_left_north;
  llist* aliens_right_north = args->aliens_right_north;
  llist* aliens_center_north = args->aliens_center_north;
  while(1){
    //printf("Calendarizador activo\n");
    //printf("Size colonia: %d\n", llist_get_size(list));
    if(llist_get_size(list) >= 1){
      for(int i = 0; i < llist_get_size(list); i++){
        alien *actual = (alien *) llist_get_by_index(list, i);
        //printf("Posiciones x: %f y:%f\n", actual->pos.x, actual->pos.y);
        if((actual->pos.x >= 325 && actual->pos.x <= 360) && (227 <= actual->pos.y && actual->pos.y <= 285)){
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
        if((actual->pos.x >= 980 && actual->pos.x <= 1020) && (227 <= actual->pos.y && actual->pos.y <= 285)){
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
        if((actual->pos.x >= 655 && actual->pos.x <= 695) && (227 <= actual->pos.y && actual->pos.y <= 285)){
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
  argsCalen *args = (argsCalen *) comunidad;
  llist *list = args->comunidadB;
  llist* aliens_left_south = args->aliens_left_south;
  llist* aliens_right_south = args->aliens_right_south;
  llist* aliens_center_south = args->aliens_center_south;
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