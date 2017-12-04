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
#include "holderror.h"
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
    if (displayGraphics) {
        this->gd = gd;
        gd->setLevel(levelCount);
        gd->setScore(score);
        gd->setHighScore(highScore);
    }
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
            if (displayGraphics) {
               cell.attach(gd);
            }
            row.emplace_back(cell);
        }
        theGrid.emplace_back(row);
    }
    if (notRandom && (levelCount == 3 || levelCount == 4)) {
      currPiece = currLevel->generatePiece(file);
      nextPiece = currLevel->generatePiece(file);
    } else {
      currPiece = currLevel->generatePiece();
      nextPiece = currLevel->generatePiece();
    }
    setPiece(currPiece);
    td->setNextPiece(nextPiece.render());
    if (displayGraphics) {
        gd->setNextPiece(nextPiece.render());
    }
}

// If down results in a collision, spawn the next piece
void Grid::down(int times) {
    unsetPiece(currPiece);
    for (int i = 0; i < times; i++) {
        currPiece.down();
        try {
            checkPiece(currPiece);
            currPiece.set();
        } catch (out_of_range) {
            currPiece.revert();
            break;
        } catch (Collision) {
            setPiece(currPiece);
            currPiece.revert();
            pieces.emplace_back(currPiece);
            removeFilledRows();
            spawnNextPiece();
            if (levelCount == 4) {
              ++blocksWithoutClear;
            }
            allowedToHold = true;
            break;
        }
    }
    setPiece(currPiece);
    cout << *this;
}

void Grid::left(int times) {
    unsetPiece(currPiece);
    for (int i = 0; i < times; i++) {
        currPiece.left();
        tryPlace();
    }
    setPiece(currPiece);
    cout << *this;
}

void Grid::right(int times) {
    unsetPiece(currPiece);
    for (int i = 0; i < times; i++) {
        currPiece.right();
        tryPlace();
    }
    setPiece(currPiece);
    cout << *this;
}

void Grid::rotateCW(int times) {
    times %= 4;
    unsetPiece(currPiece);
    for (int i = 0; i < times; i++) {
        currPiece.rotateCW();
        tryPlace();
    }
    setPiece(currPiece);
    cout << *this;
}

void Grid::rotateCCW(int times) {
    times %= 4;
    unsetPiece(currPiece);
    for (int i = 0; i < times; i++) {
        currPiece.rotateCCW();
        tryPlace();
    }
    setPiece(currPiece);
    cout << *this;
}

void Grid::drop(int times) {
  for (int i = 0; i < times; i++) {
    unsetPiece(currPiece);
      while (true) {
        currPiece.down();
        try {
          checkPiece(currPiece);
          currPiece.set();
        } catch (Collision) {
          setPiece(currPiece);
          currPiece.revert();
          pieces.emplace_back(currPiece);
          removeFilledRows();
          spawnNextPiece();
          if (levelCount == 4) {
            ++blocksWithoutClear;
          }
          break;
        }
      }
  }
  allowedToHold = true;
  cout << *this;
}

void Grid::dropCenter(Piece &centerPiece) {
  unsetPiece(centerPiece);
  while (true) {
      centerPiece.down();
      try {
        checkPiece(centerPiece);
        centerPiece.set();
      } catch (Collision) {
        centerPiece.revert();
        removeFilledRows();
        break;
      }
  }
  setPiece(centerPiece);
  cout << *this;
}

// If a collision occured on left/right commands
void Grid::tryPlace() {
    try {
        checkPiece(currPiece);
        currPiece.set();
        if (currPiece.checkHeavy()) {
          down(1);
        }
    } catch (out_of_range) {
        currPiece.revert();
    } catch (Collision) {
        currPiece.revert();
    }
}

void Grid::checkPiece(Piece piece) {
    int r, c;
    // Checks if potential coords are occupied or not first
    int size = piece.getPotentialCoords().size();
    for (int i = 0; i < size; i++) {
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
  int size = piece.getCoords().size();
  for (int i = 0; i < size; i++) {
    int r = piece.getCoords()[i][0];
    int c = piece.getCoords()[i][1];
    theGrid[r][c].setData(piece.getType());
    theGrid[r][c].notifyObservers();
  }
}

void Grid::unsetPiece(Piece piece) {
  for (int i = 0; i < piece.getCoords().size(); i++) {
    int r = piece.getCoords()[i][0];
    int c = piece.getCoords()[i][1];
    theGrid[r][c].setData(' ');
    theGrid[r][c].notifyObservers();
  }
}

void Grid::spawnNextPiece() {
    currPiece = nextPiece;
    if (notRandom && (levelCount == 3 || levelCount == 4)) {
      nextPiece = currLevel->generatePiece(file);
    } else {
      nextPiece = currLevel->generatePiece();
    }
    td->setNextPiece(nextPiece.render());
    if (displayGraphics) {
        gd->setNextPiece(nextPiece.render());
    }
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
    bool deletePiece = true;
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
      for (int j = 0; j < pieces.size(); ++j) {
        pieces.at(j).incRows(rowsToDelete.size()); //increment row of pieces by number of rows cleared
      }
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
          if (displayGraphics) {
            cell.attach(gd);
          }
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
    //cleared a line, update score
    if (rowsToDelete.size() != 0) {
      updateScore("line", levelCount);
    }

    //go through piece by piece, checking if any pieces should be deleted
    for (int j = pieces.size() - 1; j >=  0; --j) {
      for (int i = 0; i < pieces[j].getCoords().size(); ++i) {
        if (pieces.at(j).getCoords()[i][0] <= 17) { // check if each coordinate of the piece has been cleared
          deletePiece = false; //not all coordinates cleared, don't delete piece
        }
      }
      if (deletePiece) { //all coordinates have been cleared, delete the piece
        updateScore("piece", pieces.at(j).getLevel());
        pieces.erase(pieces.begin() + j);
      }
      deletePiece = true;
    }
}

void Grid::updateScore(std::string type, int level) {
  if (type == "line") {
    //cout << "Lines: " << (rowsDeleted + levelCount) * (rowsDeleted + levelCount) << endl;
    score += (rowsDeleted + levelCount) * (rowsDeleted + levelCount);
  } else if (type == "piece") {
    //cout << "Blocks: " << (level + 1) * (level + 1) << endl;
    score += (level + 1) * (level + 1);
  }
  if (score > highScore) {
    highScore = score;
  }
  td->setScore(score);
  td->setHighScore(highScore);
  if (displayGraphics) {
      gd->setScore(score);
      gd->setHighScore(highScore);
  }
}

void Grid::levelUp() {
  if (levelCount < maxLevel) {
    ++levelCount;
    setLevel(levelCount);
    td->setLevel(levelCount);
    if (displayGraphics) {
      gd->setLevel(levelCount);
    }
  } else {
    throw MaxLevel();
  }
}

void Grid::levelDown() {
  if (levelCount > minLevel) {
    --levelCount;
    setLevel(levelCount);
    td->setLevel(levelCount);
    if (displayGraphics) {
      gd->setLevel(levelCount);
    }
  } else {
    throw MinLevel();
  }
}

void Grid::setLevel(int level) {
  levelCount = level;
  td->setLevel(level);
  if (displayGraphics) {
    gd->setLevel(level);
  }
  if (levelCount == 0) {
    currLevel = std::make_shared<LevelZero>(scriptFile);
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

void Grid::noRandom(std::string file) {
  notRandom = true;
  this->file = file;
}

void Grid::random() {
  notRandom = false;
}

void Grid::replacePieceWith(char type) {
    unsetPiece(currPiece);
    Piece piece{type, levelCount};
    if (levelCount == 3 || levelCount == 4) {
        piece.makeHeavy();
    }
    currPiece = piece;
    setPiece(currPiece);
    cout << *this;
}

void Grid::textOnly() {
    displayGraphics = false;
}

void Grid::restart() {
  for (int i = 0; i < theGrid.size(); i++) {
    for (int j = 0; j < theGrid[i].size(); j++) {
        theGrid[i][j].setData(' ');
        theGrid[i][j].notifyObservers();
    }
  }
  score = 0;
  td->setScore(score);
  setPiece(currPiece);
  td->setNextPiece(nextPiece.render());
  if (displayGraphics) {
    gd->setScore(score);
    gd->setNextPiece(nextPiece.render());
  }
  cout << *this;
}

void Grid::hint() {}

void Grid::changeScriptFile(string filename) {
    scriptFile = filename;
    currLevel = make_shared<LevelZero>(scriptFile);
}

void Grid::setSeed(int seed) {
    if (levelCount == 1) {
        currLevel = std::make_shared<LevelOne>(seed);
    } else if (levelCount == 2) {
        currLevel = std::make_shared<LevelTwo>(seed);
    } else if (levelCount == 3) {
        currLevel = std::make_shared<LevelThree>(seed);
    } else if (levelCount == 4) {
        currLevel = std::make_shared<LevelFour>(seed);
    }
}

void Grid::hold() {
    if (allowedToHold && runEnhancements) {
        unsetPiece(currPiece);
        if (firstRun) {
            holdPiece = currPiece;
            spawnNextPiece();
            firstRun = false;
            allowedToHold = false;
        } else {
            // Swap pieces
            Piece tempPiece{'Z', 0};
            tempPiece = holdPiece;
            holdPiece = currPiece;
            currPiece = tempPiece;
            currPiece.reset();
            setPiece(currPiece);
            allowedToHold = false;
        }
        td->setHoldPiece(holdPiece.render());
        if (displayGraphics) {
            gd->setHoldPiece(holdPiece.render());
        }
    } else {
        throw HoldError();
    }
    cout << *this;
}

void Grid::enhancementsOn() {
    runEnhancements = true;
    td->enhancementsOn();
}

std::ostream& operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
