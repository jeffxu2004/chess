#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include "enumClasses.h"

class Board;
class Piece;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(const Piece* item, Colour turn) = 0;
    virtual void notify(const Piece* item, const Board* b) = 0;
    virtual Subscription getSubscription() const = 0;
};

#endif
