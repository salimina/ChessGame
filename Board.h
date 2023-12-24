#include <getopt.h>
#include <iostream>
#include <vector>
#include <map>
using namespace std;
#include "Location.h"
#include "Square.h"

#ifndef BOARD_H
#define BOARD_H

class AbstractPiece; 

class Board {
private:
    
    map<Location, Square> LocationSquareMap;

public:
    vector<vector<Square>> Gameboard;
    Board() : Gameboard(8, vector<Square>(8, Square(LIGHT, Location(A, 0)))){
        for (size_t i = 0; i < 8; ++i) {
            SquareColor CurrentColor = (i % 2 == 0) ? LIGHT : DARK;
            for (size_t j = 0; j < 8; ++j) {
                File holder = static_cast<File>(j);
                Location LocationCurrent(holder, 8-i);
                Square createdSquare = Square(CurrentColor, LocationCurrent);
                LocationSquareMap[LocationCurrent] = createdSquare;
                Gameboard[i][j] = createdSquare;
                CurrentColor = (CurrentColor == DARK) ? LIGHT : DARK;
            }
        }


    }

    map<Location, Square>& getLocationSquareMap(){
        return LocationSquareMap;
    }

};
#endif

