#include "grid.h"
#include <vector>
#include "cell.h"
#include "state.h"
#include "info.h"
#include "textdisplay.h"
#include <iostream>

using namespace std;

Grid::~Grid() {
    delete td;
    delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob) {
    this->ob = ob; 
}

// Is the game over, i.e., is the grid full?
bool Grid::isFull() const {
    for (size_t y = 0; y < theGrid.size(); y++) {
        for (size_t x = 0; x < theGrid[y].size(); x++) {
            if (theGrid[y][x].getInfo().colour == Colour::None) {
                return false;
            }
        }
    } 
    return true;  
}

// Who has more pieces when the board is full?
Colour Grid::whoWon() const {
    int black = 0;
    int white = 0;
    for (size_t y = 0; y < theGrid.size(); y++) {
        for (size_t x = 0; x < theGrid[y].size(); x++) {
            if (theGrid[y][x].getInfo().colour == Colour::Black) {
                black++;
            } else if (theGrid[y][x].getInfo().colour == Colour::White) {
                white++;
            }
        }
    } 
    if (black == white) {
        return Colour::None;
    } else if (black > white) {
        return Colour::Black;
    } else {
        return Colour::White;
    }
}

void Grid::init(size_t n) { // Sets up an n x n grid.  Clears old grid, if necessary.
    // Clear old grid
    theGrid.clear();
    td = new TextDisplay{n};
    // Create new grid of cells
    for (size_t y = 0; y < n; y++) { // y coordinate
        vector<Cell> row;
        for (size_t x = 0; x < n; x++) { // x coordinate
            Cell cell{x, y};
            cell.attach(ob);  
            cell.attach(td);  
            // Initalize middle 4 cells as Black, White, Black, White
            size_t mid = n / 2;
            if ((x == mid - 1 && y == mid - 1) || (x == mid && y == mid)) {
                cell.setPiece(Colour::Black);
            } else if ((x == mid - 1 && y == mid) || (x == mid && y == mid - 1)) {
                cell.setPiece(Colour::White);
            }
            row.emplace_back(cell);
        }
        theGrid.emplace_back(row);
    }
    // Attach observers
    for (size_t y = 0; y < theGrid.size(); y++) {
        for (size_t x = 0; x < theGrid[y].size(); x++) {
            if (x == 0 && y == 0) { // Top left corner
                theGrid[y][x].attach(&theGrid[y][x + 1]); // mid right
                theGrid[y][x].attach(&theGrid[y + 1][x + 1]); // bottom right
                theGrid[y][x].attach(&theGrid[y + 1][x]); // bottom
            } else if (x == theGrid[y].size() - 1 && y == 0) { // Top right corner
                theGrid[y][x].attach(&theGrid[y][x - 1]); // mid left
                theGrid[y][x].attach(&theGrid[y + 1][x - 1]); // bottom left
                theGrid[y][x].attach(&theGrid[y + 1][x]); // bottom
            } else if (x == 0 && y == theGrid.size() - 1) { // Bottom left corner
                theGrid[y][x].attach(&theGrid[y][x + 1]); // mid right
                theGrid[y][x].attach(&theGrid[y - 1][x + 1]); // top right
                theGrid[y][x].attach(&theGrid[y - 1][x]); // top
            } else if (x == theGrid[y].size() - 1 && y == theGrid.size() - 1) { // Bottom right corner
                theGrid[y][x].attach(&theGrid[y - 1][x]); // top
                theGrid[y][x].attach(&theGrid[y][x - 1]); // mid left
                theGrid[y][x].attach(&theGrid[y - 1 ][x - 1]); // top left
            } else if (x == 0) { // Left edge
                theGrid[y][x].attach(&theGrid[y - 1][x]); // top
                theGrid[y][x].attach(&theGrid[y - 1][x + 1]); // top right
                theGrid[y][x].attach(&theGrid[y][x + 1]); // mid right
                theGrid[y][x].attach(&theGrid[y + 1][x + 1]); // bottom right
                theGrid[y][x].attach(&theGrid[y + 1][x]); // bottom
            } else if (y == 0) { // Top edge
                theGrid[y][x].attach(&theGrid[y][x + 1]); // mid right
                theGrid[y][x].attach(&theGrid[y][x - 1]); // mid left
                theGrid[y][x].attach(&theGrid[y + 1][x + 1]); // bottom right
                theGrid[y][x].attach(&theGrid[y + 1][x - 1]); // bottom left
                theGrid[y][x].attach(&theGrid[y + 1][x]); // bottom
            } else if (x == theGrid[y].size() - 1) { // Right edge
                theGrid[y][x].attach(&theGrid[y - 1][x]); // top
                theGrid[y][x].attach(&theGrid[y + 1][x]); // bottom
                theGrid[y][x].attach(&theGrid[y][x - 1]); // mid left
                theGrid[y][x].attach(&theGrid[y + 1][x - 1]); // bottom left
                theGrid[y][x].attach(&theGrid[y - 1 ][x - 1]); // top left
            } else if (y == theGrid.size() - 1) { // Bottom edge
                theGrid[y][x].attach(&theGrid[y - 1 ][x - 1]); // top left
                theGrid[y][x].attach(&theGrid[y - 1][x]); // top
                theGrid[y][x].attach(&theGrid[y - 1][x + 1]); // top right
                theGrid[y][x].attach(&theGrid[y][x + 1]); // mid right
                theGrid[y][x].attach(&theGrid[y][x - 1]); // mid left
            } else { // Middle piece
                theGrid[y][x].attach(&theGrid[y - 1 ][x - 1]); // top left
                theGrid[y][x].attach(&theGrid[y - 1][x]); // top
                theGrid[y][x].attach(&theGrid[y - 1][x + 1]); // top right
                theGrid[y][x].attach(&theGrid[y][x + 1]); // mid right
                theGrid[y][x].attach(&theGrid[y][x - 1]); // mid left
                theGrid[y][x].attach(&theGrid[y + 1][x + 1]); // bottom right
                theGrid[y][x].attach(&theGrid[y + 1][x - 1]); // bottom left
                theGrid[y][x].attach(&theGrid[y + 1][x]); // bottom
            }
        }
    }
    cout << *this;
}

// Plays piece at row r, col c.
void Grid::setPiece(size_t r, size_t c, Colour colour) {
    if (r >= 0 && r <= theGrid.size() && c >= 0 && c <= theGrid.size() && theGrid[r][c].getInfo().colour == Colour::None) {
        theGrid[r][c].setPiece(colour);
        cout << *this;
    } else {
        throw InvalidMove();
    }
}

// Flips piece at row r, col c.
void Grid::toggle(size_t r, size_t c) {
    // Not necessary
}

std::ostream& operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
