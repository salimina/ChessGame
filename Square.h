#include "Location.h"
#ifndef SQUARE_H
#define SQUARE_H
class AbstractPiece;


enum SquareColor {
    LIGHT,
    DARK
};

class Square {
public:
    SquareColor squarecolor;
    Location location;
    std::unique_ptr<AbstractPiece> currentpiece; 

    Square()
        : squarecolor(LIGHT), location({A,0}), currentpiece(nullptr) {}

    Square(SquareColor squarecolorinput, Location locationinput)
        : squarecolor(squarecolorinput), location(locationinput), currentpiece(nullptr) {}

    Square(const Square& other)
        : squarecolor(other.squarecolor), location(other.location) {
        if (other.currentpiece) {
            currentpiece = std::make_unique<AbstractPiece>(*other.currentpiece);
        }
    }

    Square& operator=(const Square& rhs) {
        if (this != &rhs) {
            this->squarecolor = rhs.squarecolor;
            this->location = rhs.location;
            currentpiece = nullptr;  // Clear the current piece
            if (rhs.currentpiece) {
                currentpiece = std::make_unique<AbstractPiece>(*rhs.currentpiece);
            }
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
        currentpiece = nullptr;
    }

    SquareColor getSquareColor() const {
        return squarecolor;
    }

    Location getLocation() const {
        return location;
    }
    void setAbstractPiece(std::unique_ptr<AbstractPiece> newPiece) {
        currentpiece = std::move(newPiece);
    }

    const AbstractPiece* getAbstractPiece() const {
        return currentpiece.get();
    }

};
#endif
