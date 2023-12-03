#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../observer.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include <memory>

class Controller: public Observer {
    unique_ptr<TextDisplay> td;
    unique_ptr<GraphicsDisplay> gd;
public:
    Controller(int n);
    Subscription getSubscription() const override;
    void notify(const Piece *item, Colour turn) override;
    void notify(const Piece *item, const Board* b) override {};
    TextDisplay& getTd();
    GraphicsDisplay& getGd();
};

#endif