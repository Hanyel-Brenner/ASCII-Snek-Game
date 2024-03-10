#include "snake.h"
#include <time.h>
#include <windows.h>
#include <stdlib.h>

//game functions
//int isGameOver(Snake,Frame);

//returns number of milliseconds between start of program (time1) and the current time (time2), replicating clock() but in milliseconds;
double _clock(time_t time1,time_t time2)
{
  return difftime(time1,time2)*1000;  
}
//returns x and y value where food should spawn.
struct coord getFoodCoordinate(Frame frame)
{
  struct coord pos;
  pos.x = rand()%(frame->width - 6);
  pos.y = rand()%(frame->height - 4);
  if(pos.x < 2) pos.x++;
  if(pos.y < 2) pos.y++;
  return pos;
}

int checkOutOfBounds(Snake snake, Frame frame){
  if(snake->pos[0].x < 2 || snake->pos[0].x > frame->width - 3) return 1; //returning 1 means that the snake is out of the bounds of frame and therefore game over
  if(snake->pos[0].y < 1 || snake->pos[0].y > frame->height - 2 ) return 1;
  return 0;
}

int checkSelfColision(Snake snake){
  for(int i = 1; i < snake->length; i++){
    if(snake->pos[0].x == snake->pos[i].x && snake->pos[0].y == snake->pos[i].y) return 2;
  }
  return 0;
}

int checkFoodColision(Snake snake,Food foodMap){
  int x = snake->pos[0].x;
  int y = snake->pos[0].y;

  if(foodMap->array[y][x] == 'Q') return 1;

  return 0;

}


int main(void) {
  srand((unsigned int) time(NULL));
  int score = 0;
  int isGameOver = 0;
  int xdir = 1, ydir = 0;
  short aPressed = 0,sPressed = 0,dPressed = 0,wPressed = 0; //boolean values to verify if each of the keys is pressed or not;
  int frameWidth = 30, frameHeight = 15;
  int foodOnScreenCounter = 0;
  struct coord foodToInsert;

  time_t  programInception = time(NULL);
  double currentTime,oldTime, generateFoodTime;; //timers for the frame to be printed
  double kbTimeAccumulator_A, kbTimeAccumulator_S, kbTimeAccumulator_D, kbTimeAccumulator_W;
  Frame frame = createFrame(frameWidth,frameHeight);
  Snake snake = createSnake(15,7);
  Food foodMap = createFoodMap(frameWidth,frameHeight);
  initiateFoodMap(foodMap);
  
  currentTime = _clock(time(NULL),programInception);
  oldTime = currentTime;
  generateFoodTime = currentTime;
  kbTimeAccumulator_A = currentTime;
  kbTimeAccumulator_S = currentTime;
  kbTimeAccumulator_D = currentTime;
  kbTimeAccumulator_W = currentTime;

  printf("+-----SNEK GAME-----+ \nPress enter to start... ");
  char a; 
  scanf("%c", &a);

  while(!isGameOver){
    
    if(currentTime - oldTime > 50){
      system("cls");
      initiateFrame(frame);
      setFrameBorders(frame);

      if(currentTime - generateFoodTime > 2000 && foodOnScreenCounter < FOOD_ON_SCREEN_MAX){
        foodToInsert = getFoodCoordinate(frame);
        foodOnScreenCounter++;
        foodMap->array[foodToInsert.y][foodToInsert.x] = SNAKE_FOOD;
        generateFoodTime = currentTime;
      }

      moveHeadTo(snake,snake->pos[0].x + xdir, snake->pos[0].y + ydir);
      mapFoodToFrame(foodMap,frame);
      setSnakeBodyOnFrame(snake,frame);

      printf("SCORE : %d\n",score);
      printFrame(frame);
      printf("ELAPSED TIME : %.0lf",currentTime/1000);

      if(!isGameOver) isGameOver = checkOutOfBounds(snake,frame);
      if(!isGameOver) isGameOver = checkSelfColision(snake);
      if(checkFoodColision(snake,foodMap)){
        growSnake(snake,xdir,ydir);
        foodOnScreenCounter - 1;
        score++;
      }

      oldTime = currentTime;
      
    }

    if(GetAsyncKeyState('A') && aPressed == 0 )
    {
      aPressed = 1;
      xdir = -1;
      ydir = 0;
      kbTimeAccumulator_A = currentTime; //after that we start counting until we can again verify if key is pressed
    }

    if(aPressed == 1 && currentTime - kbTimeAccumulator_A > 50 )
    {
        aPressed = 0;
    }

    if(GetAsyncKeyState('S') && sPressed == 0 )
    {
      sPressed = 1;
      xdir = 0;
      ydir = 1;
      kbTimeAccumulator_S = currentTime; //after that we start counting until we can again verify if key is pressed
    }

    if(sPressed == 1 && currentTime - kbTimeAccumulator_S > 50 )
    {
        sPressed = 0;
    }

    if(GetAsyncKeyState('D') && dPressed == 0 )
    {
      dPressed = 1;
      xdir = 1;
      ydir = 0;
      kbTimeAccumulator_D = currentTime; //after that we start counting until we can again verify if key is pressed
    }

    if(dPressed == 1 && currentTime - kbTimeAccumulator_D > 50 )
    {
        dPressed = 0;
    }

    if(GetAsyncKeyState('W') && wPressed == 0 )
    {
      wPressed = 1;
      xdir = 0;
      ydir = -1;
      kbTimeAccumulator_W = currentTime; //after that we start counting until we can again verify if key is pressed
    }

    if(wPressed == 1 && currentTime - kbTimeAccumulator_W > 50 )
    {
        wPressed = 0;
    }

    currentTime = _clock(time(NULL),programInception);


  }
    printf("\n\n\n");
    if(isGameOver == 1) printf("\nCareful where you step, friend...\n");
    if(isGameOver == 2) printf("\nYou are biting the wrong stuff...\n");
    printf("Game is Over. Press any key to close window...");
    printf("\n\n\nv1.0 | Designed by Hanyel Brenner | 2024");
    getchar();

    return 0;
}



