#include <board.h>
#include <iostream>
#include <sstream>

using namespace std;

int main () {
    string input;
    Board chessBoard();

    while (true) {
        string cmd;
        cout << "Enter a command: ";
        getline(cin, input);
        istringstream iss{input};
        iss >> cmd;

        //currently ignores error-handeling to accomadate for enhancements format
        if (cmd == "game") { 
            string whiteSide, blackSide;
            iss >> whiteSide >> blackSide;

            // fill later
        } else if (cmd == "set up") {
            // fill
        }
        else {
            cout << "Invalid input";
        }
    }

}
