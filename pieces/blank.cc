#include "blank.h"
#include "../board.h"

Blank::Blank(int weight = 0, Colour side, pair<char, int> coords) : weight{weight}, Colour{colour}, coords{coords} {}

vector<pair<char,int>> Blank::getMoves(Board &b) const override {
	return vector<pair<char,int>>();
}

PieceType Blank::pieceType() const { return PieceType::None; }
int Blank::getWeight() const { return this->weight; }
Colour Blank::getSide() const { return this->colour; }
pair<char, int> Blank::getCoords() const { return this->coords; }
void Blank::setCords(pair<char, int> coords) { this->coords = coords; }
