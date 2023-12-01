#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Subject;
class Board;

enum class Subscription { All, King };

class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(const Subject* item) = 0;
    virtual void notify(const Subject* item, const Board* b) = 0;
    virtual Subscription getSubscription() const = 0;
};

#endif
