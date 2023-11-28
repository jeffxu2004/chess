#include <vector>
#include <utility>
#include "piece.h"
#include "observer.h"

using namespace std;

class Board;

class King: public Piece, public Observer {
	<vector<Piece*>> subjects;
	
public:
	King(); // ctor
	
	// returns the subscription of king
	Subscription getSubscription const();
	
	// adds a
	void addSubject(Subject *);
	void dropSubject(Subject *);
	<vector<pair<char, int>> getMoves(Board &b) const;
	PieceType pieceType() const;
};
