#include "frame.h"

static int SNAKE_MAX_LENGTH = 200;
static char SNAKE_BODY_CHAR = 'o';
static char NO_FOOD_CHAR = '-';
static char SNAKE_FOOD = 'Q';
static int FOOD_ON_SCREEN_MAX = 50;

struct snake{
  struct coord *pos;
  int length;
};

struct coord{
  int x;
  int y;
};

typedef struct snake *Snake;
typedef struct frame *Food;

//create snake of length 2 and set initial position (x,y) on a future frame
Snake createSnake(int x,int y){
  Snake snake = (Snake)malloc(sizeof(struct snake));  
    snake->pos = (struct coord *)malloc(SNAKE_MAX_LENGTH * sizeof(struct coord));
    snake->length = 2;
    snake->pos[0].x = x;
    snake->pos[0].y = y;
    snake->pos[1].x = x - 1;
    snake->pos[1].y = y;

    return snake;
}

Food createFoodMap(int width,int height)
{
  Food foodMap = (Food)malloc(sizeof(struct frame));
  foodMap->height = height;
  foodMap->width = width;
  foodMap->array = (char **)malloc(height * sizeof(char *));
  for(int i = 0; i<foodMap->height; i++){
    foodMap->array[i] = (char *)malloc(width * sizeof(char)); 
  }  
  return foodMap;
}

void initiateFoodMap(Food foodMap){
  for(int i = 0; i<foodMap->height; i++){
    for(int j = 0; j<foodMap->width; j++){
      foodMap->array[i][j] = NO_FOOD_CHAR;
    }
  }
}

//moves head to a location and accordingly moves the rest of the snake body to accompany the movement
int moveHeadTo(Snake snake,int x,int y){
  
    for(int i = snake->length - 1; i >= 1; i--)
    {
      snake->pos[i].x = snake->pos[i - 1].x;
      snake->pos[i].y = snake->pos[i - 1].y;
    }
    snake->pos[0].x = x;
    snake->pos[0].y = y;
}

int growSnake(Snake snake,int xdir, int ydir){
  
  int length = snake->length;
  int lastx = snake->pos[length - 1].x;
  int lasty = snake->pos[length - 1].y;
  int frontx = snake->pos[length - 2].x;
  int fronty = snake->pos[length - 2].y;
  int newx,newy;


  if(frontx - lastx == 0){
    newx = lastx;
    if(fronty - lasty == 1){
      newy = lasty - 1;
    }
    else{ newy = lasty + 1;}


  }else{
    newy = lasty;
    if(frontx - lastx == 1){
      newx = lastx - 1;
    }
    else{newx = lastx + 1;}
  }

  snake->pos[length].x = newx;
  snake->pos[length].y = newy;

snake->length++;

return 1;
  
}

//this function expects the frame to be already initiated and have frame borders set
void setSnakeBodyOnFrame(Snake snake, Frame frame){
  int x,y;
  
  for(int snakeBlock = 0; snakeBlock < snake->length ; snakeBlock ++)
  {
      x = snake->pos[snakeBlock].x;
      y = snake->pos[snakeBlock].y;
      frame->array[y][x] = SNAKE_BODY_CHAR;
  }

}

void mapFoodToFrame(Food foodMap, Frame frame)
{
  for(int i=0; i<foodMap->height; i++){
    for(int j=0; j<foodMap->width; j++){
      if(foodMap->array[i][j] == SNAKE_FOOD){
        frame->array[i][j] = SNAKE_FOOD;
      }
    }
  }
}

  
