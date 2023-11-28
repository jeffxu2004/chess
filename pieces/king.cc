#include "king.h"
#include <vector>
#include <utility>

using namespace std;

King::King(int weight, Colour side): Piece(weight, side) {}

vector<pair<char, int>> King::getMoves(Board &b) const{
	pair<char,int> current = getCoords();
	vector<pair<char,int>> moves = {
		pair<char,int> (current.first+'a'-'b', current.second),
		pair<char,int> (current.first+'a'-'b', current.second+1),
		pair<char,int> (current.first+'a'-'b', current.second-1),
		pair<char,int> (current.first+'b'-'a', current.second),
		pair<char,int> (current.first+'b'-'a', current.second+1),
		pair<char,int> (current.first+'b'-'a', current.second-1),
		pair<char,int> (current.first, current.second+1),
		pair<char,int> (current.first, current.second-1)
	};


	if (canCastle()) {
		
	}
}
