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

void TextDisplay::setHoldPiece(vector<vector<char>> holdPiece) {
    this->holdPiece = holdPiece;
}

void TextDisplay::setScore(int score) {
  this->score = score;
}

void TextDisplay::setHighScore(int highScore) {
  this->highScore = highScore;
}

void TextDisplay::enhancementsOn() {
    runEnhancement = true;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    out << endl;
    out << "Level: " << td.level << endl;
    out << "Score: " << td.score << endl;
    out << "Hi Score: " << td.highScore << endl;
    for (int i = 0; i < td.c; i++) {
        out << "-";
    }
    out << endl;
    for (int i = 3; i < td.r; i++) { // y coordinate
        for (int j = 0; j < td.c; j++) { // x coordinate
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    for (int i = 0; i < td.c; i++) {
        out << "-";
    }
    out << endl;
    out << "Next: " << endl;
    for (int i = 0; i < td.nextPiece.size(); i++) {
        for (int j = 0; j < td.nextPiece[i].size(); j++) {
            out << td.nextPiece[i][j];
        }
        out << endl;
    }
    if (td.runEnhancement) {
        out << "Hold: " << endl;
        for (int i = 0; i < td.holdPiece.size(); i++) {
            for (int j = 0; j < td.holdPiece[i].size(); j++) {
                out << td.holdPiece[i][j];
            }
            out << endl;
        }
    }
    return out;
}

