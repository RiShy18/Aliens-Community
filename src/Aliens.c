#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <util.h>
#include <graphics.h>
#include <struct.h>

//Constant values
#define  SCREEN_WIDTH  1366 //
#define  SCREEN_HEIGHT  720 //
#define  TILE_SIZE  30

 int xTiles = SCREEN_WIDTH/TILE_SIZE+1;
 int yTiles = SCREEN_HEIGHT/TILE_SIZE;

int map[24][46];
int exitProgram = 0;
int modeManual = 0; 

SDL_Event e;
SDL_Color fontColor = { 0, 0, 0, 255};

//Setup the clips for our image
SDL_Rect clips[5];

int useClip = 0;

//Load Textures & Fonts
char *bgPath = "../assets/images/bg.jpg";
char *roadPath = "../assets/images/tile2.jpg";
char *biroadPath = "../assets/images/tile4.bmp";
char *bridgePath = "../assets/images/tile4.bmp"; //Tile3.jpg
char *alienPath = "../assets/images/alien.bmp";
char *comAPath = "../assets/images/comA.jpg";
char *comBPath = "../assets/images/comB.bmp";
char *button1Path = "../assets/images/button1.bmp";
char *button2Path = "../assets/images/button2.bmp";
char *fontPath = "../assets/fonts/font.ttf";


//Functions
void handleEvents(SDL_Event e, SDL_Texture *Alien, SDL_Renderer *ren, int useClip);
void loadMap();
int configWindow();
void createAlien(int *Alien, int *ren, int x, int y, int useClip);
void createAlienA(SDL_Texture *Alien, SDL_Renderer *ren, int x, int y/*80*/,  int useClip);

int main(int args, char **argv){

  loadMap();

  //Starting SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0){
    printf("SDL_Init Error: %s\n", SDL_GetError());
    return 1;
  }

  //Starding SDL_Image
  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    printf("IMG_Init Error: %s\n", IMG_GetError());
    return 1;
  }

  //Starding SDL_TTF
  //Also need to init SDL_ttf
	if (TTF_Init() != 0){
		printf("TTF_Init Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

  //show config Window
  if(configWindow()){
    return 1;
  }


  if(modeManual){
    printf("Se selecciono el modo manual\n");
  } else if(!modeManual){
    printf("Se selecciono el modo Auto\n");
  }

  //Opening a Window
  SDL_Window *win = SDL_CreateWindow("Alien's Community", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (win == NULL){
    printf("SDL_CreateWindow Error: %s\n",SDL_GetError());
    SDL_Quit();
    return 1;
  }

  //Creating a renderer
  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (ren == NULL){
    SDL_DestroyWindow(win);
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  
  SDL_Texture *BG = loadTexture(bgPath, ren);
  SDL_Texture *BiRoad = loadTexture(biroadPath, ren);
  SDL_Texture *Bridge = loadTexture(bridgePath, ren);
  SDL_Texture *Road = loadTexture(roadPath, ren);
  SDL_Texture *Alien = loadTexture(alienPath,ren); 
  SDL_Texture *ComA = loadTexture(comAPath,ren); 
  SDL_Texture *ComB = loadTexture(comBPath,ren); 

  //Texts
  SDL_Texture *comAFont = renderText("Comunidad A", fontPath, fontColor, 25, ren);
  SDL_Texture *comBFont = renderText("Comunidad B", fontPath, fontColor, 25, ren);

  if(BG == NULL || Alien == NULL){
    printf("CreateRenderer error: %s\n", IMG_GetError());
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
  }

  int iW = 74, iH = 74;
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;

  

  //Since our clips our uniform in size we can generate a list of their
	//positions using some math (the specifics of this are covered in the lesson)
	for (int i = 0; i < 4; ++i){
		clips[i].x = 1 * iW;
		clips[i].y = i * iH ;
		clips[i].w = iW;
		clips[i].h = iH;
	}

  int animCounter = 0;
  //A sleepy rendering loop, wait for 3 seconds and render and present the screen each time
	while(!exitProgram){
    //Event Handler
    handleEvents(e, Alien, ren, useClip);

		//First clear the renderer
		SDL_RenderClear(ren);

    //Draw the background
    renderTexture(BG, ren,0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    for(int i=0;i<yTiles;i++){
      for(int j=0;j<xTiles;j++){
        if (map[i][j] == 1){
          renderTexture(Road, ren, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        } else if (map[i][j] == 2){
          renderTexture(BiRoad, ren, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        } else if (map[i][j] == 3){
          renderTexture(Bridge, ren, j * TILE_SIZE, i * TILE_SIZE, TILE_SIZE, TILE_SIZE);
        }
      }
    }

    renderTexture(ComA, ren,10, 200, 170, 170);
    renderTextureFull(comAFont,ren,15,390);
    renderTexture(ComB, ren,SCREEN_WIDTH-180, 235, 190, 170);
    renderTextureFull(comBFont,ren,SCREEN_WIDTH-180,220);

		//renderTextureSheet(Alien, ren, x, y, 80, &clips[useClip]);
    //Alien en comunidad B
    renderTextureSheet(Alien, ren, SCREEN_WIDTH-180, 400, 80, &clips[useClip]);
    renderTextureSheet(Alien, ren, 10, 100, 80, &clips[useClip]);

		//Update the screen
		SDL_RenderPresent(ren);

    SDL_Delay(17);

    animCounter += 1;
    if (animCounter == 10){
      animCounter = 0;
      useClip +=1;
      if (useClip == 4)
        useClip = 0;
    }
	}

  SDL_DestroyTexture(BG);
  SDL_DestroyTexture(Alien);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();

  return 0;
}

void handleEvents(SDL_Event e, SDL_Texture *Alien, SDL_Renderer *ren, int useClip){
  while (SDL_PollEvent(&e)){
    //If user closes the window
    if (e.type == SDL_QUIT){
      exitProgram = 1;
    }
    if (e.type == SDL_KEYDOWN){
      switch (e.key.keysym.sym){
        case SDLK_1:
          //createAlien(Alien, ren, x, y, useClip);
          useClip = 0;
          //createAlienA(Alien, ren, SCREEN_WIDTH-180, 250, useClip);
          break;
        case SDLK_2:
          useClip = 1;
          break;
        case SDLK_3:
          useClip = 2;
          break;
        case SDLK_4:
          useClip = 3;
          break;
        case SDLK_ESCAPE:
          exitProgram = 1;
          break;
        default:
          break;
      }
		}
  }
}

//int *firstClip= &clips[useClip];

void createAlienA(SDL_Texture *Alien, SDL_Renderer *ren, int x, int y/*80*/,  int useClip){
  Coordinates *Alienx;
  Alienx->Alien= Alien;
  Alienx->posx= x;
  Alienx->posy=y;
  Alienx->ren=ren;
  Alienx->type=1;
  Alienx->useClip=useClip;
  renderTextureSheet(Alienx->Alien, Alienx->ren, Alienx->posx, Alienx->posy, 80, &clips[useClip]);
}

void configHandleEvents(SDL_Event e){
  
}

void loadMap(){
  FILE * file;
  file = fopen("../assets/map/map1.map", "r");
  char ch;
  int i = 0;
  int j = 0;
  while ((ch = fgetc(file)) != EOF){
   if(ch == '\n'){
     i += 1;
     j = 0;
   } else if (ch == '-'){
     map[i][j] = 0;
     j += 1;
   } else if (ch == 'x'){
     map[i][j] = 1;
     j += 1;
   } else if (ch == 'o'){
     map[i][j] = 2;
     j += 1;
   } else if (ch == 'p'){
     map[i][j] = 3;
     j += 1;
   }
  }
}

int configWindow(){
  //Opening a Window
  SDL_Window *config = SDL_CreateWindow("Alien's Community",SCREEN_WIDTH/2-150, 200, 300, 300, SDL_WINDOW_SHOWN);
  if (config == NULL){
    printf("SDL_CreateWindow Error: %s\n",SDL_GetError());
    return 1;
  }

  //Creating a renderer
  SDL_Renderer *configRen = SDL_CreateRenderer(config, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (configRen == NULL){
    SDL_DestroyWindow(config);
    printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
    return 1;
  }
  
  SDL_Texture *BG = loadTexture(bgPath, configRen);
  SDL_Texture *Button1 = loadTexture(button1Path,configRen); 
  SDL_Texture *Button2 = loadTexture(button2Path,configRen);
  SDL_Texture *selection = renderText("Seleccione un modo", fontPath, fontColor, 25, configRen);

  SDL_Rect Button1Rect = getTextureRect(Button1,85,75);
  SDL_Rect Button2Rect = getTextureRect(Button2,85,175);
  SDL_Rect mouseRect;
  SDL_Event e;
  int mouseX, mouseY;
  int exitWin = 0;
  while(!exitWin){
    while (SDL_PollEvent(&e)){
      //If user closes the window
      if (e.type == SDL_QUIT){
        exitProgram = 1;
        exitWin = 1;
      }
      if ((e.type == SDL_MOUSEBUTTONDOWN) & SDL_BUTTON(SDL_BUTTON_LEFT)){
        SDL_GetMouseState(&mouseX,&mouseY);
        mouseRect.x = mouseX; mouseRect.y = mouseY; mouseRect.w = mouseRect.h = 1;
        if(SDL_HasIntersection(&mouseRect,&Button1Rect)){
          modeManual = 1;
          exitWin = 1;
        } else if(SDL_HasIntersection(&mouseRect,&Button2Rect)){
          modeManual = 0;
          exitWin = 1;
        }
      }
    }
    renderTexture(BG,configRen,0,0,300,300);
    renderTextureFull(Button1,configRen,85,75);
    renderTextureFull(Button2,configRen,85,175);
    renderTextureFull(selection,configRen,35,25);

    //Update the screen
		SDL_RenderPresent(configRen); 
    SDL_Delay(250);
  }

  SDL_DestroyWindow(config);
  SDL_DestroyRenderer(configRen);


  exitProgram = 0;
  return 0;
}