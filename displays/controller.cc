#include "controller.h"
#include <memory>

using namespace std;

Controller::Controller(int n) {
    td = make_unique<TextDisplay>(n);
    gd = make_unique<GraphicsDisplay>(n);
}

Subscription Controller::getSubscription() const { return Subscription::All; }

void Controller::notify(const Subject *item) {
    td->update(item);
    // gd->update(item);
}