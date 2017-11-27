#include "cell.h"
#include "info.h"
#include "state.h"
#include "subject.h"
#include <iostream>

using namespace std;

Direction Cell::getDirection(Subject<Info, State> &whoFrom) const {
    int x = whoFrom.getInfo().col - c;
    int y = whoFrom.getInfo().row - r;
    if (x == 0 && y == 1) {
        return Direction::N;
    } else if (x == 1 && y == 0) {
        return Direction::E;
    } else if (x == -1 && y == 0) {
        return Direction::W;
    } else if (x == 0 && y == -1) {
        return Direction::S;
    } else if (x == 1 && y == 1) {
        return Direction::NE;
    } else if (x == -1 && y == 1) {
        return Direction::NW;
    } else if (x == -1 && y == -1) {
        return Direction::SW;
    } else {
        return Direction::SE;
    }
}

Direction Cell::getOppositeDirection(Direction direction) const {
    if (direction == Direction::N) {
        return Direction::S;
    } else if (direction == Direction::NE) {
        return Direction::SW;
    }  else if (direction == Direction::E) {
        return Direction::W;
    } else if (direction == Direction::SE) {
        return Direction::NW;
    } else if (direction == Direction::S) {
        return Direction::N;
    } else if (direction == Direction::SW) {
        return Direction::NE;
    } else if (direction == Direction::W) {
        return Direction::E;
    } else {
        return Direction::SE;
    }
}

void Cell::printDirection(Direction direction) const {
    if (direction == Direction::N) {
        cout << "N" << endl;
    } else if (direction == Direction::NE) {
        cout << "NE" << endl;
    }  else if (direction == Direction::E) {
        cout << "E" << endl;
    } else if (direction == Direction::SE) {
        cout << "SE" << endl;
    } else if (direction == Direction::S) {
        cout << "S" << endl;
    } else if (direction == Direction::SW) {
        cout << "SW" << endl;
    } else if (direction == Direction::W) {
        cout << "W" << endl;
    } else {
        cout << "NW" << endl;
    }
}

Cell::Cell(size_t r, size_t c): r{r}, c{c} {}

void Cell::setPiece(Colour colour) {
    this->colour = colour;
    State newS;
    newS.type = StateType::NewPiece;
    newS.colour = colour;
    setState(newS);
    notifyObservers();
}

void Cell::toggle() {
    if (colour == Colour::Black) {
        colour = Colour::White;
    } else if (colour == Colour::White) {
        colour = Colour::Black;
    }
}

void Cell::notify(Subject<Info, State> &whoFrom) {
    State state = whoFrom.getState();
    State newS;
    Direction direction = getDirection(whoFrom);
    if (state.type == StateType::NewPiece) {
        if (state.colour != colour && colour != Colour::None) {
            newS.type = StateType::Relay;
            newS.colour = state.colour;
            newS.direction = direction;
            setState(newS);
            notifyObservers();
        }
    } else if (state.type == StateType::Relay) {
        if (direction == state.direction) {
            if (colour == Colour::None) {
                return;
            } else if (colour != state.colour) {
                newS.type = StateType::Relay;
                newS.colour = state.colour;
                newS.direction = direction;
                setState(newS);
                notifyObservers();
            } else if (colour == state.colour) { // Found a match
                newS.type = StateType::Reply;
                newS.colour = state.colour;
                newS.direction = getOppositeDirection(direction);
                setState(newS);
                notifyObservers();
            }
        }
    } else if (state.type == StateType::Reply) {
        if (direction == state.direction) {
            if (colour != state.colour && colour != Colour::None) {
                toggle();
                newS.type = StateType::Reply;
                newS.colour = state.colour;
                newS.direction = state.direction;
                setState(newS);
                notifyObservers();
            }
        }
    }
}

Info Cell::getInfo() const {
    Info info;
    info.row = r;
    info.col = c;
    info.colour = colour;
    return info;
}
