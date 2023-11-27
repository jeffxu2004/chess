#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>

class Subject;

enum class Subcription { All, King };

class Observer {
public:
    virtual ~Observer() = default;
    virtual void notify(const Subject *item) = 0;
    virtual Subscription getSubscription() = 0;
};

#endif
