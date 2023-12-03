#ifndef CHESS_BOT_CREATOR_H
#define CHESS_BOT_CREATOR_H

#include <string>
#include <memory>
#include "chessbot.h"
#include "levelfour.cc"
#include "levelthree.cc"
#include "leveltwo.cc"
#include "levelone.cc"


using namespace std;

class ChessBotCreator {
public:
        static unique_ptr<ChessBot> make(string s) {
            if (s == "computer1")
            return make_unique<LevelOne>();
        }
};

#endif
