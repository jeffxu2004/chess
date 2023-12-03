#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <X11/Xlib.h>
#include <iostream>
#include <string>

const int WIDTH = 600;
const int BORDER_WIDTH = 5;
const int COORDS_WIDTH = 25;
const int BOARD_WIDTH = WIDTH - 2 * (BORDER_WIDTH + COORDS_WIDTH);

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

 public:
  Xwindow(int width=WIDTH, int height=WIDTH);  // Constructor; displays the window.
  ~Xwindow();                              // Destructor; destroys the window.

  enum {White=0, Black, Red, Green, Blue}; // Available colours.

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int height, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

};

#endif
