#ifndef MOVE_H
#define MOVE_H

void move(point *actual, point dest, float speed, llist *list, int index, int community);
int stop_move(point *actual, point dest, float dist_x, float dist_y);
void init_routes(point routes_a[8][3], point routes_b[8][3]);
void move_bridge(point *actual, float *progress, int direcction);
float generate_alien_speed(int type, int base_speed, int percentage);
void move_invader(point *actual, point dest, float speed);

#endif