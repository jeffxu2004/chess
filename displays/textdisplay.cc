#include "textdisplay.h"
#include "../piececreator.h"

TextDisplay::TextDisplay(int n): gridSize{n} {
    vector<vector<char>> board;
    vector<char> row;
    for (int i=0; i<n; ++i) {
        if (i % 2 == 0) {
            for (int j=0; j<n; ++j) {
                if (j % 2 == 0)
                    row.push_back(' ');
                else
                    row.push_back('_');
            }
        } else {
            for (int j=0; j<n; ++j) {
                if (j % 2 == 0)
                    row.push_back('_');
                else   
                    row.push_back(' ');
            }
        }

        board.push_back(row);
        row.clear();
    }
}

void TextDisplay::update(const Piece* item) {
    const Piece* piece = dynamic_cast<const Piece*>(item);

    int row = 8 - piece->getCoords().second;
    int col = int(piece->getCoords().first - 'a');

    bool isDark = (row % 2 == 0) && (col % 2 == 1);

    display[row][col] = PieceCreator::createPiece(piece->pieceType(), piece->getSide(), isDark);
}

ostream& operator<<(ostream& out, const TextDisplay& td) {
    int width = td.gridSize;

    // print top border
    out << "  ";
    for (int i=0; i<width; ++i) {
        out << "-";
    }
    out << endl;

    // print rows
    for (int i=0; i<width; ++i) {
        out << i << " |";
        for (int j=0; j<width; ++j) {
            out << td.display[i][j];
        }
        out << "|";
        out << endl;
    }

    // print bottom border
    out << "  ";
    for (int i=0; i<width; ++i) {
        out << "-";
    }
    out << endl;

    // print column labels
    for (int i=0; i<width; ++i) {
        out << ('a' + i) << endl;
    }

    return out;

}