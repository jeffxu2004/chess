#include "king.h"
#include "rook.h"
#include <vector>
#include <utility>
#include <memory>

using namespace std;

King::King(int weight, Colour side, pair<char,int> coords): Piece {weight, side, coords} {}

vector<pair<char, int>> King::getMoves(Board &b) const{
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
					if (!rook->hasMoved())
					if (piece->getCoords().first == 'a')
						moves.emplace_back(current.first+'a'-'c', current.second);
					if (piece->getCoords().first == 'h')
						moves.emplace_back(current.first+'c'-'a', current.second);
				}
			}
		} if (getSide() == Colour::Black) {
			for (Piece* piece:subjects) {
				if (piece->pieceType() == PieceType::Rook &&
					!piece->hasMoved()) {
					if (piece->getCoords().first == 'a')
						moves.emplace_back(current.first+'a'-'c', current.second);
					if (piece->getCoords().first == 'h')
						moves.emplace_back(current.first+'c'-'a', current.second);
				}
			}
		}
	}

	vector<vector<unique_ptr<Piece>>> grid = b.getGrid();
	
	for (auto it=moves.begin(); it !=moves.end(); ++it) {
		if (it->first < 'a' || it->getCofirst > 'h')
			moves.erase(it);
		else if (it->second < 1 || it->second > 8)
			moves.erase(it);
		else if (grid[8-it->second][it->first-'a']->pieceType != PieceType::Blank)
			moves.erase(it);
	}

	return moves;
}

PieceType King::pieceType() const { return PieceType::King; }

Subscription getSubscription() const { return Subscription::King; }

void King::notify(const Subject *item) {
	
}

vector<Subject*> getSubjects() const { return subjects; }

void King::addSubject(Piece* subject) { moves.push_back(subject); }

void King::dropSubject(Piece* subject) { moves.erase(subject); }

bool King::inCheck() const { return check; }

bool King::hasMoved() const { return moved; }

bool King::justCastled() const { return hasCastled; }
