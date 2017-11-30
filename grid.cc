#include <vector>
#include <iostream>
#include <vector>
#include <exception>
#include <memory>
#include "grid.h"
#include "cell.h"
#include "info.h"
#include "piece.h"
#include "textdisplay.h"
#include "level.h"

using namespace std;

void Grid::setTextDisplay(shared_ptr<TextDisplay> td) {
    this->td = td;
}

bool Grid::isGameOver() const {
    return false;
}

void Grid::init(int r, int c) {
    rows = r;
    cols = c;
    theGrid.clear();
    for (int i = 0; i < r; i++) { // Generate Rows
        vector<Cell> row;
        for (int j= 0; j < c; j++) { // Generate Columns
            Cell cell{i, j, '-'};
            cell.attach(td);
            row.emplace_back(cell);
        }
        theGrid.emplace_back(row);
    }
    setPiece(currPiece);
}

void Grid::setPiece(Piece piece) {
    for (int i = 0; i < piece.getCoords().size(); i++) {
        int r = piece.getCoords()[i][0];
        int c = piece.getCoords()[i][1];
        theGrid[r][c].setData(piece.getType());
    }
}

void Grid::checkPiece(Piece piece) {
    int r, c;
    unsetPiece(piece);
    // Checks if potential coords are occupied or not first
    for (int i = 0; i < piece.getPotentialCoords().size(); i++) {
        r = piece.getPotentialCoords()[i][0];
        c = piece.getPotentialCoords()[i][1];
        if (r < 0 || c < 0 || r >= rows || c >= cols || theGrid[r][c].getInfo().data != '-') {
            throw out_of_range("Boundary");
        }
    }
}

void Grid::unsetPiece(Piece piece) {
  for (int i = 0; i < piece.getCoords().size(); i++) {
    int r = piece.getCoords()[i][0];
    int c = piece.getCoords()[i][1];
    theGrid[r][c].setData('-');
  }
}

void Grid::pieceCommand(string cmd) {
    if (cmd == "down") {
        currPiece.down();
    } else if (cmd == "clockwise") { 
        currPiece.rotateCW();
    } else if (cmd == "counterclockwise") {
        currPiece.rotateCCW();
    } else if (cmd == "drop") {
        // Call down until it throws an exception
        while (true) {
            currPiece.down();
            try {
                checkPiece(currPiece);
                currPiece.set();
                setPiece(currPiece);
            } catch (out_of_range) {
                setPiece(currPiece);
                currPiece.revert();
                break;
            }
        }
        cout << *this;
        return;
    }
    try {
        checkPiece(currPiece);
        currPiece.set();
        setPiece(currPiece);
    } catch (out_of_range) {
        setPiece(currPiece);
        currPiece.revert();
    }
    cout << *this;
}

void Grid::levelUp() {}

void Grid::levelDown() {}

void Grid::noRandom(std::string file) {}

void Grid::random() {}

void Grid::sequence(std::string file) {}

void Grid::replacePieceWith(char type) {}

void Grid::restart() {}

void Grid::hint() {}

std::ostream& operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
