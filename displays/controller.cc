#include "controller.h"
#include <memory>

using namespace std;

Controller::Controller(int n) {
    td = make_unique<TextDisplay>(n);
    gd = make_unique<GraphicsDisplay>(n);
}

Subscription Controller::getSubscription() const { return Subscription::All; }

void Controller::notify(const Piece *item) {
    td->update(item);
    gd->update(item);
}

TextDisplay& Controller::getTd() { return *td; }

GraphicsDisplay& Controller::getGd() { return *gd; }