#include "board.h"
#include "displays/controller.h"
#include <iostream>
#include <sstream>

using namespace std;

// returns true if its a valid chess coord like "a8" or "b3"
bool checkValidCoords(const string& coords) {
    if (coords.length() != 2) return false;

    char col = coords[0];
    char row = coords[1];

    bool isValidCol = col >= 'a' && col <= 'h'; 
    bool isValidRow = row >= '1' && row <= '8';

    return isValidCol && isValidRow;
}


int main () {
    string input;

    while (true) {
        Board board(8);
        string cmd;
        cout << "Enter a command: ";
        Controller c (8);
        getline(cin, input);
        istringstream iss{input};
        iss >> cmd;

        //currently ignores error-handeling to accomadate for enhancements format
        if (cmd == "game") {  // call "game p p" for testing
            string whiteSide, blackSide; 
            iss >> whiteSide >> blackSide;
            board.attach(&c);
            board.standardInit();
            cout << c.getTd();

            
            while (true) {
                string start, end;
                getline(cin, input);
                iss >> cmd >> start >> end;
                if(board.getTurn() == Colour::White) {
                    if (whiteSide == "p") {
                        bool b = board.playMove(make_pair(start[0],start[1] - '0'), make_pair(end[0] , end[1] - '0'));
                    } else if (whiteSide == "c1"){
                        //
                    }
                }
                else if(board.getTurn() == Colour::Black) {
                    if (blackSide == "p") {
                        bool b = board.playMove(make_pair(start[0],start[1] - '0'), make_pair(end[0] , end[1] - '0'));
                    } else if (blackSide == "c1"){
                        //
                    }
                }

                if (board.getState() == Win) {
                    cout << "checkmate" << endl;
                    break;
                } 
                else if (board.getState() == Draw) {
                    cout << "stalemate" << endl;
                    break;
                }
                cout << c.getTd();
            }
        } else if (cmd == "set up") {
            board.attach(&c);
            while (true) {
                string piece, move;
                cin >> piece >> move;
                //board.changeSquare()
            }   
            cout << c.getTd();
        }
        else {
            cout << "Invalid input";
        }
    }

}
