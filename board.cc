using namespace std;

#include "board.h";

class Queen;

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

vector<vector<unique_ptr<Piece>>> Board::getGrid() {
    return grid;
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

void Board::changeSquare(pair<char, int> loc, PieceType p, Colour Side) {
    int col = loc.first - 'a';
    int row = loc.second - 1;
    // grid[row][col] = make_unique<Piece>() 
    // Need this method in the future
    

}

bool Board::playMove(pair<char, int> start, pair<char, int> end) {
    
    bool p1 = false;
    bool p2 = false;

    for (auto &row : grid) {
        for (auto &piece : row) {
            if (piece->getCoords() == start || piece->getCoords() == end) {
                //
            }
        }
    }
    

    
    

}

bool Board::isPlayableMove(Piece *piece, pair<char, int> dest) {
    auto moves = piece->getMoves(*this);
    for (const auto m : moves) {
        if (m == dest) {
            return true;
        }
    }

    return false;
}


void Board::playMove(pair<char, int> start, pair<char, int> end, PieceType type, Colour side) {
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

void Board::notifyAllObservers() {
  for (Observer *observer : observers) {
      if (observer->getSubscription() == Subscription::All) { 
          observer->notify(this);
      }
  }
}