#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct Coordinates{
int posx;
int posy;
SDL_Texture *Alien;
int useClip;
SDL_Renderer *ren;
int type;
} Coordinates;