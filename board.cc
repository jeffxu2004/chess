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

bool Board::checkDraw() {
    for(auto &row : grid) {
        for (auto &piece : row) {
            if (piece->pieceType() != PieceType::King && piece->pieceType() != PieceType::Blank) {
                return false;
            }
        }
    }
    return true;
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

int Board::getSize() {return size;}

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

void Board::setTurn(Colour c) {
    turn = c;
}

void Board::setResult(Result r) {
    state = r;
}

void Board::clearBoard() {
    for (int row = 1; row <= size; row++) {
        for (char col = 'a'; col <= 'h'; col++) {
            int gridRow = 8 - row + 1;
            grid[row-1][col-'a'] = PieceCreator::createPiece(PieceType::Blank, Colour::Neither, make_pair(col, gridRow));
        }
    }
    for(auto &row : grid) {
        for (auto &piece : row) {
            notifyAllObservers(piece.get(), getTurn());
        }
    }
}

Board& Board::copyBoard() {
    Board newBoard(8);


    // auto& newGrid = newBoard.grid;
    // for (int row = 1; row <= size; row++) {
    //     for (char col = 'a'; col <= 'h'; col++) {
    //         int gridRow = 8 - row + 1;
    //         newGrid[row-1][col-'a'] = PieceCreator::createPiece
    //             (grid[row-1][col-'a'].get()->pieceType(), grid[row-1][col-'a'].get()->getSide(), make_pair(col, gridRow));
    //     }
    // }

    return newBoard;
}

void Board::standardInit() {
    setTurn(Colour::White);

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
    
    Rook * rook = dynamic_cast<Rook*>(grid[7][0].get());
    rook->setMoved(false);
    rook = dynamic_cast<Rook*>(grid[7][7].get());
    rook->setMoved(false);
    rook = dynamic_cast<Rook*>(grid[0][0].get());
    rook->setMoved(false);
    rook = dynamic_cast<Rook*>(grid[0][7].get());
    rook->setMoved(false);

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
    king->setMoved(false);
    grid[7][4] = PieceCreator::createPiece(PieceType::King, Colour::White, make_pair('e', 1));
    king = dynamic_cast<King*>(grid[7][4].get());
    king->notify(king, this);
    king->setMoved(false);

    for(auto &row : grid) {
        for (auto &piece : row) {
            notifyAllObservers(piece.get(), getTurn());
        }
    }
    state = Result::Continue;
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
  
    for(int i = 0; i < size; i++) {
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
    //cout << "Start of playMove(): " << endl;
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

    //cout << "White king is " << (kingw->inCheck() ? "in" : "not in") << " check" << endl;
    //cout << "Black king is " << (kingb->inCheck() ? "in" : "not in") << " check" << endl;
    
    //cout << "------------------------------" << endl;
    if (isPlayableMove(grid[row1][col1].get(), end) == false) return false;
    bool legal = this->playLegalMove(start, end);

    if (!legal)  {
        //cout << "hi" << endl;
        return false;
    }

    if (checkDraw()) {
        state = Result::Draw;
        return true;
    }
    // for (auto s:subject) {
    //     cout << s->getCoords() << endl;
    // }
    
    turn = turn == Colour::White ? Colour::Black : Colour::White;

    notifyAllObservers(getPiece(start), getTurn());   
    notifyAllObservers(getPiece(end), getTurn()); 

    auto king =  dynamic_cast<King*>(getKing(turn)); //find king
    kingw = dynamic_cast<King*>(getKing(Colour::White));
    kingb = dynamic_cast<King*>(getKing(Colour::Black));
    bool isCheck = king->inCheck();  // check if king is in check
    bool checkw = kingw->inCheck();
    bool checkb = kingb->inCheck();
    //cout << kingw->getSide() << " is " << (checkw ? "in" : "not in ") << "check" << endl;
    //cout << kingb->getSide() << " is " << (checkb ? "in" : "not in " ) << "check" << endl;

    bool playableMove = false;
    auto moves = getAllMoves(turn);

    for (auto m : moves) { //iterates through possible moves next player can make
        if(kingIsNotCheck(m.first, m.second)) { //checks if theres a single legal move
            subject = kingw->getSubjects();
            playableMove = true; 
            break;
        }
    }
    if (playableMove == false) { // if there are no legal moves
        if (isCheck == true) state = Result::Win; //if the king is in check other side wins
        else state = Result::Stalemate; //otherwise its stalemate => draw
    }
    
    // //cout << "End of playMove(): " << endl;
    subject = kingw->getSubjects();
    //cout << "   White King Subjects:" << endl;
    for (auto s:subject) {
        //cout << s->getCoords() << endl;
    }

    // kingb = dynamic_cast<King*>(getKing(Colour::Black));
    // subject = kingb->getSubjects();
    // cout << "   Black King Subjects: " << endl;
    // for (auto s:subject){
    //     cout << s->getCoords() << endl;
    // }
    // cout << "------------------------------" << endl;

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
    pair<char, int> thirdCoord = make_pair('0', -1);
    pair<char, int> fourthCoord = make_pair('0', -1);  
    vector<Piece*> ownSubjects; //used to store original observers of white king
    vector<Piece*> oppSubjects; //used to store original observers of black king
    King* ownKing = dynamic_cast<King*> (getKing(turn));
    King* oppKing = dynamic_cast<King*> (getKing(turn == Colour::White ? Colour::Black : Colour::White));
    bool ownInCheck = ownKing->inCheck();
    bool oppInCheck = oppKing->inCheck();
    unique_ptr<Piece> temp; //used to hold pieces in case revert 
    unique_ptr<Piece> temp2; 
    unique_ptr<Piece> temp3;
    unique_ptr<Piece> temp4;   
    bool promotes = false;
    bool enpas = false;
    bool castle = false;
    bool kingMove = getPiece(start)->pieceType() == PieceType::King;
    auto subjects = ownKing->getSubjects();
    King *newKing;

    if(grid[row1][col1]->getSide() != turn) {
        return false; //check if moving piece of own colour
    }  
    if(grid[row2][col2]->getSide() == turn){ 
        return false;
    } //check if capturing own piece

    // checks for promotion, en passant, castling
    promotes = isPromoting(start, end);
    enpas = isEnPas(start, end);
    castle = isCastle(start, end);

    // checks if the starting square is in the subject list of either kings
    bool ownSubjectStart = false;
    bool oppSubjectStart = false;
    bool ownSubjectEnd = false;
    bool oppSubjectEnd = false;
    bool ownSubject3 = false, oppSubject3 = false;
    bool ownSubject4 = false, oppSubject4 = false;
    
    ownSubjects = ownKing->getSubjects();
    oppSubjects = oppKing->getSubjects();


    if(promotes) {
        temp = move(grid[row2][col2]); // stores piece on back rank
        temp2 = move(grid[row1][col1]); // stores old pawn
        grid[row2][col2] = PieceCreator::createPiece(promotionPiece, turn, end);
    } else if (enpas) {
        cout << "ENPASSSANNTTTTTTTTTTTTT!!!!!!!!!!!!!!!!" << endl;
        temp = move(grid[row2][col2]); // store pawn that is going to be captured 
        temp2 = move(grid[row1][col1]); // stores empt that is going to be moved
        grid[row2][col2] = PieceCreator::createPiece(PieceType::Pawn, turn, end);

        //stroes pawn that is going to be taken through en passant
        if (turn == Colour::White) {
            temp3 = move(grid[row1][col2]);
            thirdCoord = make_pair(end.first, start.second);
            grid[row1][col2] = PieceCreator::createPiece(PieceType::Blank, Colour::Neither, thirdCoord);      
        } else {
            temp3 = move(grid[row1][col2]);
            thirdCoord = make_pair(end.first, start.second);
            grid[row1][col2] = PieceCreator::createPiece(PieceType::Blank, Colour::Neither, thirdCoord);    
        }
    
    } else if (castle) {
        if (start.first < start.second) {// moving right 
            if (!kingIsNotCheck(start, make_pair(end.first + 1, end.second))) return false;
        } else {
            if (!kingIsNotCheck(start, make_pair(end.first - 1, end.second))) return false;
        }
        temp = move(grid[row2][col2]); // store the empty square
        temp2 = move(grid[row1][col1]); // store old king
        grid[row2][col2] = PieceCreator::createPiece(PieceType::King, turn, end); 
        if (col2 > col1) {

            temp3 = move(grid[row2][col2 - 1]); //store other empty square
            thirdCoord = make_pair(end.first - 1, end.second);
            grid[row2][col2 - 1] = PieceCreator::createPiece(PieceType::Rook, turn, thirdCoord);

            temp4 = move(grid[row2][size-1]);
            fourthCoord = make_pair('h', end.second);
            grid[row2][size - 1] = PieceCreator::createPiece(PieceType::Blank, Colour::Neither, fourthCoord);
        } else {
            temp3 = move(grid[row2][col2 + 1]); //store other empty square
            thirdCoord = make_pair(end.first + 1, end.second);
            grid[row2][col2 + 1] = PieceCreator::createPiece(PieceType::Rook, turn, thirdCoord);

            temp4 = move(grid[row2][0]);
            fourthCoord = make_pair('a', end.second);
            grid[row2][0] = PieceCreator::createPiece(PieceType::Blank, Colour::Neither, fourthCoord);           
        }
    } else {
        temp = move(grid[row2][col2]); // store piece that is going to be captured 
        temp2 = move(grid[row1][col1]); // stores piece that is going to be moved
        grid[row2][col2] = PieceCreator::createPiece(temp2->pieceType(), turn, end);
    }

    // changes original square to be a blank
    grid[row1][col1] = PieceCreator::createPiece(PieceType::Blank, Colour::Neither, start);

    if (kingMove) { //reupdate observers for king move 
        newKing = dynamic_cast <King*> (grid[row2][col2].get());
        newKing->notify(newKing, this);
        oppKing->notify(oppKing, this); // fix later

    } else {
        for (auto subject:ownSubjects) {
            if (subject->getCoords() == start) ownSubjectStart = true;
            if (subject->getCoords() == end) ownSubjectEnd = true;
            if (subject->getCoords() == thirdCoord) ownSubject3 = true;
        }

        for (auto subject:oppSubjects) {
            if (subject->getCoords() == start) oppSubjectStart = true;
            if (subject->getCoords() == end) oppSubjectEnd = true;
            if (subject->getCoords() == thirdCoord) oppSubject3 = true;     
        }

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

        if (ownSubject3) {
            ownKing->dropSubject(temp3.get());
            ownKing->addSubject(getPiece(thirdCoord));
        }

        if (oppSubject3) {
            oppKing->dropSubject(temp3.get());
            oppKing->addSubject(getPiece(thirdCoord));
        }

        if (ownSubjectStart) ownKing->notify(grid[row1][col1].get(), this);

        if (thirdCoord.second != -1) {
            subjects = ownKing->getSubjects();
            for(Piece* s : subjects) {
                if (s->getCoords() == thirdCoord) ownKing->notify(getPiece(thirdCoord), this);  
            }
        }
        
        subjects = ownKing->getSubjects();
        for(Piece* s : subjects) {
            if (s->getCoords() == end) ownKing->notify(grid[row2][col2].get(), this);    
        }

        //notify king observrs for enemy king   
        if (oppSubjectStart) oppKing->notify(grid[row1][col1].get(), this);

        if (thirdCoord.second != -1) {
            subjects = oppKing->getSubjects();        
            for(Piece* s : subjects) {
                if (s->getCoords() == thirdCoord) oppKing->notify(getPiece(thirdCoord), this); 
            }
        }
        subjects = oppKing->getSubjects();

        for(Piece* s : subjects) {
            if (s->getCoords() == end) oppKing->notify(grid[row2][col2].get(), this);    
        }

    }

    bool isCheckAfter;
    if (kingMove) {
        isCheckAfter = newKing->inCheck();
    } else {
        isCheckAfter = ownKing->inCheck(); // determines if the king is still in check AFTER the move is played
    }

    if (revert || isCheckAfter) { // if reverts or the king is still in check
        if (enpas) {
            grid[row2][col2] = move(temp); // restore orginal move
            grid[row1][col1] = move(temp2);

            //restores pawn that was taken
            if (turn == Colour::White) grid[row2+1][col2] = move(temp3);
            else grid[row2-1][col2] = move(temp3);

        } else if (castle) {
            grid[row2][col2] = move(temp); //becomes empty
            grid[row1][col1] = move(temp2); //becomes king
            if (col2 > col1) {
                grid[row2][col2 - 1] = move(temp3); // becomes empty square 
                grid[row2][size - 1] = move(temp4);
            } else {
                grid[row2][col2 + 1] = move(temp3);
                grid[row2][0] = move(temp4);                
            }
        } else {
            grid[row2][col2] = move(temp); // restore original pieces
            grid[row1][col1] = move(temp2);
        }
        ownKing->setSubjects(ownSubjects);
        oppKing->setSubjects(oppSubjects);
        ownKing->setCheck(ownInCheck);
        oppKing->setCheck(oppInCheck);
        if (revert) { return !isCheckAfter; }
        else return false;
    }
    
    Piece* movedPiece = getPiece(end);

    //set moved for rook to be true
    if (movedPiece->pieceType() == PieceType::Rook) dynamic_cast<Rook*>(movedPiece)->hasMoved();

    // disable enpas not sure if works
    for(auto &row : grid) {
        for (auto &piece : row) {
            if (piece->pieceType() == PieceType::Pawn) {
                auto p = dynamic_cast<Pawn*>(piece.get());
                p->setEnPas(false);
            }
        }
    }


    if (movedPiece->pieceType() == PieceType::Pawn) {
        auto p = dynamic_cast<Pawn*>(movedPiece);

        p->setMoveTwo(false);

        if (row1 + 2 == row2 || row1 - 2 == row2) {
            p->setEnPas(true);
            cout << "true" << endl;
        }
    }

    if (castle) {
        notifyAllObservers(getPiece(thirdCoord), getTurn());
        notifyAllObservers(getPiece(fourthCoord), getTurn());
    }

    if (enpas) {
        notifyAllObservers(getPiece(thirdCoord), getTurn());

    }
    return true; //if reverting the board is not requested and that its a legal move return true

}

bool Board::isPromoting(pair<char, int> start, pair<char, int> end) {
    int col1 = start.first - 'a';
    int row1 = size - start.second;
    

    if (grid[row1][col1]->pieceType() == PieceType::Pawn) {
        if (grid[row1][col1]->getSide() == Colour::White && row1 == 1) return true;
        if (grid[row1][col1]->getSide() == Colour::Black && row1 == 6) return true;
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

void Board::notifyAllObservers(const Piece* p, Colour turn) const {
  for (Observer *observer : observers) {
      if (observer->getSubscription() == Subscription::All) { 
          observer->notify(p, turn);
      }
  }
}
