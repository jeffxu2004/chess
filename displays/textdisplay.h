#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <iostream>
#include <string>
#include <vector>
#include "../pieces/piece.h"

using namespace std;

class TextDisplay {
    vector<vector<char>> display;
    const int gridSize;
    Colour turn = Colour::White;
    
public:
    TextDisplay(int n);
    void update(const Piece* item, Colour turn);
    vector<vector<char>> getDisplay() const;
    friend ostream& operator<<(ostream& out, const TextDisplay& td);
};

#endif
