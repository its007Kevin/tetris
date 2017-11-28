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
    }
    // Attach observers
    // for (int row = 0; row < theGrid.size(); row++) {
    //     for (int col = 0; col < theGrid[row].size(); col++) {
    //         if (col == 0 && row == 0) { // Top left corner
    //             theGrid[row][col].attach(&theGrid[row][col + 1]); // mid right
    //             theGrid[row][col].attach(&theGrid[row + 1][col + 1]); // bottom right
    //             theGrid[row][col].attach(&theGrid[row + 1][col]); // bottom
    //         } else if (col == theGrid[row].size() - 1 && row == 0) { // Top right corner
    //             theGrid[row][col].attach(&theGrid[row][col - 1]); // mid left
    //             theGrid[row][col].attach(&theGrid[row + 1][col - 1]); // bottom left
    //             theGrid[row][col].attach(&theGrid[row + 1][col]); // bottom
    //         } else if (col == 0 && row == theGrid.size() - 1) { // Bottom left corner
    //             theGrid[row][col].attach(&theGrid[row][col + 1]); // mid right
    //             theGrid[row][col].attach(&theGrid[row - 1][col + 1]); // top right
    //             theGrid[row][col].attach(&theGrid[row - 1][col]); // top
    //         } else if (col == theGrid[row].size() - 1 && row == theGrid.size() - 1) { // Bottom right corner
    //             theGrid[row][col].attach(&theGrid[row - 1][col]); // top
    //             theGrid[row][col].attach(&theGrid[row][col - 1]); // mid left
    //             theGrid[row][col].attach(&theGrid[row - 1 ][col - 1]); // top left
    //         } else if (col == 0) { // Left edge
    //             theGrid[row][col].attach(&theGrid[row - 1][col]); // top
    //             theGrid[row][col].attach(&theGrid[row - 1][col + 1]); // top right
    //             theGrid[row][col].attach(&theGrid[row][col + 1]); // mid right
    //             theGrid[row][col].attach(&theGrid[row + 1][col + 1]); // bottom right
    //             theGrid[row][col].attach(&theGrid[row + 1][col]); // bottom
    //         } else if (row == 0) { // Top edge
    //             theGrid[row][col].attach(&theGrid[row][col + 1]); // mid right
    //             theGrid[row][col].attach(&theGrid[row][col - 1]); // mid left
    //             theGrid[row][col].attach(&theGrid[row + 1][col + 1]); // bottom right
    //             theGrid[row][col].attach(&theGrid[row + 1][col - 1]); // bottom left
    //             theGrid[row][col].attach(&theGrid[row + 1][col]); // bottom
    //         } else if (col == theGrid[row].size() - 1) { // Right edge
    //             theGrid[row][col].attach(&theGrid[row - 1][col]); // top
    //             theGrid[row][col].attach(&theGrid[row + 1][col]); // bottom
    //             theGrid[row][col].attach(&theGrid[row][col - 1]); // mid left
    //             theGrid[row][col].attach(&theGrid[row + 1][col - 1]); // bottom left
    //             theGrid[row][col].attach(&theGrid[row - 1 ][col - 1]); // top left
    //         } else if (row == theGrid.size() - 1) { // Bottom edge
    //             theGrid[row][col].attach(&theGrid[row - 1 ][col - 1]); // top left
    //             theGrid[row][col].attach(&theGrid[row - 1][col]); // top
    //             theGrid[row][col].attach(&theGrid[row - 1][col + 1]); // top right
    //             theGrid[row][col].attach(&theGrid[row][col + 1]); // mid right
    //             theGrid[row][col].attach(&theGrid[row][col - 1]); // mid left
    //         } else { // Middle piece
    //             theGrid[row][col].attach(&theGrid[row - 1 ][col - 1]); // top left
    //             theGrid[row][col].attach(&theGrid[row - 1][col]); // top
    //             theGrid[row][col].attach(&theGrid[row - 1][col + 1]); // top right
    //             theGrid[row][col].attach(&theGrid[row][col + 1]); // mid right
    //             theGrid[row][col].attach(&theGrid[row][col - 1]); // mid left
    //             theGrid[row][col].attach(&theGrid[row + 1][col + 1]); // bottom right
    //             theGrid[row][col].attach(&theGrid[row + 1][col - 1]); // bottom left
    //             theGrid[row][col].attach(&theGrid[row + 1][col]); // bottom
    //         }
    //     }
    // }
}



// Plays piece at row r, col c.
void Grid::setPiece(Piece piece, int r, int c) {
  //can use botLeftx and botLefty to determine r and c
  for (int i = 0; i < piece.cells.size(); i++) {
    // theGrid[a][b] accesses the b'th element of the a'th row
    if (theGrid[r + piece.cells[i][1]][c + piece.cells[i][0]].getInfo().data != nullptr) throw 3;
  }
  for (int i = 0; i < piece.cells.size(); i++) {
    theGrid[r + piece.cells[i][1]][c + piece.cells[i][0]] //set the piece
  }
  //notify surrounding cells
}

void Grid::unsetPiece(Piece piece) {
  for (int i = 0; i < piece.cells.size(); i++) {
    int r = piece.botLefty - height + piece.cells[i][1];
    int c = piece.botLeftx + piece.cells[i][0];
    theGrid[r][c].unset();
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

std::ostream& operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
