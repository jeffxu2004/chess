#include "board.h"
#include "displays/controller.h"
#include "chessbot/chessbot.h"
#include "chessbot/chessbotcreator.h"
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


// checks if whitside, blackside is a valid input
bool checkValidInput(string s, bool &cpu) {
    if (s == "human" || s == "p" || s == "player") return true;
    if (s == "computer1" || s == "computer2" || s == "computer3" || s == "computer4") {
        cpu = true;
        return true;
    } 
    if (s == "c1" || s == "c2" || s == "c3" || s == "c4") {
        cpu = true;
        return true;
    }
    return false;
}


int main () {
    string input;
    Board board(8);
    board.standardInit();

    while (true) {
        string cmd;
        cout << "Enter a command: ";
        Controller c (8);
        board.attach(&c);
        getline(cin, input);
        istringstream iss{input};
        iss >> cmd;

        //currently ignores error-handeling to accomadate for enhancements format
        if (cmd == "game") {  // call "game p p" for testing
            bool whiteCPU = false; //true if white is a CPU/bot
            bool blackCPU = false;
            unique_ptr<ChessBot> wBot; //pointer to white Bot 
            unique_ptr<ChessBot> bBot;
            string whiteSide, blackSide; 
            iss >> whiteSide >> blackSide;
            if (!checkValidInput(whiteSide, whiteCPU) || !checkValidInput(whiteSide, blackCPU)) {
                cout << "Invalid input" << endl;
                continue;
            }

            if (whiteCPU) wBot = ChessBotCreator::makeBot(Colour::White);
            if (blackCPU) bBot = ChessBotCreator::makeBot(Colour::Black);           

            cout << c.getTd();
            
            while (true) {
                string start, end;
                getline(cin, input);
                istringstream newIss {input};
                newIss >> cmd >> start >> end;

                if (cmd == "resign") {
                    cout << "lmfao you lost hahahaha" << endl;
                    if (board.getTurn() == Colour::White) cout << "black wins" << endl;
                    if (board.getTurn() == Colour::Black) cout << "white wins" << endl;                   
                }


                if (cmd != "move" || !checkValidCoords(start) || !checkValidCoords(end)) {
                    cout << "Invalid Input" << endl;
                    continue;
                }

                if(board.getTurn() == Colour::White) {
                    if (!whiteCPU) {
                        bool b = board.playMove(make_pair(start[0],start[1] - '0'), make_pair(end[0] , end[1] - '0'));
                        if (!b) {
                            cout << "Not a valid move" << endl;
                            continue;
                        }
                    } else {
                        auto move = wBot->getNextMove();
                        bool b = board.playMove(move.first, move.second);                       
                    }
                }
                if(board.getTurn() == Colour::Black) {
                    if (!blackCPU) {
                        bool b = board.playMove(make_pair(start[0],start[1] - '0'), make_pair(end[0] , end[1] - '0'));
                        if (!b) {
                            cout << "Not a valid move" << endl;
                            continue;
                        }
                    } else {
                        auto move = bBot->getNextMove();
                        bool b = board.playMove(move.first, move.second);                       
                    }
                }

                King* king = dynamic_cast<King*>(board.getKing(Colour::White));
                auto subjects = king->getSubjects();
                cout << "$$$$$$$$$$$$$$" << endl;
                for (auto s: subjects) {
                    cout << s->getCoords() << endl;
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
