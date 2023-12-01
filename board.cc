using namespace std;

#include "board.h"

Board::Board(int n = 8) {
    grid.resize(n, vector<unique_ptr<Piece>>(n, nullptr));
    size = n;

    for (char col = 'a'; col <= 'h'; col++) {
        for (int row = 1; row <= n; row++) {
            grid[row - 1][col - 'a'] = PieceCreator::createPiece(PieceType::Blank, Colour::None, pair(col, row));
        }
    }
}

Board::~Board() {
    grid.clear();
}

PieceType Board::getPromotionPiece() const {
    return promotionPiece;
}

Result Board::getState() const {
    return state;
}

Colour Board::getTurn() const {
    return turn;
}

vector<vector<unique_ptr<Piece>>> Board::getGrid() const {
    return grid;
}

// can not return unique ptr by value so we use raw ptr
Piece* Board::getPiece(pair<char,int> loc) {
    int col = loc.first - 'a';
    int row = size - loc.second;
    
    // check if pair is within bounds
    // technically can check if its a valid pair in main to be consistent with other functions
    // easy change to make however
    if (row >= 0 && row < grid.size() && col >= 0 && col < grid[row].size()) {
        return grid[row][col].get(); //returns raw ptr
    } else {
        return nullptr;
    }
}

King* Board::getKing(Colour c) {
    for(auto &row : grid) {
        for (auto &piece : row) {
            if (piece->pieceType() == PieceType::King) { //finds king
                return dynamic_cast<King*>(piece.get()); //returns raw ptr 
            }
        }
    }
}

void Board::setPromotionPiece(PieceType p) {
    promotionPiece = p;
}

void Board::standardInit() {
    // Pawns
    for (char col = 'a'; col <= 'h'; col++) {
        grid[6][col - 'a'] = PieceCreator::createPiece(PieceType::Pawn, Colour::Black, make_pair(col, 2));
        grid[1][col - 'a'] = PieceCreator::createPiece(PieceType::Pawn, Colour::White, make_pair(col, 7));
    }

    // Rooks
    grid[7][0] = PieceCreator::createPiece(PieceType::Rook, Colour::Black, make_pair('a', 8));
    grid[7][7] = PieceCreator::createPiece(PieceType::Rook, Colour::Black, make_pair('h', 8));
    grid[0][0] = PieceCreator::createPiece(PieceType::Rook, Colour::White, make_pair('a', 1));
    grid[0][7] = PieceCreator::createPiece(PieceType::Rook, Colour::White, make_pair('h', 1));

    // Knights
    grid[7][1] = PieceCreator::createPiece(PieceType::Knight, Colour::Black, make_pair('b', 8));
    grid[7][6] = PieceCreator::createPiece(PieceType::Knight, Colour::Black, make_pair('g', 8));
    grid[0][1] = PieceCreator::createPiece(PieceType::Knight, Colour::White, make_pair('b', 1));
    grid[0][6] = PieceCreator::createPiece(PieceType::Knight, Colour::White, make_pair('g', 1));

    // Bishops
    grid[7][2] = PieceCreator::createPiece(PieceType::Bishop, Colour::Black, make_pair('c', 8));
    grid[7][5] = PieceCreator::createPiece(PieceType::Bishop, Colour::Black, make_pair('f', 8));
    grid[0][2] = PieceCreator::createPiece(PieceType::Bishop, Colour::White, make_pair('c', 1));
    grid[0][5] = PieceCreator::createPiece(PieceType::Bishop, Colour::White, make_pair('f', 1));

    // Queens
    grid[7][3] = PieceCreator::createPiece(PieceType::Queen, Colour::Black, make_pair('d', 8));
    grid[0][3] = PieceCreator::createPiece(PieceType::Queen, Colour::White, make_pair('d', 1));

    // Kings
    grid[7][4] = PieceCreator::createPiece(PieceType::King, Colour::Black, make_pair('e', 8));
    grid[0][4] = PieceCreator::createPiece(PieceType::King, Colour::White, make_pair('e', 1));
}


bool Board::validSetup() {
    int countw = 0;
    int countb = 0;
    for(auto &row : grid) {
        for (auto &piece : row) {
            if (piece->pieceType() == PieceType::King) { //finds king
                if (piece->getSide() == Colour::White) countw++;
                else if (piece->getSide() == Colour::Black) countb++;                
            }
        }
    }
    if (countw != 1 || countb != 1) return false; //checks only 1 king of each colour

    for(int i = 0; i <= size; i++) {
        if (grid[0][i]->pieceType() == PieceType::Pawn) return false; 
        if (grid[size - 1][i]->pieceType() == PieceType::Pawn) return false;        
    }
    auto kingw = getKing(Colour::White);
    auto kingb = getKing(Colour::Black);
    kingw->notify(kingw, this);
    kingb->notify(kingb, this);   
    if (kingw->inCheck() || kingb->inCheck()) return false;
    return true;
}

void Board::changeSquare(pair<char, int> loc, PieceType p, Colour side) {
    int col = loc.first - 'a';
    int row = size - loc.second;
    grid[row][col] = PieceCreator::createPiece(p, side, loc);
}

bool Board::playMove(pair<char, int> start, pair<char, int> end) {
    int col1 = start.first - 'a';
    int row1 = size - start.second; 

    if (isPlayableMove(grid[row1][col1].get(), end) == false) return false;

    bool legal = this->playLegalMove(start, end);
    bool checkmate;
    bool stalemate;
    if (!legal) return false;

    turn = turn == Colour::White ? Colour::Black : Colour::White;

    auto king =  dynamic_cast<King*>(getKing(turn)); //find king
    bool isCheck = king->inCheck();  // check if king is in check

    bool playableMove = false;
    auto moves = getAllMoves(turn);
    for (auto m : moves) { //iterates through possible moves next player can make
        if(kingIsNotCheck(m.first, m.second)) { //checks if theres a single legal move
            playableMove = true; 
            break;
        }
    }
    if (playableMove == false) { // if there are no legal moves
        if (isCheck == true) state = Result::Win; //if the king is in check other side wins
        else state = Result::Draw; //otherwise its stalemate => draw
    }

    return true;
}

bool Board::isPlayableMove(Piece *piece, pair<char, int> dest) {
    if (piece->getSide() != turn) return false;
    auto moves = piece->getMoves(*this);
    for (const auto m : moves) { //checks if dest is an element of the getMoves
        if (m == dest) {
            return true;
        }
    }

    return false;
}

vector<pair<pair<char, int>,pair<char, int>>> Board::getAllMoves(Colour c) {
    vector<pair<pair<char, int>,pair<char, int>>> list;
    for(auto &row : grid) {
        for (auto &piece : row) { //iterates through each piece 
            if (piece->getSide() == turn) {  //checks for pieces of own colour
                auto moves = piece->getMoves(*this);
                for(auto m : moves) { 
                    auto a = piece->getCoords();
                    list.emplace_back(make_pair(a, m)); //adds all possible moves to a vector
                }
            }
        }
    }
}

bool Board::kingIsNotCheck(pair<char, int> start, pair<char, int> end) {
    return checkLegalMove(start, end, true);
}


bool Board::playLegalMove(pair<char, int> start, pair<char, int> end){
    return checkLegalMove(start, end, false);    
}

bool Board::checkLegalMove(pair<char, int> start, pair<char, int> end, bool revert) {
    int col1 = start.first - 'a';
    int row1 = size - start.second; 
    int col2 = end.first - 'a';
    int row2 = size - end.second;
    vector<Piece*> ownSubjects; //used to store original observers of white king
    vector<Piece*> oppSubjects; //used to store original observers of black king
    King* ownKing = dynamic_cast<King*> (getKing(turn));
    King* oppKing = dynamic_cast<King*> (getKing(turn == Colour::White ? Colour::Black : Colour::White));
    bool inCheck;
    unique_ptr<Piece> temp; //used to hold pieces in case revert 
    unique_ptr<Piece> temp2; 
    bool promotes = false;
    bool enpas = false;
    bool castle = false;

    if(grid[row1][col1]->getSide() != turn) return false; //check if moving piece of own colour
    if(grid[row2][col2]->getSide() == turn) return false; //check if capturing own piece

    // checks for promotion, en passant, castling
    promotes = isPromoting(start, end);
    enpas = isEnPas(start, end);
    castle = isCastle(start, end);


    if(promotes) {
        temp = move(grid[row2][col2]); // stores piece on back rank
        temp2 = move(grid[row1][col1]); // stores old pawn
        grid[row2][col2] = PieceCreator::createPiece(promotionPiece, turn, end);
    } else if (enpas) {
        temp = move(grid[row2 + 1][col2]); // store pawn that is going to be captured 
        temp2 = move(grid[row1][col1]); // stores piece that is going to be moved        
        grid[row2][col2] = PieceCreator::createPiece(PieceType::Pawn, turn, end);
        grid[row2 + 1][col2] = PieceCreator::createPiece(PieceType::Pawn, turn, make_pair(col2 + 'a', row2 + 1));      
    } else if (castle) {
        temp = move(grid[row2][col2]); // store piece that is going to be captured 
        temp2 = move(grid[row1][col1]); // stores piece that is going to be moved
        grid[row2][col2] = PieceCreator::createPiece(PieceType::King, turn, end); 
        if (col2 > col1) grid[row2][col2 - 1] = PieceCreator::createPiece(PieceType::Rook, turn, make_pair(col2 + 'a' - 1, row2));
        else grid[row2][col2 + 1] = PieceCreator::createPiece(PieceType::Rook, turn, make_pair(col2 + 'a' + 1, row2));
    } else {
        temp = move(grid[row2][col2]); // store piece that is going to be captured 
        temp2 = move(grid[row1][col1]); // stores piece that is going to be moved
        grid[row2][col2] = PieceCreator::createPiece(grid[row1][col1]->pieceType(), turn, end);
    }

    // changes original square to be a blank
    grid[row1][col1] = PieceCreator::createPiece(PieceType::Blank, Colour::None, start);

    
    //notify king observers for own king
    auto subjects = ownKing->getSubjects();
    ownSubjects = subjects;
    for(Piece* s : subjects) {
        // notify king if piece moved from starting square or to ending square
        // Instead of calling notifyKing, just call ownKing->notify(grid[row1][col1], )
        if (s->getCoords() == start) ownKing->notify(grid[row1][col1].get(), this);
        if (s->getCoords() == end) ownKing->notify(grid[row2][col2].get(), this);
    }

    // en paessent 
    //notify king observrs for enemy king
    subjects = oppKing->getSubjects();
    oppSubjects = subjects;
    for(Piece* s : subjects) {
        // notify king if piece moved from starting square or to ending square
        // Instead of calling notifyKing, just call ownKing->notify(grid[row1][col1], )
        if (s->getCoords() == start) oppKing->notify(grid[row1][col1].get(), this);
        if (s->getCoords() == end) oppKing->notify(grid[row2][col2].get(), this);      
    }

    inCheck = ownKing->inCheck() ? true : false;
    if (revert || inCheck) { // if reverts or the king is still in check
        grid[row2][col2] = move(temp); // stores piece on back rank
        grid[row1][col1] = move(temp2);
        if (enpas) {
            grid[row1][col1] = move(temp2); // restore orginal move
            grid[row2+1][col1] = move(temp); //restore captured pawn
            grid[row2][col2] = PieceCreator::createPiece(PieceType::Pawn, Colour::None, end);
            // restores squares to blanks
            grid[row2 + 1][col2] = PieceCreator::createPiece(PieceType::Blank, Colour::None, make_pair(col2 + 'a', row2 + 1));                 
        } else if (castle) {
            grid[row1][col1] = move(temp2); // restore orginal move
            grid[row2+1][col1] = move(temp); //restore captured pawn
            grid[row2][col2] = PieceCreator::createPiece(PieceType::Blank, Colour::None, end); 
            // restores squares to blanks
            if (col2 > col1) grid[row2][col2 - 1] = PieceCreator::createPiece(PieceType::Blank, Colour::None, make_pair(col2 + 'a' - 1, row2));
            else grid[row2][col2 + 1] = PieceCreator::createPiece(PieceType::Blank, Colour::None, make_pair(col2 + 'a' + 1, row2));
        }

        if (revert) return !inCheck;
        else return false;
    }
    return true; //if reverting the board is not requested and that its a legal move return true

}

bool Board::isPromoting(pair<char, int> start, pair<char, int> end) {
    int col1 = start.first - 'a';
    int row1 = size - start.second;
    

    if (grid[row1][col1]->pieceType() == PieceType::Pawn) {
        if (grid[row1][col1]->getSide() == Colour::White && row1 == 1) return true;
        if (grid[row1][col1]->getSide() == Colour::Black && row1 == 7) return true;
    }
    return false;
}

bool Board::isCastle(pair<char, int> start, pair<char, int> end) {
    int col1 = start.first - 'a';
    int row1 = size - start.second; 
    int col2 = end.first - 'a';
    int row2 = size - end.second;

    if (grid[row1][col1]->pieceType() == PieceType::King) {
        if ( col1 + 2 == col2 || col1 - 2 == col2) return true; //checks if king is making castling move
    }
    return false;
}

bool Board::isEnPas(pair<char, int> start, pair<char, int> end) {
    int col1 = start.first - 'a';
    int row1 = size - start.second; 
    int col2 = end.first - 'a';
    int row2 = size - end.second;

    if (grid[row1][col1]->pieceType() == PieceType::Pawn) {
        if ( col1 + 1 == col2 || col1 - 1 == col2) { //checks if pawn is capturing a piece 
            // "capturing" empty square => enpas
            if (grid[row2][col2]->pieceType() == PieceType::Blank) return true;
        } 
    }
    return false;
}

void Board::attach(Observer* obs) {
    observers.emplace_back(obs);
}

void Board::detach(Observer* obs) {
    auto it = find(observers.begin(), observers.end(), obs);
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