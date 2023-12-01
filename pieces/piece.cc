#include "piece.h"
#include <vector>
#include <utility>

using namespace std;

Piece::Piece(int weight, Colour side, pair<char,int> coords):
    weight {weight}, side {side}, coords {coords} {}

int Piece::getWeight() const { return weight; }

Colour Piece::getSide() const { return side; }

pair<char,int> Piece::getCoords() const { return coords; }

void Piece::setCoords(pair<char,int> coords) { this->coords = coords; }

bool Piece::operator==(Piece* other) {
    return getCoords() == other->getCoords();
}