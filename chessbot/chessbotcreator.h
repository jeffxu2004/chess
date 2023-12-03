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
        static unique_ptr<ChessBot> makeBot(string s, Colour c) {
            if (s == "computer1" || s == "c1"){
                return make_unique<LevelOne>(c);               
            } else if (s == "computer2" || s == "c2"){
                return make_unique<LevelTwo>(c);
            } else if (s == "computer3" || s == "c3"){
                return make_unique<LevelThree>(c);
            } else if (s == "computer4" || s == "c4"){
                return make_unique<LevelFour>(c);
            } else {
                return make_unique<LevelOne>(c);                  
            }
        }
};

#endif
