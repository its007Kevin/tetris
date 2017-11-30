#include "textdisplay.h"
#include "subject.h"
#include <iostream>

using namespace std;

TextDisplay::TextDisplay(int r, int c): r{r}, c{c} {
    for (int i = 0; i < r; i++) { // creates r rows
        vector<char> row;
        for (int j = 0; j < c; j++) { // creates c columns
            row.emplace_back('-'); 
        }
        theDisplay.emplace_back(row);
    }
}

void TextDisplay::notify(Subject &whoNotified) {
    int r = whoNotified.getInfo().row;
    int c = whoNotified.getInfo().col;
    theDisplay[r][c] = whoNotified.getInfo().data;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    out << "Level: " << endl;
    out << "Score: " << endl;
    out << "Hi Score: " << endl;
    out << "-----------" << endl; 
    out << endl;
    for (int i = 3; i < td.r; i++) { // y coordinate
        for (int j = 0; j < td.c; j++) { // x coordinate
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    out << endl;
    out << "-----------" << endl;
    out << "Next: " << endl;
    return out;
}
