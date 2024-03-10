#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 50
#define WIDTH 50
static char BACKGROUND_CHAR = ' ';
static char BORDER_CHAR = '|';

struct frame {
  int height;
  int width;
  char **array;
};

typedef struct frame *Frame;

Frame createFrame(int height, int width);
void initiateFrame(Frame frame);
void setFrameBorders(Frame frame);
void printFrame(Frame frame);

