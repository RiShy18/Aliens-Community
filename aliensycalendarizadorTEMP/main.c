#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "include/llist.h"
#include "include/Alien.h"

struct argsGen
{
    llist *mylist;
    double interval;
    int total;
    int velocidad;
    pthread_mutex_t *lockColonia;
    int generating;
    int ready;
    int cantExtremos;
};


struct argsPrint
{
    llist *mylist;
    pthread_mutex_t *lockColonia;
    int numColonia;
};

struct argsCalenPrior
{
    llist *colonia;
    llist *extremo;
    pthread_mutex_t *lockColonia;
    pthread_mutex_t *lockExtremo;
    int total;
    int *generating;
    int *ready;
    int cantExtremos;
};

struct argsBridgeY
{
    llist *extremoN;
    llist *extremoS;
    pthread_mutex_t *lockExtremoN;
    pthread_mutex_t *lockExtremoS;
    int Y;
    int lenBr;
    int pesoSoport;
    int generatingN;
    int generatingS;
};

struct alienCruzando{
    pthread_t tid;
    struct Alien *alien;
    int pos;
    int indice;

};

void numprint(void *);

double ran_expo(double lambda){
    double u;
    u = rand() / (RAND_MAX + 1.0);
    return -log(1- u) / lambda;
}

void *alienGen(void *arguments){
    struct argsGen * args = (struct argsGen *) arguments;

    printf("Empieza Generacion\n");


    int count = 0;
    double vPorcent = args->velocidad * 0.2;
    
    while(count < args->total){
        srand(time(0));
        struct Alien *alien = (struct Alien*) malloc(sizeof(struct Alien));
        alien->peso = (rand() % (10 - 1 + 1)) + 1;;
        alien->tipo = (rand() % (2 - 0 + 1)) + 0;
        alien->velocidad = args->velocidad;
        alien->prioridad = (rand() % (10 - 1 + 1)) + 1;
        if(alien->tipo == 1){
            alien->velocidad = alien->velocidad + vPorcent;
        }
        else if(alien->tipo == 2){
            alien->velocidad = 2 * alien->velocidad;
            alien->prioridad = 10;
        }
        pthread_mutex_lock(args->lockColonia); 
        addLast(args->mylist, alien);
        //printf("Hice un Alien %f\n", args->interval);
        if(getSize(args->mylist) == args->cantExtremos){
            args->ready = 1;
        }
        pthread_mutex_unlock(args->lockColonia); 
        sleep(args->interval);
        count++;
    }
    args->generating = 0;
}

void *printAliens(void *arguments){
    llist *mylist = ((struct argsPrint *)arguments)->mylist;
    pthread_mutex_t *lockColonia = ((struct argsPrint *)arguments)->lockColonia;
    int numColonia = ((struct argsPrint *)arguments)->numColonia;
    while(1){
        pthread_mutex_lock(lockColonia);
        printf("Aliens en colonia %d\n", numColonia); 
        print(mylist, numprint);
        pthread_mutex_unlock(lockColonia); 
        sleep(1);
    }

}

void *calen_prioridad(void *arguments){
    printf("Empieza el calndarizador\n");
    struct argsCalenPrior * args = (struct argsCalenPrior *)arguments;
    int count = 0;
    int size = 0;
    while(1){
        //printf("Generating: %d\n",*args->generating);
        //printf("Ready: %d\n", *args->ready);
        pthread_mutex_lock(args->lockColonia);
        size = getSize(args->colonia);
        if(*args->generating == 0 && size == 0){
            pthread_mutex_unlock(args->lockColonia);
            break;
        }
        //printf("size: %d\n", size);
        if(*args->ready == 1 && getSize(args->extremo) < args->cantExtremos){
            //printf("Entra al if\n");
            int index = 0;
            struct Alien *prior = (struct Alien *) malloc(sizeof(struct Alien));
            prior->prioridad = -1;
            for(int i = 0; i < size; i++){
                struct Alien *data = (struct Alien *) getbyId(args->colonia,i);
                if(prior->prioridad < data->prioridad){
                    prior->peso = data->peso;
                    prior->prioridad = data->prioridad;
                    prior->tipo = data->tipo;
                    prior->velocidad = data->velocidad;
                    index = i;
                }
            }
            if(prior->prioridad != -1){
                addLast(args->extremo, prior);
                //printf("Hace Delete index = %d el size es %d\n", index, size);
                delById(args->colonia, index);
                pthread_mutex_unlock(args->lockColonia);
                count++;
            }
        }else{
            pthread_mutex_unlock(args->lockColonia);
            //printf("Sali del unlock\n");
        }
    }
}

void *alienThr(void *arguments){
    
}

void *bridgeY(void *arguments){
    struct argsBridgeY *args = (struct argsBridgeY *) arguments;
    llist *aliensEnPuente = create(NULL);
    int sentido = 0;
    int pesoEnmomento = 0;
    int aliensTotal = 0;
    int aliensPasados = 0;
    llist *extremoTrab;
    pthread_mutex_t *lockExtremo;
    pthread_mutex_t lockAliensPuente;

    pthread_mutex_init(&lockAliensPuente, NULL); 
    while(1){
        printf("sentido: %d, pesoEnmomento: %d, AliensTotal: %d, AliensPasados: %d\n", sentido, pesoEnmomento, aliensTotal, aliensPasados);
        if(aliensTotal > args->Y && aliensTotal == 0){
            aliensTotal = 0;
            if(sentido == 0){
                sentido = 1;
            }else{
                sentido = 0;
            }
        }
        if(sentido == 0){
            extremoTrab = args->extremoN;
            lockExtremo = args->lockExtremoN;
        }else{
            extremoTrab = args->extremoS;
            lockExtremo = args->lockExtremoS;
        }
        pthread_mutex_lock(lockExtremo);
        if(getSize(extremoTrab) > 0){
            struct Alien *alienAct = (struct Alien *) getbyId(extremoTrab, 0);
            if((pesoEnmomento + alienAct->peso) <= args->pesoSoport){
                struct alienCruzando *alientTemp = (struct alienCruzando *) malloc(sizeof(struct alienCruzando));
                pthread_t tid;
                pesoEnmomento = pesoEnmomento + alienAct->peso;
                alientTemp->alien = alienAct;
                alientTemp->indice = aliensPasados;
                alientTemp->pos = 0;
                printf("Aqui deberia generar un thread \n");
                numprint(alientTemp->alien);
                //pthread_create(&alientTemp->tid, NULL, alienThr, (void *)alientTemp);
                aliensPasados++;
                aliensTotal++;
                delById(extremoTrab, 0);
            }
        }
        pthread_mutex_unlock(lockExtremo);
        if(args->generatingN == 0  && args->generatingS == 0 && getSize(args->extremoN) == 0 && getSize(args->extremoS) == 0){
            break;
        }
        sleep(1);
    }
    pthread_mutexattr_destroy(&lockAliensPuente);
}

int main(){/*
    llist *colonia1 = create(NULL);

    struct Alien * alien = (struct Alien *) malloc(sizeof(struct Alien));

    alien->peso = 1;
    alien->prioridad = 1;
    alien->tipo = 1;
    alien->velocidad = 1;

    struct Alien * alien2 = (struct Alien *) malloc(sizeof(struct Alien));

    alien2->peso = 2;
    alien2->prioridad = 2;
    alien2->tipo = 2;
    alien2->velocidad = 2;

    addLast(colonia1,alien);

    addLast(colonia1,alien2);

    struct Alien* alienGet = (struct Alien *) getbyId(colonia1, 0);

    delById(colonia1, 0);

    printf("Colonia :\n");
    print(colonia1, numprint);

    printf("Alien suelto: \n");
    numprint(alienGet);*/


    pthread_mutex_t lockColonia1, lockColonia2, lockExtremoN, lockExtremoS;


    pthread_mutex_init(&lockColonia1, NULL); 
    pthread_mutex_init(&lockColonia2, NULL); 

    pthread_mutex_init(&lockExtremoN, NULL); 
    pthread_mutex_init(&lockExtremoS, NULL); 

    srand((unsigned)time(NULL));
    double sleep_time = ran_expo(0.5);
    llist *colonia1 = create(NULL);

    llist *colonia2 = create(NULL);

    llist *extremoN = create(NULL);

    llist *extremoS = create(NULL);

    printf("Tiempo para creacion de Alien en Colonia1 %f\n", sleep_time);


    struct argsGen *Params = (struct argsGen*) malloc(sizeof(struct argsGen));

    Params->interval = sleep_time;
    Params->mylist = colonia1;
    Params->total = 6;
    Params->velocidad = 5;
    Params->lockColonia = &lockColonia1;
    Params->generating = 1;
    Params->ready = 0;
    Params->cantExtremos = 5;

    struct argsPrint *ParamsPrint = (struct argsPrint*) malloc(sizeof(struct argsPrint));
    ParamsPrint->mylist = colonia1;
    ParamsPrint->lockColonia = &lockColonia1;
    ParamsPrint->numColonia = 1;


    sleep_time = ran_expo(0.5);
    printf("Tiempo para creacion de Alien en Colonia2 %f\n", sleep_time);
    struct argsGen *Params2 = (struct argsGen*) malloc(sizeof(struct argsGen));

    Params2->interval = sleep_time;
    Params2->mylist = colonia2;
    Params2->total = 6;
    Params2->velocidad = 5;
    Params2->lockColonia = &lockColonia2;
    Params2->generating = 1;
    Params2->ready = 0;
    Params2->cantExtremos = 5;

    struct argsPrint *ParamsPrint2 = (struct argsPrint*) malloc(sizeof(struct argsPrint));
    ParamsPrint2->mylist = colonia2;
    ParamsPrint2->lockColonia = &lockColonia2;
    ParamsPrint2->numColonia = 2;

    struct argsCalenPrior *ParamsCalenN = (struct argsCalenPrior*) malloc(sizeof(struct argsCalenPrior));
    ParamsCalenN->colonia = colonia1;
    ParamsCalenN->extremo = extremoN;
    ParamsCalenN->lockColonia = &lockColonia1;
    ParamsCalenN->lockExtremo = &lockExtremoN;
    ParamsCalenN->total = 5;
    ParamsCalenN->generating = &Params->generating;
    ParamsCalenN->ready = &Params->ready;
    ParamsCalenN->cantExtremos = 5;

    struct argsCalenPrior *ParamsCalenN2 = (struct argsCalenPrior*) malloc(sizeof(struct argsCalenPrior));
    ParamsCalenN2->colonia = colonia2;
    ParamsCalenN2->extremo = extremoS;
    ParamsCalenN2->lockColonia = &lockColonia2;
    ParamsCalenN2->lockExtremo = &lockExtremoS;
    ParamsCalenN2->total = 5;
    ParamsCalenN2->generating = &Params2->generating;
    ParamsCalenN2->ready = &Params2->ready;
    ParamsCalenN2->cantExtremos = 5;

    struct argsBridgeY *bridge1 = (struct argsBridgeY *) malloc(sizeof(struct argsBridgeY));


    bridge1->extremoN = extremoN;
    bridge1->extremoS = extremoS;
    bridge1->generatingN = Params->generating;
    bridge1->generatingS = Params2->generating;
    bridge1->lenBr = 100;
    bridge1->lockExtremoN = &lockExtremoN;
    bridge1->lockExtremoS = &lockExtremoS;
    bridge1->pesoSoport = 15;
    bridge1->Y = 3;


    pthread_t tid1, tid2, tid3, tid4, tid5;

    pthread_create(&tid1, NULL, alienGen, (void *)Params);
    
    pthread_create(&tid2, NULL, alienGen, (void *)Params2);

    pthread_create(&tid3, NULL, calen_prioridad, (void *)ParamsCalenN);

    pthread_create(&tid4, NULL, calen_prioridad, (void *)ParamsCalenN2);

    pthread_create(&tid5, NULL, bridgeY, (void *)bridge1);


    //pthread_create(&tid3, NULL, printAliens, (void *)ParamsPrint);
    //pthread_create(&tid4, NULL, printAliens, (void *)ParamsPrint2);

    pthread_join(tid1, NULL);

    pthread_join(tid2, NULL);

    pthread_join(tid3, NULL);

    pthread_join(tid4, NULL);


    //pthread_cancel(tid3);

    //pthread_join(tid2, NULL);

    printf("Gen: %d\n", Params->generating);

    //pthread_cancel(tid4);

    printf("Aliens en colonia #1\n");
    print(colonia1, numprint);
    
    printf("Aliens calend en extremo1\n");
    print(extremoN, numprint);
    
    printf("Aliens en colonia #2\n");
    print(colonia2, numprint);

    printf("Aliens calend en extremo2\n");
    print(extremoS, numprint);

    pthread_join(tid5, NULL);

    //lfree(colonia1);
    //lfree(colonia2);
    pthread_mutex_destroy(&lockColonia1); 
    pthread_mutex_destroy(&lockColonia2);

    pthread_mutex_destroy(&lockExtremoN); 
    pthread_mutex_destroy(&lockExtremoS);

    return 0;
}

void numprint(void *num){
    struct Alien *pnum = (struct Alien *)num;
    if(num == NULL){
        return;
    }
    printf("Velocidad: %f, Tipo: %d, Peso: %d, Prioridad: %d\n", pnum->velocidad, pnum->tipo, pnum->peso, pnum->prioridad);
}