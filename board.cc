using namespace std;

#include "board.h"

using namespace std;

Board::Board(int n = 8) {
    size = n;
    for (int row = 1; row <= n; row++) {
        grid.push_back(vector<unique_ptr<Piece>>());
        for (char col = 'a'; col <= 'h'; col++) {
            grid[row-1].push_back(PieceCreator::createPiece(PieceType::Blank, Colour::Neither, make_pair(col,8-row+1)));
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

vector<vector<Piece *>> Board::getGrid() const {
    vector<vector<Piece*>> retGrid (size, vector<Piece*> (size, nullptr));
    for (int i=0; i<size; ++i) {
        for (int j=0; j<size; ++j) {
            retGrid[i][j] = grid[i][j].get();
        }
    }
    return retGrid;
}

// can not return unique ptr by value so we use raw ptr
Piece* Board::getPiece(pair<char,int> loc) {
    int col = loc.first - 'a';
    int row = size - loc.second;
    
    // check if pair is within bounds
    // technically can check if its a valid pair in main to be consistent with other functions
    // easy change to make however
    if (row >= 0 && row < size && col >= 0 && col < size) {
        return grid[row][col].get(); //returns raw ptr
    } else {
        return nullptr;
    }
}

Piece* Board::getKing(Colour c) {
    for(auto &row : grid) {
        for (auto &piece : row) {
            if (piece->pieceType() == PieceType::King && piece->getSide() == c) { //finds king
                return piece.get(); //returns raw ptr 
            }
        }
    }
    return nullptr;
}

void Board::setPromotionPiece(PieceType p) {
    promotionPiece = p;
}

void Board::standardInit() {
    // Pawns
    for (char col = 'a'; col <= 'h'; col++) {
        grid[1][col - 'a'] = PieceCreator::createPiece(PieceType::Pawn, Colour::Black, make_pair(col, 7));
        grid[6][col - 'a'] = PieceCreator::createPiece(PieceType::Pawn, Colour::White, make_pair(col, 2));
    }

    // Rooks
    grid[7][0] = PieceCreator::createPiece(PieceType::Rook, Colour::White, make_pair('a', 1));
    grid[7][7] = PieceCreator::createPiece(PieceType::Rook, Colour::White, make_pair('h', 1));
    grid[0][0] = PieceCreator::createPiece(PieceType::Rook, Colour::Black, make_pair('a', 8));
    grid[0][7] = PieceCreator::createPiece(PieceType::Rook, Colour::Black, make_pair('h', 8));

    // Knights
    grid[0][1] = PieceCreator::createPiece(PieceType::Knight, Colour::Black, make_pair('b', 8));
    grid[0][6] = PieceCreator::createPiece(PieceType::Knight, Colour::Black, make_pair('g', 8));
    grid[7][1] = PieceCreator::createPiece(PieceType::Knight, Colour::White, make_pair('b', 1));
    grid[7][6] = PieceCreator::createPiece(PieceType::Knight, Colour::White, make_pair('g', 1));

    // Bishops
    grid[0][2] = PieceCreator::createPiece(PieceType::Bishop, Colour::Black, make_pair('c', 8));
    grid[0][5] = PieceCreator::createPiece(PieceType::Bishop, Colour::Black, make_pair('f', 8));
    grid[7][2] = PieceCreator::createPiece(PieceType::Bishop, Colour::White, make_pair('c', 1));
    grid[7][5] = PieceCreator::createPiece(PieceType::Bishop, Colour::White, make_pair('f', 1));

    // Queens
    grid[0][3] = PieceCreator::createPiece(PieceType::Queen, Colour::Black, make_pair('d', 8));
    grid[7][3] = PieceCreator::createPiece(PieceType::Queen, Colour::White, make_pair('d', 1));

    // Kings
    grid[0][4] = PieceCreator::createPiece(PieceType::King, Colour::Black, make_pair('e', 8));
    King *king = dynamic_cast<King*>(grid[0][4].get());
    king->notify(king, this);
    grid[7][4] = PieceCreator::createPiece(PieceType::King, Colour::White, make_pair('e', 1));
    king = dynamic_cast<King*>(grid[7][4].get());
    king->notify(king, this);

    for(auto &row : grid) {
        for (auto &piece : row) {
            notifyAllObservers(piece.get(), getTurn());
        }
    }
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
    auto kingw = dynamic_cast<King*>(getKing(Colour::White));
    auto kingb = dynamic_cast<King*>(getKing(Colour::Black));
    kingw->notify(kingw, this);
    kingb->notify(kingb, this);   
    if (kingw->inCheck() || kingb->inCheck()) return false;
    return true;
}

void Board::changeSquare(pair<char, int> loc, PieceType p, Colour side) {
    int col = loc.first - 'a';
    int row = size - loc.second;
    grid[row][col] = PieceCreator::createPiece(p, side, loc);
    notifyAllObservers(getPiece(loc), getTurn());
}

void Board::changeSquare(char c, pair<char, int> loc) {
    int col = int(loc.first - 'a');
    int row = size - loc.second;
    grid[row][col] = PieceCreator::setPiece(c, loc);   
    notifyAllObservers(getPiece(loc), getTurn());   
}

bool Board::playMove(pair<char, int> start, pair<char, int> end) {
    cout << "Start of playMove(): " << endl;
    int col1 = start.first - 'a';
    int row1 = size - start.second; 
    auto kingw = dynamic_cast<King*>(getKing(Colour::White));
    auto subject = kingw->getSubjects();
    cout << "   White King Subjects:" << endl;
    for (auto s:subject) {
        cout << s->getCoords() << endl;
    }

    auto kingb = dynamic_cast<King*>(getKing(Colour::Black));
    subject = kingb->getSubjects();
    cout << "   Black King Subjects: " << endl;
    for (auto s:subject){
        cout << s->getCoords() << endl;
    }
    cout << "------------------------------" << endl;
    if (isPlayableMove(grid[row1][col1].get(), end) == false) return false;
    bool legal = this->playLegalMove(start, end);

    if (!legal) return false;

    cout << "*************" << endl;
    kingw = dynamic_cast<King*>(getKing(Colour::White));
    subject = kingw->getSubjects();
    cout << "   White King Subjects:" << endl;
    for (auto s:subject) {
        cout << s->getCoords() << endl;
    }
    
    turn = turn == Colour::White ? Colour::Black : Colour::White;

    notifyAllObservers(getPiece(start), getTurn());   
    notifyAllObservers(getPiece(end), getTurn()); 

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
    

    cout << "End of playMove(): " << endl;

    kingw = dynamic_cast<King*>(getKing(Colour::White));
    subject = kingw->getSubjects();
    cout << "   White King Subjects:" << endl;
    for (auto s:subject) {
        cout << s->getCoords() << endl;
    }

    kingb = dynamic_cast<King*>(getKing(Colour::Black));
    subject = kingb->getSubjects();
    cout << "   Black King Subjects: " << endl;
    for (auto s:subject){
        cout << s->getCoords() << endl;
    }
    cout << "-----------------------" << endl;

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

    return list;
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
    bool kingMove = getPiece(start)->pieceType() == PieceType::King;

    if(grid[row1][col1]->getSide() != turn) return false; //check if moving piece of own colour
    if(grid[row2][col2]->getSide() == turn) return false; //check if capturing own piece

    // checks for promotion, en passant, castling
    promotes = isPromoting(start, end);
    enpas = isEnPas(start, end);
    castle = isCastle(start, end);

    // checks if the starting square is in the subject list of either kings
    bool ownSubjectStart = false;
    bool oppSubjectStart = false;
    
    ownSubjects = ownKing->getSubjects();
    oppSubjects = oppKing->getSubjects();

    for (auto subject:ownSubjects) {
        if (subject->getCoords() == start) ownSubjectStart = true;
    }

    for (auto subject:oppSubjects) {
        if (subject->getCoords() == start) oppSubjectStart = true;
    }

    // checks if the ending square is in the subject list of either kings
    bool ownSubjectEnd = false;
    bool oppSubjectEnd = false;

    for (auto subject:ownSubjects) {
        if (subject->getCoords() == end) ownSubjectEnd = true;
    }

    for (auto subject:oppSubjects) {
        if (subject->getCoords() == end) oppSubjectEnd = true;
    }

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
        grid[row2][col2] = PieceCreator::createPiece(temp2->pieceType(), turn, end);
    }

    // changes original square to be a blank
    grid[row1][col1] = PieceCreator::createPiece(PieceType::Blank, Colour::Neither, start);
    //notify king observers for own king 
    
    if (ownSubjectStart) {
        ownKing->dropSubject(temp2.get());
        ownKing->addSubject(grid[row1][col1].get());
    }

    if (oppSubjectStart) {
        oppKing->dropSubject(temp2.get());
        oppKing->addSubject(grid[row1][col1].get());
    }

    if (ownSubjectEnd) {
        ownKing->dropSubject(temp.get());
        ownKing->addSubject(grid[row2][col2].get());
    }

    if (oppSubjectEnd) {
        oppKing->dropSubject(temp.get());
        oppKing->addSubject(grid[row2][col2].get());
    }

    if (ownSubjectStart) ownKing->notify(grid[row1][col1].get(), this);
    

    auto subjects = ownKing->getSubjects();
    for(Piece* s : subjects) {
        if (s->getCoords() == end) ownKing->notify(grid[row2][col2].get(), this);
    }

    //notify king observrs for enemy king   
    if (oppSubjectStart) oppKing->notify(grid[row1][col1].get(), this);

    subjects = oppKing->getSubjects();

    for(Piece* s : subjects) {
        if (s->getCoords() == end) oppKing->notify(grid[row2][col2].get(), this);
    }

    inCheck = ownKing->inCheck();
    
    if (revert || inCheck) { // if reverts or the king is still in check
        if (enpas) {
            grid[row1][col1] = move(temp2); // restore orginal move
            grid[row2+1][col1] = move(temp); //restore captured pawn
            grid[row2][col2] = PieceCreator::createPiece(PieceType::Pawn, Colour::Neither, end);
            // restores squares to blanks
            grid[row2 + 1][col2] = PieceCreator::createPiece(PieceType::Blank, Colour::Neither, make_pair(col2 + 'a', row2 + 1));                 
        } else if (castle) {
            grid[row1][col1] = move(temp2); // restore orginal move
            grid[row2+1][col1] = move(temp); //restore captured pawn
            grid[row2][col2] = PieceCreator::createPiece(PieceType::Blank, Colour::Neither, end); 
            // restores squares to blanks
            if (col2 > col1) grid[row2][col2 - 1] = PieceCreator::createPiece(PieceType::Blank, Colour::Neither, make_pair(col2 + 'a' - 1, row2));
            else grid[row2][col2 + 1] = PieceCreator::createPiece(PieceType::Blank, Colour::Neither, make_pair(col2 + 'a' + 1, row2));
        } else {
            grid[row2][col2] = move(temp); // restore original pieces
            grid[row1][col1] = move(temp2);
        }
        ownKing->setSubjects(ownSubjects);
        oppKing->setSubjects(oppSubjects);

        if (revert) return !inCheck;
        else return false;
    }
    
    Piece* movedPiece = getPiece(end);

    //set moved for rook to be true
    if (movedPiece->pieceType() == PieceType::Rook) dynamic_cast<Rook*>(movedPiece)->hasMoved();

    //set moved for rook to be false
    if (movedPiece->pieceType() == PieceType::Pawn) {
        if (row1 + 2 == row2 || row1 - 2 == row2) {
            auto p = dynamic_cast<Pawn*>(movedPiece);
            p->setMoveTwo(false);
            p->setEnPas(true);
        }
    }

    // disable enpas not sure if works
    for(auto &row : grid) {
        for (auto &piece : row) {
            if (piece->pieceType() == PieceType::Pawn) {
                auto p = dynamic_cast<Pawn*>(piece.get());
                p->setEnPas(false);
            }
        }
    }

    if (kingMove) {
        King* k = dynamic_cast <King*> (grid[row2][col2].get());
        k->setSubjects(ownKing->getSubjects());
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

void Board::notifyAllObservers(Piece* p, Colour turn) {
  for (Observer *observer : observers) {
      if (observer->getSubscription() == Subscription::All) { 
          observer->notify(p, turn);
      }
  }
}
