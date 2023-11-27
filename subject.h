#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "observer.h"

class Subject {
private:
	std::vector<Observer*> observers;
public:
    virtual void attach(Observer *observer) = 0;
    virtual void detach(Observer *observer) = 0;
    virtual void notifyObservers() = 0;
	~Subject() = default;
};

#endif
