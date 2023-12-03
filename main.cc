#include "board.h"
#include "displays/controller.h"
#include "chessbot/chessbot.h"
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

bool checkValidInput(string s, ChessBot& cb) {
    if (s == "human") return true;
    if (s == "human") {
        
    }

}


int main () {
    string input;

    while (true) {
        Board board(8);
        string cmd;
        cout << "Enter a command: ";
        Controller c (8);
        board.attach(&c);
        getline(cin, input);
        istringstream iss{input};
        iss >> cmd;

        //currently ignores error-handeling to accomadate for enhancements format
        if (cmd == "game") {  // call "game p p" for testing
            string whiteSide, blackSide; 
            iss >> whiteSide >> blackSide;
            

            board.standardInit();
            cout << c.getTd();

            
            while (true) {
                string start, end;
                getline(cin, input);
                istringstream newIss {input};
                newIss >> cmd >> start >> end;
                
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

                if (board.getState() == Result::Win) {
                    cout << "checkmate" << endl;
                    break;
                } 
                else if (board.getState() == Result::Draw) {
                    cout << "stalemate" << endl;
                    break;
                }
                cout << c.getTd();
            }
        } else if (cmd == "setup") {
            while (true) { //format is K e8
                string piece, move;
                cin >> piece >> move;
                board.changeSquare(piece[0] , make_pair(move[0],move[1] - '0'));
            }
            cout << c.getTd();
        }
        else {
            cout << "Invalid input";
        }
    }

}
