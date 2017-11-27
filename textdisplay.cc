#include "textdisplay.h"
#include "info.h"
#include "subject.h"
#include <iostream>

using namespace std;

TextDisplay::TextDisplay(int n): gridSize{n} {
    for (int y = 0; y < gridSize; y++) { // y coordinate
        vector<char> row;
        for (int x = 0; x < gridSize; x++) { // x coordinate
            row.emplace_back('-'); 
        }
        theDisplay.emplace_back(row);
    }
}

void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    if (whoNotified.getInfo().colour == Colour::Black) {
        theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'B';
    } else if (whoNotified.getInfo().colour == Colour::White) {
        theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'W';
    }
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int y = 0; y < td.gridSize; y++) { // y coordinate
        for (int x = 0; x < td.gridSize; x++) { // x coordinate
            out << td.theDisplay[y][x];
        }
        out << endl;
    }
    return out;
}
