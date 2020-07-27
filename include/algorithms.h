#ifndef _ALGORITHMS_H
#define _ALGORITHMS_H

//Algoritmos de Calendarización y puentes
int calendarizadorA(void *comunidad);
int calendarizadorB(void *comunidad);
alien *calen_prioridad(llist *extremo);
alien *calen_FIFO(llist *extremo);
alien *calen_mascorto(llist *extremo, int bLength);
alien *calen_lotterry(llist *extremo);
alien *calen_RR(llist *extremo);
void *bridgeY(void *arguments);
void *bridgeSurv(void *arguments);
void *bridgeSem(void *arguments);

#endif