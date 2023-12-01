#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Board;
class Piece;

enum class Subscription { All, King };

class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(const Piece* item) = 0;
    virtual void notify(const Piece* item, const Board* b) = 0;
    virtual Subscription getSubscription() const = 0;
};

#endif
