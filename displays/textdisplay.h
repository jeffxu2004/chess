#include <iostream>
#include <string>
#include <vector>

using namespace std;

class TextDisplay {
    vector<vector<char>> display;
    int gridSize;
    
public:
    TextDisplay(int n);
    void update(const Piece* item);
    friend ostream& operator<<(ostream& out, const TextDisplay& td);
};