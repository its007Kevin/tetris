#include <vector>
#include <iostream>
#include <exception>
#include <memory>
#include "grid.h"
#include "cell.h"
#include "info.h"
#include "piece.h"
#include "textdisplay.h"
#include "level.h"
#include "collision.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"

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
    for (int i = 0; i < r; i++) {
        vector<Cell> row;
        for (int j= 0; j < c; j++) {
            Cell cell{i, j, '-'};
            cell.attach(td);
            row.emplace_back(cell);
        }
        theGrid.emplace_back(row);
    }
    setPiece(currPiece);
}

void Grid::down() {
    currPiece.down();
    try {
        checkPiece(currPiece);
        currPiece.set();
        setPiece(currPiece);
    } catch (out_of_range) {
        setPiece(currPiece);
        currPiece.revert();
    } catch (Collision) {
        setPiece(currPiece);
        currPiece.revert();
        spawnNextPiece();
    }
    cout << *this;
}

void Grid::left() {
    currPiece.left();
    tryPlace();
}

void Grid::right() {
    currPiece.right();
    tryPlace();
}

void Grid::rotateCW() {
    currPiece.rotateCW();
    tryPlace();
}

void Grid::rotateCCW() {
    currPiece.rotateCCW();
    tryPlace();
}

void Grid::drop() {
    while (true) {
        currPiece.down();
        try {
            checkPiece(currPiece);
            currPiece.set();
            setPiece(currPiece);
        } catch (Collision) {
            setPiece(currPiece);
            currPiece.revert();
            spawnNextPiece();
            break;
        }
    }
    cout << *this;
}

void Grid::tryPlace() {
    try {
        checkPiece(currPiece);
        currPiece.set();
        setPiece(currPiece);
        if (currPiece.checkHeavy()) {
          down();
        }
    } catch (out_of_range) {
        setPiece(currPiece);
        currPiece.revert();
    } catch (Collision) {
        setPiece(currPiece);
        currPiece.revert();
    }
    cout << *this;
}

void Grid::checkPiece(Piece piece) {
    int r, c;
    unsetPiece(piece);
    // Checks if potential coords are occupied or not first
    for (int i = 0; i < piece.getPotentialCoords().size(); i++) {
        r = piece.getPotentialCoords()[i][0];
        c = piece.getPotentialCoords()[i][1];
        if (r < 0 || c < 0 || c >= cols) {
            throw out_of_range("boundary");
        } else if (r >= rows || theGrid[r][c].getInfo().data != '-') {
            throw Collision();
        }
    }
}

void Grid::setPiece(Piece piece) {
    for (int i = 0; i < piece.getCoords().size(); i++) {
        int r = piece.getCoords()[i][0];
        int c = piece.getCoords()[i][1];
        theGrid[r][c].setData(piece.getType());
    }
}

void Grid::unsetPiece(Piece piece) {
  for (int i = 0; i < piece.getCoords().size(); i++) {
    int r = piece.getCoords()[i][0];
    int c = piece.getCoords()[i][1];
    theGrid[r][c].setData('-');
  }
}

void Grid::spawnNextPiece() {
    currPiece = currLevel->generatePiece();
    if (levelCount == 3 || levelCount == 4) {
      currPiece.makeHeavy();
    } else {
      currPiece.removeHeavy();
    }
    setPiece(currPiece);
}

void Grid::removeFilledRows() {
    for (int i = 0; i < theGrid.size(); i++) {
    }
}

void Grid::levelUp() {
  if (levelCount < maxLevel) {
    ++levelCount;
    setLevel();
  } else {
    throw "Reached Max Level";
  }
}

void Grid::levelDown() {
  if (levelCount > minLevel) {
    --levelCount;
    setLevel();
  } else {
    throw "Reached Min Level";
  }
}

void Grid::setLevel() {
  if (levelCount == 0) {
    currLevel = std::make_shared<LevelZero>();
  } else if (levelCount == 1) {
    currLevel = std::make_shared<LevelOne>();
  } else if (levelCount == 2) {
    currLevel = std::make_shared<LevelTwo>();
  } else if (levelCount == 3) {
    currLevel = std::make_shared<LevelThree>();
  } else if (levelCount == 4) {
    currLevel = std::make_shared<LevelFour>();
  }
}

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
