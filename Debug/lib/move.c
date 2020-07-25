#include <math.h>
#include <structs.h>
#include <unistd.h>
#include <stdio.h>
#include <list.h>
#include <SDL2/SDL.h>
#include <lpthread.h>
#include <utilities.h>

int stop_move(point *actual, point dest, float dist_x, float dist_y)
{
  int cond_x, cond_y;

  if (dist_x > 0)
    cond_x = actual->x >= dest.x;
  else if (dist_x < 0)
    cond_x = actual->x <= dest.x;
  else
    cond_x = actual->x == dest.x;

  if (dist_y > 0)
    cond_y = actual->y >= dest.y;
  else if (dist_y < 0)
    cond_y = actual->y <= dest.y;
  else
    cond_y = actual->y == dest.y;

  return cond_x && cond_y;
}

void move(point *actual, point dest, float speed, llist *list, int index, int community)
{
  float dist_x = dest.x - actual->x;
  float dist_y = dest.y - actual->y;

  float norm = sqrt(pow(dist_x, 2) + pow(dist_y, 2));

  dist_x /= norm;
  dist_y /= norm;

  int moving = 1;

  float tmp_x, tmp_y;

  SDL_Rect myself, other;

  int square;

  if (community == 0)
  {
    square = 28;
  }
  else if (community == 1)
  {
    square = 20;
  }

  myself.h = square;
  myself.w = square;

  other.h = square;
  other.w = square;

  int intersection = 0;
  int size = 0;

  while (moving)
  {
    tmp_x = actual->x + dist_x * speed;
    tmp_y = actual->y + dist_y * speed;

    myself.x = tmp_x;
    myself.y = tmp_y;

    //Lmutex_lock(lock);
    size = llist_get_size(list);
    //Lmutex_unlock(lock);

    for (int i = 0; i < size; ++i)
    {
      //Lmutex_lock(lock);
      alien *curr = llist_get_by_index(list, i);
      //Lmutex_unlock(lock);

      if (curr == NULL)
      {
        printf("INDEX OUT OF RANGE ERROR. BREAKING LOOP\n");
        break;
      }

      if (index != curr->id)
      {
        other.x = curr->pos.x;
        other.y = curr->pos.y;

        if (SDL_HasIntersection(&myself, &other))
        {
          intersection = 1;
        }
      }

      //Lmutex_lock(lock);
      size = llist_get_size(list);
      //Lmutex_unlock(lock);
    }

    if (!intersection)
    {
      actual->x += dist_x * speed;
      actual->y += dist_y * speed;
    }

    intersection = 0;

    if (stop_move(actual, dest, dist_x, dist_y))
    {
      moving = 0;
    }

    usleep(16666 * 2);
  }

  actual->x = ceil(actual->x);
  actual->y = ceil(actual->y);
}

void move_bridge(point *actual, float *progress, int direcction)
{
  float init_pos_y = actual->y;
  int bridge_height = 120;

  while (*progress < 1)
  {
    actual->y = (bridge_height * (*progress)) * direcction + init_pos_y;

    usleep(16666);
  }
}

void move_invader(point *actual, point dest, float speed)
{
  float dist_x = dest.x - actual->x;
  float dist_y = dest.y - actual->y;

  float norm = sqrt(pow(dist_x, 2) + pow(dist_y, 2));

  dist_x /= norm;
  dist_y /= norm;

  int moving = 1;

  while (moving)
  {
    actual->x += dist_x * speed;
    actual->y += dist_y * speed;

    if (stop_move(actual, dest, dist_x, dist_y))
    {
      moving = 0;
    }

    usleep(16666 * 2);
  }

  actual->x = ceil(actual->x);
  actual->y = ceil(actual->y);
}

float generate_alien_speed(int type, int base_speed, int percentage)
{
  float result = 1;

  switch (type)
  {
  case 0:
    result = base_speed;
    break;

  case 1:
    result = base_speed + (base_speed * 0.2);
    break;

  case 2:
    result = base_speed + base_speed * (percentage / 100);
    break;

  default:
    break;
  }

  return result;
}

void init_routes(point routes_a[8][3], point routes_b[8][3])
{
  /* Community A to Init Pink */
  routes_a[0][0].x = 90;
  routes_a[0][0].y = 60;

  routes_a[0][1].x = 630;
  routes_a[0][1].y = 60;

  routes_a[0][2].x = 630;
  routes_a[0][2].y = 120;

  /* Left A Init Pink to Bridge Init */
  routes_a[1][0].x = 330;
  routes_a[1][0].y = 120;

  routes_a[1][1].x = 330;
  routes_a[1][1].y = 240;

  routes_a[1][2].x = 330;
  routes_a[1][2].y = 270;

  /* Left A End Bridge to End Pink */
  routes_a[4][0].x = 330;
  routes_a[4][0].y = 530;

  routes_a[4][1].x = 630;
  routes_a[4][1].y = 530;

  routes_a[4][2].x = 690;
  routes_a[4][2].y = 530;

  /* Right A Init Pink to Bridge Init  A */
  routes_a[2][0].x = 660;
  routes_a[2][0].y = 150;

  routes_a[2][1].x = 990;
  routes_a[2][1].y = 150;

  routes_a[2][2].x = 990;
  routes_a[2][2].y = 270;

  /* Right A Bridge End to Pink End */
  routes_a[5][0].x = 990;
  routes_a[5][0].y = 510;

  routes_a[5][1].x = 730;
  routes_a[5][1].y = 510;

  routes_a[5][2].x = 690;
  routes_a[5][2].y = 530;

  /* Center A Init Pink to Bridge Init */
  routes_a[3][0].x = 660;
  routes_a[3][0].y = 150;

  routes_a[3][1].x = 660;
  routes_a[3][1].y = 240;

  routes_a[3][2].x = 660;
  routes_a[3][2].y = 270;

  /* Center A End Bridge to Pink End */
  routes_a[6][0].x = 660;
  routes_a[6][0].y = 420;

  routes_a[6][1].x = 660;
  routes_a[6][1].y = 500;

  routes_a[6][2].x = 690;
  routes_a[6][2].y = 530;

  /* End Pink to Community A */
  routes_a[7][0].x = 690;
  routes_a[7][0].y = 630;

  routes_a[7][1].x = 1230;
  routes_a[7][1].y = 630;

  routes_a[7][2].x = 1230;
  routes_a[7][2].y = 390;

  /* Community B to Pink */
  routes_b[0][0].x = 1290;
  routes_b[0][0].y = 680;

  routes_b[0][1].x = 630;
  routes_b[0][1].y = 680;

  routes_b[0][2].x = 630;
  routes_b[0][2].y = 530;

  /* Left B Init Pink to Init Bridge */
  routes_b[1][0].x = 600;
  routes_b[1][0].y = 500;

  routes_b[1][1].x = 360;
  routes_b[1][1].y = 500;

  routes_b[1][2].x = 360;
  routes_b[1][2].y = 390;

  /* Left B End Bridge to End Pink */
  routes_b[4][0].x = 360;
  routes_b[4][0].y = 150;

  routes_b[4][1].x = 660;
  routes_b[4][1].y = 150;

  routes_b[4][2].x = 690;
  routes_b[4][2].y = 120;

  /* Right B Init Pink to Init Pink */
  routes_b[2][0].x = 1020;
  routes_b[2][0].y = 530;

  routes_b[2][1].x = 1020;
  routes_b[2][1].y = 420;

  routes_b[2][2].x = 1020;
  routes_b[2][2].y = 390;

  /* Right B End Bridge to End Pink */
  routes_b[5][0].x = 1020;
  routes_b[5][0].y = 120;

  routes_b[5][1].x = 720;
  routes_b[5][1].y = 120;

  routes_b[5][2].x = 690;
  routes_b[5][2].y = 120;

  /* Center B Init Pink to Init Bridge */
  routes_b[3][0].x = 690;
  routes_b[3][0].y = 500;

  routes_b[3][1].x = 690;
  routes_b[3][1].y = 420;

  routes_b[3][2].x = 690;
  routes_b[3][2].y = 390;

  /* Center B End Pink to End Bridge */
  routes_b[6][0].x = 690;
  routes_b[6][0].y = 240;

  routes_b[6][1].x = 690;
  routes_b[6][1].y = 210;

  routes_b[6][2].x = 690;
  routes_b[6][2].y = 120;

  /* Pink End to Community B*/
  routes_b[7][0].x = 690;
  routes_b[7][0].y = 0;

  routes_b[7][1].x = 30;
  routes_b[7][1].y = 0;

  routes_b[7][2].x = 30;
  routes_b[7][2].y = 180;
}