#include <getopt.h>
#include <iostream>
#include <vector>
#include <map>
#include <memory>  // Include memory header for shared_ptr
using namespace std;
#include "Location.h"

#ifndef BOARD_H
#define BOARD_H

class AbstractPiece;
struct Moves;

class Board {
private:
    map<Location, shared_ptr<AbstractPiece>> LocationSquareMap;

public:
    std::vector<std::vector<shared_ptr<AbstractPiece>>> Gameboard;

    
    
    Board() : Gameboard(8, vector<shared_ptr<AbstractPiece>>(8)) {
        for (size_t i = 0; i < 8; ++i) {
            for (size_t j = 0; j < 8; ++j) {
                File holder = static_cast<File>(j);
                Location LocationCurrent(holder, 8 - i);
                LocationSquareMap[LocationCurrent] = nullptr;
                Gameboard[i][j] = nullptr;
            }
        }
    }

    void reset(Location L) {
        Gameboard[static_cast<size_t>(L.getFile())][L.getRank()] = nullptr;
    }

    void setPiece(shared_ptr<AbstractPiece> piece, size_t row, size_t col) {
        Gameboard[row][col] = piece;
    }

    shared_ptr<AbstractPiece> getPiece(Location L) {
        return Gameboard[static_cast<size_t>(L.getFile())][L.getRank()];
    }

    map<Location, shared_ptr<AbstractPiece>> getLocationSquareMap() {
        return LocationSquareMap;
    }

    
};

#endif


