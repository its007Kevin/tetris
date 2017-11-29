#include "grid.h"
#include <vector>
#include "cell.h"
#include "info.h"
#include "piece.h"
#include "textdisplay.h"
#include <iostream>

using namespace std;

Grid::~Grid() {}

void Grid::setTextDisplay(shared_ptr<TextDisplay> td) {
    this->td = td;
}

bool Grid::isGameOver() const {
    return false;
}

void Grid::init(int r, int c) { // Sets up an grid with r rows and c columns
    // Clear old grid
    theGrid.clear();
    // Create new grid of cells
    for (int i = 0; i < r; i++) { // Generate Rows
        vector<Cell> row;
        for (int j= 0; j < c; j++) { // Generate Columns
            Cell cell{i, j, ' '}; 
            cell.attach(td);  
            row.emplace_back(cell);
        }
        theGrid.emplace_back(row);
    }0
}



// Plays piece at row r, col c.
void Grid::setPiece(Piece piece) {
  //can use botLeftx and botLefty to determine r and c
  for (int i = 0; i < piece.cells.size(); i++) {
    // theGrid[a][b] accesses the b'th element of the a'th row
//need proper exception
    if (theGrid[piece.cells[i][1]][piece.cells[i][0]].getInfo().data != ' ') throw 3;
  }
  for (int i = 0; i < piece.cells.size(); i++) {
    theGrid[piece.cells[i][1]][piece.cells[i][0]].setData(piece.type); //set the piece
  }
  //notify surrounding cells
}

void Grid::unsetPiece(Piece piece) {
  for (int i = 0; i < piece.cells.size(); i++) {
    int r = piece.cells[i][1];
    int c = piece.cells[i][0];
    theGrid[r][c].setData(' ');
  }
}

// try catch needs work
void Grid::moveLeft() {
  unsetPiece(currPiece);
  currPiece.moveLeft();
  try {
    setPiece(currPiece);
  } catch() {
    currPiece.moveRight();
    setPiece(currPiece);
  }
}

void Grid::moveRight() {
  unsetPiece(currPiece);
  currPiece.moveRight();
  try {
    setPiece(currPiece);
  } catch() {
    currPiece.moveLeft();
    setPiece(currPiece);
  }
}

void Grid::moveDown() {
  unsetPiece(currPiece);
  currPiece.moveDown();
  try {
    setPiece(currPiece);
  } catch() {
    currPiece.moveUp();
    setPiece(currPiece);
  }
}

void Grid::rotate(bool isCw) {
  unsetPiece(currPiece);
  currPiece.rotate(isCw);
  try {
    setPiece(currPiece);
  } catch() {
    currPiece.rotate(!isCw);
    setPiece(currPiece);
  }
}

void Grid::levelUp() {}

void Grid::levelDown() {}

void Grid::noRandom(std::string file) {}

void Grid::random() {}

void Grid::sequence(std::string file) {}

void Grid::replacePieceWith(char type) {
  //delete old currPiece??
  currPiece = unique_ptr<Piece> {type};
}

void Grid::restart() {

}

void Grid::hint() {

}

std::ostream& operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
