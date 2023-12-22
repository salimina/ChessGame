
#include <getopt.h>
#include <iostream>
#include <vector>
#include "Square.h"
#include "Board.h"
#include "LocationFactory.h"
using namespace std;
#ifndef ABSTRACT_PIECE_H
#define ABSTRACT_PIECE_H


enum PieceColor{
    WHITE,
    BLACK
};


class AbstractPiece {
private:
    string name;
    PieceColor piececolor;
    Square currentsquare;  


public:

    AbstractPiece() {}
    
    AbstractPiece(PieceColor piececolorinput) : piececolor(piececolorinput){}

    void setName(const string& pieceName) {
        name = pieceName;
    }  

    string getName(){
        return name;
    }

    PieceColor getPieceColor(){
        return piececolor;
    }    

    Square getSquare(){
        return currentsquare;
    }    

   void setSquareColor(Square squarecolorinput){
        currentsquare = squarecolorinput;
    } 

    void printPiece(AbstractPiece piece){
        cout << piece.getName() << "\n";
        cout << PieceColortoString(piece.getPieceColor()) << "\n";
    }

    static std::string PieceColortoString(PieceColor piececolor) {
        switch (piececolor) {
            case WHITE: return "WHITE";
            case BLACK: return "BLACK";
            default: return "Unknown";
        }
    }  

    vector<Location> getValidMoves(Board board, Square currentsquare);
    // void makeMove(Square square);

};

class Pawn : public AbstractPiece {
public:
    bool isFirstMove = true;
    
    Pawn(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("Pawn");
    }
//Board board,
    vector<Location> getValidMoves( Square currentsquare){
        vector<Location> moveCandidates;
        Location current = currentsquare.getLocation();
        moveCandidates.push_back(LocationFactory::build(current, 0, 1));
        if(isFirstMove){
            moveCandidates.push_back(LocationFactory::build(current, 0, 2));
            return moveCandidates;
        }
            moveCandidates.push_back(LocationFactory::build(current, 1, 1));
            moveCandidates.push_back(LocationFactory::build(current, -1, 1));

        return moveCandidates;
    }
};

class Queen : public AbstractPiece {
public:
    Queen(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("Queen");
    }
};

class Bishop : public AbstractPiece {
public:
    Bishop(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("Bishop");
    }
};

class Knight : public AbstractPiece {
public:
    Knight(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("Knight");
    }
};

class Rook : public AbstractPiece {
public:
    Rook(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("Rook");
    }
};

class King : public AbstractPiece {
public:
    King(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("King");
    }
};




#endif