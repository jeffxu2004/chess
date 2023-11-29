using namespace std;

#include "board.h";


Board::Board() {
    grid.resize(8, vector<unique_ptr<Piece>>(8, nullptr));
    state = Result::Continue;
    turn = Colour::White;
}

Board::Board(int n) {
    grid.resize(n, vector<unique_ptr<Piece>>(n, nullptr));
    state = Result::Continue;
}

Board::~Board() {
    grid.clear();
}

Result Board::getState() {
    return state;
}

Colour Board::getTurn() {
    return turn;
}

vector<vector<unique_ptr<Piece>>> Board::getGrid() {
    return grid;
}

// can not return unique ptr by value so we use raw ptr
Piece* Board::getPiece(pair<char,int> loc) {
    int col = loc.first - 'a';
    int row = 8 - loc.second;
    
    // check if pair is within bounds
    // technically can check if its a valid pair in main to be consistent with other functions
    // easy change to make however
    if (row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size()) {
        return grid[row][col].get(); //returns raw ptr
    } else {
        return nullptr;
    }
}

void Board::changeSquare(pair<char, int> loc, PieceType p, Colour side) {
    int col = loc.first - 'a';
    int row = 8 - loc.second;
    grid[row][col] = PieceCreator::createPiece(p, side, loc);
}

// there is some functional redundancy between playmove and isplayablemove
// might make some changes later

bool Board::playMove(pair<char, int> start, pair<char, int> end) {
    int col1 = start.first - 'a';
    int row1 = 8 - start.second; 
    int col2 = end.first - 'a';
    int row2 = 8 - end.second;
    King* ownKing;

    
    if(grid[row1][col1]->getSide() != turn) return false; //check if moving piece of own colour
    if(grid[row2][col2]->getSide() == turn) return false; //check if capturing own piece
    
    auto temp = move(grid[row2][col2]); // store piece that is going to be captured 
    grid[row2][col2] = move(grid[row1][col1]); // moves piece to the designated square

    // changes original square to be a blank
    grid[row1][col1] = PieceCreator::createPiece(PieceType::None, Colour::None, start);



    // iterate through pieces to notify king
    for(auto &row : grid) {
        for (auto &piece : row) {
            if (piece->pieceType() == PieceType::King) { //if the piece is a king
                King* k = dynamic_cast<King*>(piece.get());
                auto subjects = k->getSubjects(); //obtain its observers
                if (k->getSide() == turn) ownKing = k;
                for(Piece* s : subjects) {
                    // notify king if piece moved from starting square or to ending square
                    if (s->getCoords() == start) grid[row1][col1]->notifyKing(); 
                    if (s->getCoords() == end) grid[row2][col2]->notifyKing();                    
                }
            }
        }
    }

    // THERE IS AN ISSUE: on reverting the notifyKing if the move is not valid
    // currently WIP 
    if (ownKing->inCheck()) {  // check if king is in check => not valid move
        grid[row1][col1] = move(grid[row2][col2]);
        grid[row2][col2] = move(temp);
        return false;
    }

    // switches turns, can be better designed maybe
    turn = turn == Colour::White ? Colour::Black : Colour::White;
    
    // Check checkmate
    // Check Stalemate

    return true;
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