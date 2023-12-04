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
    Controller c (8);
    board.attach(&c);
    board.standardInit();
    int blackScore = 0;
    int whiteScore = 0;
    // scoring not yet added
    while (true) {
        string cmd;
        cout << "Enter a command: " << endl;
        getline(cin, input);
        istringstream iss{input};
        iss >> cmd;
        
        // format is game whiteplayer blackplayer
        // game p p for player player
        // game p c1-c4 for player bot
        // game c4-c1 p also
        //currently ignores error-handeling to accomadate for enhancements format
        if (cmd == "game") {  // call "game p p" for testing
            bool whiteCPU = false; //true if white is a CPU/bot
            bool blackCPU = false;
            unique_ptr<ChessBot> wBot; //pointer to white Bot 
            unique_ptr<ChessBot> bBot;
            string whiteSide, blackSide; 
            iss >> whiteSide >> blackSide;
            if (!checkValidInput(whiteSide, whiteCPU) || !checkValidInput(blackSide, blackCPU)) {
                cout << "Invalid input" << endl;
                continue;
            }

            if (whiteCPU) wBot = ChessBotCreator::makeBot(whiteSide, Colour::White);
            if (blackCPU) bBot = ChessBotCreator::makeBot(blackSide, Colour::Black);           

            cout << c.getTd();
            
            while (true) { // simply call move for cpu turn
                cout << "Enter a command:" << endl;
                string start, end;
                getline(cin, input);
                istringstream newIss {input};
                newIss >> cmd >> start >> end;

                if (cmd == "resign") {
                    cout << "lmfao you lost hahahaha" << endl;
                    string side = board.getTurn() == Colour::White ? "Black" : "White";
                    cout << side << " wins!" << endl;  
                    break;                
                }

                // checks valid cmd input
                if (cmd == "move" ) {
                    if (board.getTurn() == Colour::White && !whiteCPU)
                        if (!checkValidCoords(start) || !checkValidCoords(end)) {
                        cout << "Invalid Input" << endl;
                        continue;
                    }
                    if (board.getTurn() == Colour::Black && !blackCPU)
                        if (!checkValidCoords(start) || !checkValidCoords(end)) {
                        cout << "Invalid Input" << endl;
                        continue;
                    }
                } else {
                    cout << "Invalid Input" << endl;
                    continue;                    
                }

                if(board.getTurn() == Colour::White) {
                    if (!whiteCPU) {
                        if (board.isPromoting(make_pair(start[0],start[1] - '0'), make_pair(end[0] , end[1] - '0'))) {
                            string promotion;
                            newIss >> promotion;
                            if (promotion == "Q" || promotion == "q") board.setPromotionPiece(PieceType::Queen);
                            if (promotion == "R" || promotion == "r") board.setPromotionPiece(PieceType::Rook);
                            if (promotion == "N" || promotion == "n") board.setPromotionPiece(PieceType::Knight);
                            if (promotion == "B" || promotion == "b") board.setPromotionPiece(PieceType::Bishop);
                        }
                        bool b = board.playMove(make_pair(start[0],start[1] - '0'), make_pair(end[0] , end[1] - '0'));
                        if (!b) {
                            cout << "Not a valid move" << endl;
                        }
                    } else {
                        auto move = wBot->getNextMove(board);
                        cout << move << endl;
                        if (move.first.first == '0') { // no valid moves 
                            cout << "no moves possible" << endl;
                        } else {
                            bool b = board.playMove(move.first, move.second); 
                        }
                    }
                }
                else if(board.getTurn() == Colour::Black) {
                    if (!blackCPU) {
                        if (board.isPromoting(make_pair(start[0],start[1] - '0'), make_pair(end[0] , end[1] - '0'))) {
                            string promotion;
                            newIss >> promotion;
                            if (promotion == "Q" || promotion == "q") board.setPromotionPiece(PieceType::Queen);
                            if (promotion == "R" || promotion == "r") board.setPromotionPiece(PieceType::Rook);
                            if (promotion == "N" || promotion == "n") board.setPromotionPiece(PieceType::Knight);
                            if (promotion == "B" || promotion == "b") board.setPromotionPiece(PieceType::Bishop);
                        }
                        bool b = board.playMove(make_pair(start[0],start[1] - '0'), make_pair(end[0] , end[1] - '0'));
                        if (!b) {
                            cout << "Not a valid move" << endl;
                        }
                    } else {
                        auto move = bBot->getNextMove(board);
                        cout << move << endl;
                        if (move.first.first == '0') { // no valid moves 
                            cout << "no moves possible" << endl; 
                        } else {
                            bool b = board.playMove(move.first, move.second);   
                        }                      
                    }
                }

                if (board.getState() == Result::Win) {
                    cout << "Checkmate! ";
                    string side = board.getTurn() == Colour::White ? "Black" : "White";
                    cout << side << " wins!" << endl;
                    break;
                } 
                else if (board.getState() == Result::Draw) {
                    cout << "stalemate" << endl;
                    break;
                }
                cout << c.getTd();
                if (dynamic_cast <King*> (board.getKing(Colour::White))->inCheck()) {
                    cout << "White is in check" << endl;
                } else if (dynamic_cast <King*> (board.getKing(Colour::Black))->inCheck()) {
                    cout << "Black is in check" << endl;
                }
            }
            cout << "Enter anything to proceed to the next game" << endl;
            getline(cin, input); 
            board.clearBoard();
            board.standardInit();  // return to standard board after a game

        // PLEASE READ cmds properly: added clear
        } else if (cmd == "setup") { //some of the error detection is not done
            cout << "Now in setup mode" << endl;
            cout << c.getTd();
            while (true) { 
                cout << "Enter a command:" << endl;
                getline(cin, input);
                istringstream newIss {input};

                newIss >> cmd;
                if (cmd == "+") { //format is + K e8
                    string piece, move;
                    newIss >> piece >> move;
                    board.changeSquare(piece[0] , make_pair(move[0],move[1] - '0'));
                } else if (cmd == "-") { //format is - e2 
                    string move;
                    newIss >> move;
                    board.changeSquare(make_pair(move[0],move[1] - '0'), PieceType::Blank, Colour::Neither);
                } else if (cmd == "=") { //format is  = w
                    string c;
                    newIss >> c;
                    if (c == "White" || "W" || "w" || "white") board.setTurn(Colour::White);
                    if (c == "Black" || "B" || "b" || "black") board.setTurn(Colour::Black);
                    board.notifyAllObservers(board.getGrid()[0][0], board.getTurn() );
                } else if (cmd == "done") { // format: done
                    if (board.validSetup()) {  //checks if valid configuration
                        cout << "Exiting setup mode" << endl;
                        break;
                    } else {
                        cout << "Setup is invalid" << endl;
                        cout << "Please make it valid before proceeding" << endl;
                    }
                    
                } else if (cmd == "clear") { // format: clear
                    //enhancement command, clears the board 
                    board.clearBoard();
                } else {
                    cout << "Invalid Input" << endl;
                }
                cout << c.getTd();
            }
        } else if (cmd == "q" || cmd == "quit" || cmd == "exit"){
            cout << "Existing Program" << endl;
            break;
        }else {
            cout << "Invalid input" << endl;
        }
    }
}
