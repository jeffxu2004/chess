#include "graphicsdisplay.h"
#include "../piececreator.h"

GraphicsDisplay::GraphicsDisplay(int n): gridSize {n}, squareWidth {BOARD_WIDTH / n} {
    // set up display with empty board
    display.fillRectangle(COORDS_WIDTH, COORDS_WIDTH, WIDTH - 2*COORDS_WIDTH , WIDTH - 2*COORDS_WIDTH , Xwindow::Blue);

    for (int i=0; i<gridSize; ++i) {
        int start = COORDS_WIDTH + BORDER_WIDTH + squareWidth / 2;
        string label;
        label += char('H'-i);
        display.drawString(COORDS_WIDTH / 2, start + i*squareWidth, label);
        display.drawString(start + i*squareWidth, WIDTH-COORDS_WIDTH / 2, to_string(i+1));
        if (i % 2 == 0) {
            for (int j=0; j<gridSize; ++j) {
                if (j % 2 == 0)
                    display.fillRectangle(i*squareWidth+30, j*squareWidth+30, squareWidth, squareWidth, Xwindow::Red);
                else 
                    display.fillRectangle(i*squareWidth+30, j*squareWidth+30, squareWidth, squareWidth, Xwindow::Green);
            }
        } else {
            for (int j=0; j<gridSize; ++j) {
                if (j % 2 == 0)
                    display.fillRectangle(i*squareWidth+30, j*squareWidth+30, squareWidth, squareWidth, Xwindow::Green);
                else  
                    display.fillRectangle(i*squareWidth+30, j*squareWidth+30, squareWidth, squareWidth, Xwindow::Red);
            }
        }
    }
}

void GraphicsDisplay::update(const Piece* item) {
    int row = 8 - item->getCoords().second;
    int col = int(item->getCoords().first - 'a');

    bool isDark = ((row % 2 == 0) && (col % 2 == 1)) || ((row % 2 == 1) && (col % 2 == 0));
    string piece = PieceCreator::drawPiece(item->pieceType(), item->getSide(), isDark);

    if (piece != "_" && piece != " ") {
        display.drawString(
            col*squareWidth+BORDER_WIDTH+COORDS_WIDTH+squareWidth / 2-10,
            row*squareWidth+BORDER_WIDTH+COORDS_WIDTH+squareWidth / 2,
            piece
        );
    } else if (piece != "_") {
        display.fillRectangle(
            col*squareWidth+BORDER_WIDTH+COORDS_WIDTH,
            row*squareWidth+BORDER_WIDTH+COORDS_WIDTH,
            squareWidth,
            squareWidth,
            Xwindow::Red
        );
    } else {
        display.fillRectangle(
            col*squareWidth+BORDER_WIDTH+COORDS_WIDTH,
            row*squareWidth+BORDER_WIDTH+COORDS_WIDTH,
            squareWidth,
            squareWidth,
            Xwindow::Green
        );
    }
}