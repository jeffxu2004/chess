#include <iostream>
#include <string>
#include <vector>
#include "../subject.h"

using namespace std;

class TextDisplay {
    vector<vector<char>> display;
    int gridSize;
    
public:
    TextDisplay(int n);
    void update(const Subject* item);
    friend ostream& operator<<(ostream& out, const TextDisplay& td);
};