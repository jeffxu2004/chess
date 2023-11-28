#include <vector>
#include <utility>
#include "piece.h"
#include "observer.h"

using namespace std;

class Board;

class King: public Piece, public Observer {
	// tracks the subjects that the king is observing to make it easier to determine the
	// legality of a move when the king is in check
	<vector<Piece*>> subjects;
	
public:
	King(int weight, Colour side); // ctor
	~King() override = default; // dtor
	
	// Overrides from Piece:	
	<vector<pair<char, int>> getMoves(Board &b) const override;

	PieceType pieceType() const override;


	// Overrides from Observer:
	Subscription getSubscription const();
	
	void notify(const Subject *item) override;


	// Accessors and Mutators
	// returns a vector of the subjects that the king is observing	
	<vector<Piece*>> getSubjects() const;
	
	// appends a subject to the end of the vector
	void addSubject(Subject *);

	// removes subject from subjects
	void dropSubject(Subject *);
};
