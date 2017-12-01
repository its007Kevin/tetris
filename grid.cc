#include <vector>
#include <iostream>
#include <exception>
#include <memory>
#include "grid.h"
#include "cell.h"
#include "info.h"
#include "piece.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
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

void Grid::setGraphicsDisplay(shared_ptr<GraphicsDisplay> gd) {
    this->gd = gd;
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
            //cell.attach(gd);
            row.emplace_back(cell);
        }
        theGrid.emplace_back(row);
    }
    setPiece(currPiece);
}

// If down results in a collision, spawn the next piece
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
        removeFilledRows();
        spawnNextPiece();
        ++blocksWithoutClear;
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
            removeFilledRows();
            spawnNextPiece();
            ++blocksWithoutClear;
            break;
        }
    }
    cout << *this;
}

void Grid::dropCenter(Piece &centerPiece) {
  while (true) {
      centerPiece.down();
      try {
        checkPiece(centerPiece);
        centerPiece.set();
        setPiece(centerPiece);
      } catch (Collision) {
        setPiece(centerPiece);
        centerPiece.revert();
        removeFilledRows();
        break;
      }
  }
  cout << *this;
}

// If a collision occured on left/right commands
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
    if (levelCount == 4) {
      if (blocksWithoutClear % 5 == 0 && blocksWithoutClear != 0) {
        Piece centerPiece = currLevel->generateCenterPiece();
        setPiece(centerPiece);
        dropCenter(centerPiece);
      }
    }
    if (levelCount == 3 || levelCount == 4) {
      currPiece.makeHeavy();
    } else {
      currPiece.removeHeavy();
    }
    setPiece(currPiece);
}

void Grid::removeFilledRows() {
    bool isFilled;
    vector<int> rowsToDelete;
    // Find the indexes of the rows to delete.
    for (int i = 0; i < theGrid.size(); i++) {
        isFilled = true;
        for (int j = 0; j < theGrid[i].size(); j++) {
            if (theGrid[i][j].getInfo().data == '-') {
                isFilled = false;
            }
        }
        if (isFilled == true) {
            rowsToDelete.emplace_back(i);
        }
    }
    for (int i = 0; i < rowsToDelete.size(); i++) {
        theGrid.erase(theGrid.begin() + rowsToDelete.at(i) - i);
    }
    int offset = rowsToDelete.size();
    int index = 0;
    for (int i = 0; i < rowsToDelete.size(); i++) {
      for (; index < rowsToDelete[i] - rowsToDelete.size() + offset; index++) {
        for (int j = 0; j < cols; j++) {
          theGrid[index][j].shiftRows(offset); //+= offset;
        }
      }
      offset--;
    }
    for (int i = rowsToDelete.size() - 1; i >= 0; i--) {
      vector<Cell> row;
      for (int j = 0; j < cols; j++) {
          Cell cell{i, j, '-'};
          cell.attach(td);
          row.emplace_back(cell);
      }
      theGrid.emplace(theGrid.begin(), row);
    }
    // Update textDisplay
    for (int i = 0; i < theGrid.size(); i++) {
      for (int j = 0; j < theGrid[i].size(); j++) {
        theGrid[i][j].notifyObservers();
      }
    }
}

void Grid::printCellCoords() {
    for (int i = 0; i < theGrid.size(); i++) {
      cout << "[";
      for (int j = 0; j < theGrid[i].size(); j++) {
        cout << "(" << theGrid[i][j].getInfo().row << "," << theGrid[i][j].getInfo().col << ") ";
      }
      cout << "]" << endl;
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

void Grid::replacePieceWith(char type) {}

void Grid::sequence(std::string file) {}

void Grid::restart() {}

void Grid::hint() {}

std::ostream& operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
