#include "frame.h"

Frame createFrame(int width, int height) {
  Frame MyFrame = (Frame)malloc(sizeof(struct frame));
  MyFrame->height = height;
  MyFrame->width = width;
  MyFrame->array = (char **)malloc(height * sizeof(char *));
  for(int i = 0; i<MyFrame->height; i++){
    MyFrame->array[i] = (char *)malloc(width * sizeof(char)); 
  }  
  return MyFrame;
}

void initiateFrame(Frame frame){
  for(int i = 0; i<frame->height; i++){
    for(int j = 0; j<frame->width; j++){
      frame->array[i][j] = BACKGROUND_CHAR;
    }
  }
}

void setFrameBorders(Frame frame){
  for(int i=0; i<frame->height; i++){
    frame->array[i][0] = BORDER_CHAR;
    frame->array[i][1] = BORDER_CHAR;
  }
  for(int i=0; i<frame->height; i++){
    frame->array[i][frame->width-2] = BORDER_CHAR;
    frame->array[i][frame->width-1] = BORDER_CHAR;
  }
  for(int j=0; j<frame->width; j++){
    frame->array[0][j] = BORDER_CHAR;
    //frame->array[1][j] = BORDER_CHAR;
  }
  for(int j=0; j<frame->width; j++){
    //frame->array[frame->height - 2][j] = BORDER_CHAR;
    frame->array[frame->height - 1][j] = BORDER_CHAR;
  }
}

void printFrame(Frame frame){
  for(int i = 0; i<frame->height; i++){
    for(int j = 0; j<frame->width; j++){
      printf("%c",frame->array[i][j]);
    }
    printf("\n");
  }
}