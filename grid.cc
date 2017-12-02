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
#include "maxlevel.h"
#include "minlevel.h"
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

bool Grid::checkIsGameOver() {
    for (int i = 0; i < currPiece.getCoords().size(); i++) {
        int r = currPiece.getCoords()[i][0];
        int c = currPiece.getCoords()[i][1];
        if (theGrid[r][c].getInfo().data != ' ') {
            throw "GameOver";
        }
    }
}

void Grid::init(int r, int c) {
    rows = r;
    cols = c;
    theGrid.clear();
    for (int i = 0; i < r; i++) {
        vector<Cell> row;
        for (int j= 0; j < c; j++) {
            Cell cell{i, j, ' '};
            cell.attach(td);
            //cell.attach(gd);
            row.emplace_back(cell);
        }
        theGrid.emplace_back(row);
    }
    currPiece = currLevel->generatePiece();
    nextPiece = currLevel->generatePiece();
    setPiece(currPiece);
    td->setNextPiece(nextPiece.render());
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
        } else if (r >= rows || theGrid[r][c].getInfo().data != ' ') {
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
    theGrid[r][c].setData(' ');
  }
}

void Grid::spawnNextPiece() {
    currPiece = nextPiece;
    nextPiece = currLevel->generatePiece();
    td->setNextPiece(nextPiece.render());
    checkIsGameOver();
    if (levelCount == 4) {
      if (blocksWithoutClear % 5 == 0 && blocksWithoutClear != 0) {
        Piece centerPiece = currLevel->generateCenterPiece();
        setPiece(centerPiece);
        dropCenter(centerPiece);
      }
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
            if (theGrid[i][j].getInfo().data == ' ') {
                isFilled = false;
            }
        }
        if (isFilled == true) {
            blocksWithoutClear = 0;
            rowsToDelete.emplace_back(i);
        }
    }
    for (int i = 0; i < rowsToDelete.size(); i++) {
        theGrid.erase(theGrid.begin() + rowsToDelete.at(i) - i);
    }
    int offset = rowsToDelete.size();
    rowsDeleted = rowsToDelete.size();
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
          Cell cell{i, j, ' '};
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
    if (rowsToDelete.size() != 0) {
      updateScore();
    }

}

void Grid::updateScore() {
  score += (rowsDeleted + levelCount) * (rowsDeleted + levelCount);
  if (score > highScore) {
    highScore = score;
  }
  td->setScore(score);
  td->setHighScore(highScore);
  //cout << "Score " << score << endl;
  //cout << "High score " << highScore << endl;
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
    setLevel(levelCount);
    td->setLevel(levelCount);
  } else {
    throw MaxLevel();
  }
}

void Grid::levelDown() {
  if (levelCount > minLevel) {
    --levelCount;
    setLevel(levelCount);
    td->setLevel(levelCount);
  } else {
    throw MinLevel();
  }
}

void Grid::setLevel(int level) {
  levelCount = level;
  td->setLevel(level);
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

void Grid::replacePieceWith(char type) {
    unsetPiece(currPiece);
    Piece piece{type};
    currPiece = piece;
    setPiece(currPiece);
    cout << *this;
}

void Grid::restart() {
  for (int i = 0; i < theGrid.size(); i++) {
    for (int j = 0; j < theGrid[i].size(); j++) {
        theGrid[i][j].setData(' ');
    }
  }
  setPiece(currPiece);
  td->setNextPiece(nextPiece.render());
  cout << *this;
}

void Grid::hint() {}

std::ostream& operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
