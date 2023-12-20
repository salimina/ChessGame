#include "Location.h"

#ifndef SQUARE_H
#define SQUARE_H

enum SquareColor {
    LIGHT,
    DARK
};

class Square {
public:
    SquareColor squarecolor;
    Location location;

    Square(SquareColor squarecolorinput, Location locationinput)
        : squarecolor(squarecolorinput), location(locationinput), isOccupied(false) {}

    Square(const Square& other)
        : squarecolor(other.squarecolor), location(other.location), isOccupied(other.isOccupied) {}

    Square& operator=(const Square& rhs) {
        if (this != &rhs) {
            this->squarecolor = rhs.squarecolor;
            this->location = rhs.location;
            this->isOccupied = rhs.isOccupied;  // Add this line
        }
        return *this;
    }

    static std::string SquareColortoString(SquareColor squarecolor) {
        switch (squarecolor) {
            case LIGHT: return "light";
            case DARK: return "dark";
            default: return "Unknown";
        }
    }  

    void reset() {
        isOccupied = false;
    }

    void setOccupation(bool occupied) {
        isOccupied = occupied;
    }

    bool getOccupation() const {
        return isOccupied;
    }

    SquareColor getSquareColor() const {
        return squarecolor;
    }

    Location getLocation() const {
        return location;
    }

private:
    bool isOccupied;
};
#endif
