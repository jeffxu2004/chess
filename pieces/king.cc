#include "king.h"
#include <vector>
#include <utility>
#include <memory>
#include "../board.h"

using namespace std;


King::King(int weight, Colour side, pair<char,int> coords): Piece {weight, side, coords} {}

vector<pair<char, int>> King::getMoves(const Board& b) const{
	pair<char,int> current = getCoords();
	vector<pair<char,int>> moves = {
		// move left
		pair<char,int> (current.first+'a'-'b', current.second),
		pair<char,int> (current.first+'a'-'b', current.second+1),
		pair<char,int> (current.first+'a'-'b', current.second-1),
		
		// move right
		pair<char,int> (current.first+'b'-'a', current.second),
		pair<char,int> (current.first+'b'-'a', current.second+1),
		pair<char,int> (current.first+'b'-'a', current.second-1),

		// move up and down
		pair<char,int> (current.first, current.second+1),
		pair<char,int> (current.first, current.second-1)
	};
	
	vector<Piece*> subjects = getSubjects();

	if (!hasMoved() && !inCheck()) {
		if (getSide() == Colour::White){
			for (Piece* piece:subjects) {
				if (piece->pieceType() == PieceType::Rook) {
					Rook* rook = dynamic_cast<Rook *>(piece);
					if (rook->hasMoved())
						continue;

					if (piece->getCoords().first == 'a')
						moves.emplace_back(current.first+'a'-'c', current.second);
					if (piece->getCoords().first == 'h')
						moves.emplace_back(current.first+'c'-'a', current.second);
				}
			}
		} if (getSide() == Colour::Black) {
			for (Piece* piece:subjects) {
				if (piece->pieceType() == PieceType::Rook) {
					Rook* rook = dynamic_cast<Rook *>(piece);
					if (rook->hasMoved())
						continue;

					if (piece->getCoords().first == 'a')
						moves.emplace_back(current.first+'a'-'c', current.second);
					if (piece->getCoords().first == 'h')
						moves.emplace_back(current.first+'c'-'a', current.second);
				}
			}
		}
	}

	vector<vector<Piece *>> grid = b.getGrid();
	
	for (auto it=moves.begin(); it !=moves.end(); ++it) {
		if (it->first < 'a' || it->first > 'h')
			moves.erase(it);
		else if (it->second < 1 || it->second > 8)
			moves.erase(it);
		else if (grid[8-it->second][int(it->first-'a')]->getSide() == getSide())
			moves.erase(it);
	}

	return moves;
}

PieceType King::pieceType() const { return PieceType::King; }

Subscription King::getSubscription() const { return Subscription::King; }

void King::notify(const Piece* item, const Board* b) {
	char kingCol = int(getCoords().first - 'a');
	int kingRow = 8 - getCoords().second;

	vector<pair<int,int>> knightSquares = {
		make_pair(kingCol-1, kingRow-2),
		make_pair(kingCol-1, kingRow+2),
		make_pair(kingCol+1, kingRow-2),
		make_pair(kingCol+1, kingRow+2),
		make_pair(kingCol-2, kingRow+1),
		make_pair(kingCol-2, kingRow-1),
		make_pair(kingCol+2, kingRow+1),
		make_pair(kingCol+2, kingRow-1)
	};

	const Piece* piece = dynamic_cast<const Piece*> (item);
	const vector<vector<Piece *>> grid = b->getGrid();
	
	int row = 8 - piece->getCoords().second;
	int col = int(piece->getCoords().first - 'a');
	
	if (piece->pieceType() == PieceType::Blank) { // if the square is calling notify because a piece moved away from it
		for (auto coord:knightSquares) {
			if (coord.first == int(piece->getCoords().first-'a') && coord.second == 8-piece->getCoords().second) {
				return;
			}
		}
		
		// if the piece is in the same column then add pieces to subject until 
		// the next non-blank piece is reached 
		if (col == kingCol) {
			if (row == 0 || row == 7)
				return;

			if (kingRow > row) {
				do {
					addSubject(grid[row-1][kingCol]);
					--row;
				} while (row > 0 && grid[row-1][kingCol]->pieceType() == PieceType::Blank);
				
				if (row > 0)
					addSubject(grid[row-1][kingCol]);
			} else {
				do {
					addSubject(grid[row+1][kingCol]);
					++row;
				} while (row < 7 && grid[row+1][kingCol]->pieceType() == PieceType::Blank);

				if (row < 7)
					addSubject(grid[row+1][kingCol]);
			}

		} else if (row == kingRow) { // if the piece is in the same row
			if (col == 0 || col == 7)
				return;
			
			if (kingCol > col) {
				do {
					addSubject(grid[kingRow][col-1]);
					--col;
				} while (col > 0 && grid[kingRow][col-1]->pieceType() == PieceType::Blank);

				if (col > 0)
					addSubject(grid[kingRow][col-1]);
			} else {
				do {
					addSubject(grid[kingRow][col+1]);
					++col;
				} while (col < 7 && grid[kingRow][col+1]->pieceType() == PieceType::Blank);

				if (col < 7) 
					addSubject(grid[kingRow][col+1]);
			}
		} else { // if it reaches here, then the piece must belong on a diagonal that the king is observing
			if (col == 0 || col == 7 || row == 0 || row == 7)
				return;

			if (col > kingCol && row > kingRow) {
				do {
					addSubject(grid[row+1][col+1]);
					++row;
					++col;
				} while (row < 7 && col < 7 && grid[row+1][col+1]->pieceType() == PieceType::Blank);

				if (row < 7 && col < 7)
					addSubject(grid[row+1][col+1]);

			} else if (col > kingCol) {
				do {
					addSubject(grid[row-1][col+1]);
					--row;
					++col;
				} while (row > 0 && col < 7 && grid[row-1][col+1]->pieceType() == PieceType::Blank);

				if (row > 0 && col < 7) 
					addSubject(grid[row-1][col+1]);
			} else if (row > kingRow) {
				do {
					addSubject(grid[row+1][col-1]);
					++row;
					--col;
				} while (row < 7 && col > 0 && grid[row+1][col-1]->pieceType() == PieceType::Blank);

				if (row < 7 && col > 0)
					addSubject(grid[row+1][col-1]);
			} else {
				do {
					addSubject(grid[row-1][col-1]);
					--row;
					--col;
				} while (row > 0 && col > 0 && grid[row-1][col-1]->pieceType() == PieceType::Blank);
				if (row > 0 && col > 0)
					addSubject(grid[row-1][col-1]);
			}
		}	
	} else if (piece != this) { // if the square calling notify is a piece moving into it and that piece is not the king itself
		if (kingCol == col) {
			if (kingRow > row) {
				for (auto pieceIt=subjects.begin(); pieceIt!=subjects.end();) {
					int pieceCol = (*pieceIt)->getCoords().first - 'a';
					int pieceRow = 8 - (*pieceIt)->getCoords().second;

					if (pieceCol == kingCol && pieceRow < row)
						subjects.erase(pieceIt);
					else
						++pieceIt;
				}

			} else {
				for (auto pieceIt=subjects.begin(); pieceIt!=subjects.end();) {
					int pieceCol = (*pieceIt)->getCoords().first - 'a';
					int pieceRow = 8 - (*pieceIt)->getCoords().second;

					if (pieceCol == kingCol && pieceRow > row)
						subjects.erase(pieceIt);
					else
						++pieceIt;
				}
			}

		} else if (kingRow == row) {
			if (kingCol > col) {
				for (auto pieceIt=subjects.begin(); pieceIt!=subjects.end();) {
					int pieceCol = (*pieceIt)->getCoords().first - 'a';
					int pieceRow = 8 - (*pieceIt)->getCoords().second;

					if (pieceRow == kingRow && pieceCol < col)
						subjects.erase(pieceIt);
					else
						++pieceIt;
				}
			} else {
				for (auto pieceIt=subjects.begin(); pieceIt!=subjects.end();) {
					int pieceCol = (*pieceIt)->getCoords().first - 'a';
					int pieceRow = 8 - (*pieceIt)->getCoords().second;

					if (pieceRow == kingRow && pieceCol > col)
						subjects.erase(pieceIt);
					else
						++pieceIt;
				} 
			}

		} else { // then the piece is on the diagonal that the king observes
			if (col > kingCol && row > kingRow) {
				for (auto pieceIt=subjects.begin(); pieceIt!=subjects.end();) {
					int pieceCol = (*pieceIt)->getCoords().first - 'a';
					int pieceRow = 8 - (*pieceIt)->getCoords().second;

					if (pieceRow > row && pieceRow-row == pieceCol-col) 
						subjects.erase(pieceIt);
					else
						++pieceIt;
				}
			} else if (col > kingCol) {
				for (auto pieceIt=subjects.begin(); pieceIt!=subjects.end();) {
					int pieceCol = (*pieceIt)->getCoords().first - 'a';
					int pieceRow = 8 - (*pieceIt)->getCoords().second;

					if (row > pieceRow && row-pieceRow == pieceCol-col)
						subjects.erase(pieceIt);
					else
						++pieceIt;
				}
			} else if (row > kingRow) {
				for (auto pieceIt=subjects.begin(); pieceIt!=subjects.end();) {
					int pieceCol = (*pieceIt)->getCoords().first - 'a';
					int pieceRow = 8 - (*pieceIt)->getCoords().second;

					if (row < pieceRow && pieceRow-row == col-pieceCol)
						subjects.erase(pieceIt);
					else
						++pieceIt;
				}
			} else {
				for (auto pieceIt=subjects.begin(); pieceIt!=subjects.end();) {
					int pieceCol = (*pieceIt)->getCoords().first - 'a';
					int pieceRow = 8 - (*pieceIt)->getCoords().second;

					if (row-pieceRow == col-pieceRow && row > pieceRow)
						subjects.erase(pieceIt);
					else
						++pieceIt;
				}
			}
		}
	} else { // if the king move
		for (auto coords:knightSquares) {
			if (coords.first >= 0 && coords.first <= 7 && coords.second >= 0 && coords.second <= 7) {
				addSubject(grid[coords.first][coords.second]);
			}
		}

		int inc = 1;
		while (kingRow-inc >= 0) {
			Piece *up = grid[kingRow-inc][kingCol];
			addSubject(up);

			if (up->pieceType() != PieceType::Blank) break;
		
			++inc;
		}

		inc = 1;

		while (kingRow+inc <= 7) {
			Piece *down = grid[kingRow+inc][kingCol];
			addSubject(down);

			if (down->pieceType() != PieceType::Blank) break;

			inc++;
		}

		inc = 1;

		while (kingCol-inc >= 0) {
			Piece *left = grid[kingRow][kingCol-inc];
			addSubject(left);

			if (left->pieceType() != PieceType::Blank) break;
	
			++inc;
		}

		inc = 1;

		while (kingCol+inc <= 7) {
			Piece *right = grid[kingRow][kingCol-inc];
			addSubject(right);

			if (right->pieceType() != PieceType::Blank) break;
			
			++inc;
		}

		inc = 1;

		while (kingCol-inc >= 0 && kingRow-inc >= 0) {
			Piece *upLeft = grid[kingRow-inc][kingCol-inc];
			addSubject(upLeft);

			if (upLeft->pieceType() != PieceType::Blank) break;

			++inc;
		}

		inc = 1;

		while (kingCol-inc >= 0 && kingRow+inc <= 7) {
			Piece *downLeft = grid[kingRow-inc][kingCol+inc];
			addSubject(downLeft);
			
			if (downLeft->pieceType() != PieceType::Blank) break;
			++inc;
		}

		inc = 1;

		while (kingCol+inc <= 7 && kingRow-inc >= 0) {
			Piece *upRight = grid[kingCol+inc][kingRow-inc];
			addSubject(upRight);

			if (upRight->pieceType() != PieceType::Blank) break;

			++inc;
		}

		inc = 1;

		while (kingCol+inc <= 7 && kingRow+inc <= 7) {
			Piece *downRight = grid[kingCol+inc][kingRow+inc];
			addSubject(downRight);

			if (downRight->pieceType() != PieceType::Blank) break;

			++inc;
		}
	}
	
	check = false;

	// Check if the king is in check
	for(auto subject:subjects) {
		if (subject->pieceType() != PieceType::Blank && 
			subject->getSide() != getSide()) {
			int pieceCol = int(subject->getCoords().first-'a');
			int pieceRow = 8 - subject->getCoords().second;

			if ((subject->pieceType() == PieceType::Rook || 
				subject->pieceType() == PieceType::Queen) &&
				(pieceCol == kingCol || pieceRow == kingRow)) {
				check = true;
			} else if ((subject->pieceType() == PieceType::Bishop ||
				subject->pieceType() == PieceType::Queen) &&
				(pieceCol-kingCol == pieceRow-kingRow || 
				pieceCol-kingCol == kingRow-pieceRow)) {
				check = true;
			} else if (subject->pieceType() == PieceType::Pawn) {
				if (getSide() == Colour::Black &&
					kingRow+1 == pieceRow &&
					(kingCol-1 == pieceCol || kingCol+1 == pieceCol)) {
					check = true;
				} else if (kingRow-1 == pieceRow &&
					(kingCol-1 == pieceCol || kingCol+1 == pieceCol)) {
					check = true;
				}
			} else if (subject->pieceType() == PieceType::Knight && 
				pieceCol != kingCol && pieceRow != kingRow && 
				(pieceCol-kingCol == pieceRow-kingRow ||
				pieceCol-kingCol == kingRow-pieceRow)) {
				check = true;
			}
		}
	}
}

vector<Piece*> King::getSubjects() const { return subjects; }

void King::addSubject(Piece* subject) { 
	subjects.push_back(subject); 
}

void King::dropSubject(Piece* subject) { 
	for (auto pieceIt=subjects.begin(); pieceIt != subjects.end(); ++pieceIt) {
		if (*pieceIt == subject) {
			subjects.erase(pieceIt);
			return;
		}
	}
}

bool King::inCheck() const { return check; }

void King::setCheck(bool check) { this->check = check; }

bool King::hasMoved() const { return moved; }

void King::setMoved(bool move) { moved = move; }

bool King::justCastled() const { return hasCastled; }

void King::setCastled(bool castle) { hasCastled = castle; }
