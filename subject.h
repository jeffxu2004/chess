#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

enum class PieceType { Pawn, Knight, Bishop, Rook, Queen, King, Blank };

class Subject {
protected:
	std::vector<Observer*> observers;
public:
    virtual void attach(Observer *observer) = 0;
    virtual void detach(Observer *observer) = 0;
    int observerLength() { return observers.size(); }
    virtual void notifyAllObservers(Subject* s) = 0;
	~Subject() = default;
};

#endif
