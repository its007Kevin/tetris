#include "textdisplay.h"
#include "subject.h"
#include <iostream>

using namespace std;

TextDisplay::TextDisplay(int r, int c): r{r}, c{c} {
    for (int i = 0; i < r; i++) { // creates r rows
        vector<char> row;
        for (int j = 0; j < c; j++) { // creates c columns
            row.emplace_back(' '); 
        }
        theDisplay.emplace_back(row);
    }
}

void TextDisplay::notify(Subject &whoNotified) {
    int r = whoNotified.getInfo().row;
    int c = whoNotified.getInfo().col;
    theDisplay[r][c] = whoNotified.getInfo().data;
}

void TextDisplay::setLevel(int level) {
    this->level = level;
}

void TextDisplay::setNextPiece(vector<vector<char>> nextPiece) {
    this->nextPiece = nextPiece;
}

vector<vector<char>> TextDisplay::getNextPiece() const {
    return nextPiece;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    out << endl;
    out << "Level: " << td.level << endl;
    out << "Score: " << endl;
    out << "Hi Score: " << endl;
    out << "-----------" << endl; 
    for (int i = 3; i < td.r; i++) { // y coordinate
        for (int j = 0; j < td.c; j++) { // x coordinate
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    out << "-----------" << endl;
    out << "Next: " << endl;
    for (int i = 0; i < td.getNextPiece().size(); i++) {
        for (int j = 0; j < td.getNextPiece()[i].size(); j++) {
            out << td.getNextPiece()[i][j];
        }
        out << endl;
    }
    return out;
}
