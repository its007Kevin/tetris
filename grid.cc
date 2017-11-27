#include "grid.h"
#include <vector>
#include "cell.h"
#include "info.h"
#include "piece.h"
#include "textdisplay.h"
#include <iostream>

using namespace std;

Grid::~Grid() {
    delete td;
}

void Grid::setTextDisplay(TextDisplay *td) {
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

}

std::ostream& operator<<(std::ostream &out, const Grid &g) {
    out << *(g.td);
    return out;
}
