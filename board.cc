using namespace std;

#include "board.h";


Board::Board() {
    grid.resize(8, vector<unique_ptr<Piece>>(8, nullptr));
    state = Result::Continue;
}

Board::Board(int n) {
    grid.resize(n, vector<unique_ptr<Piece>>(n, nullptr));
    state = Result::Continue;
}

Board::~Board() {
    grid.clear();
}

// can not return unique ptr by value so we use raw ptr
Piece* Board::getPiece(pair<char,int> loc) {
    int col = loc.first - 'a';
    int row = loc.second - 1;
    
    // check if pair is within bounds
    // technically can check if its a valid pair in main to be consistent with other functions
    // easy change to make however
    if (row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size()) {
        return grid[row][col].get(); //returns raw ptr
    } else {
        return nullptr;
    }
}

void Board::playMove(pair<char, int> start, pair<char, int> end) {
    // hehe 
}

bool Board::isValidMove(Piece *piece, pair<char, int> dest) {
    return true;
}

void Board::playMove(pair<char, int> start, pair<char, int> end, PieceType type) {
    // heheheha
}

bool Board::isPromoting(pair<char, int> start, pair<char, int> end) {
    return true;
}

void Board::attach(Observer* obs) {
    observers.emplace_back(obs);
}

void Board::detach(Observer* obs) {
    auto it = std::find(observers.begin(), observers.end(), obs);
    if (it != observers.end()) {
        observers.erase(it);
    }
}

void Board::notifyObservers() {
    //fill
}