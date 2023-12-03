#ifndef GRAPHICSDISPLAY_H
#define GRAPHICSDISPLAY_H

#include "window.h"
#include "../pieces/piece.h"

class GraphicsDisplay {
    Xwindow display;
    const int gridSize;
    const int squareWidth;

    public:
        GraphicsDisplay(int n); // ctor
        void update(const Piece* item);
};

#endif