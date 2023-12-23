
#include <getopt.h>
#include <iostream>
#include <vector>
#include "Square.h"
#include "Board.h"
// #include "LocationFactory.h"
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

    Location build(Location current, int Fileoffset, int Rankoffset){
            return Location(static_cast<File>(current.getFile() + Fileoffset), current.getRank() + static_cast<size_t>(Rankoffset));
    } 

    vector<Location> getValidMoves(Board board, Square currentsquare);

    void possibleCandidates(vector<Location> &moveCandidates, Location &possibility, Location &current, Board &Gameboard){
        map<Location, Square> board = Gameboard.getLocationSquareMap();
        if (possibility.getRank() < 8 && possibility.getFile() < static_cast<File>(8)){
            if (!board[possibility].currentpiece){
                moveCandidates.push_back(possibility);
            }
            else {
                if (board[possibility].currentpiece->getPieceColor() != board[current].currentpiece->getPieceColor()){
                    moveCandidates.push_back(possibility);
                }
            }
        }
    }


};

class Pawn : public AbstractPiece {
public:
    bool isFirstMove = true;
    
    Pawn(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("Pawn");
    }

    vector<Location> getValidMoves(Square &currentsquare, Board &Gameboard){
        vector<Location> moveCandidates;
        Location current = currentsquare.getLocation();
        map<Location, Square> board = Gameboard.getLocationSquareMap();
        Location possibility = build(current, 0, 1);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        if(isFirstMove){
            Location possibility = build(current, 0, 2);
            possibleCandidates(moveCandidates, possibility, current, Gameboard);
            // return moveCandidates;
            //shud it return?
        }
            possibility = build(current, 1, 1);
            possibleCandidates(moveCandidates, possibility, current, Gameboard);
            possibility = build(current, -1, 1);
            possibleCandidates(moveCandidates, possibility, current, Gameboard);
        
        return moveCandidates;
    }
};

class Bishop : public AbstractPiece {
public:
    Bishop(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("Bishop");
    }
    vector<Location> getValidMoves(Square &currentsquare, Board &Gameboard){
        vector<Location> moveCandidates;
        Location current = currentsquare.getLocation();
        map<Location, Square> board = Gameboard.getLocationSquareMap();
        possibleCandidates(moveCandidates, board, current, 1, 1);
        possibleCandidates(moveCandidates, board, current, 1, -1);
        possibleCandidates(moveCandidates, board, current, -1, -1);
        possibleCandidates(moveCandidates, board, current, -1, 1);
        return moveCandidates;
    }

    void possibleCandidates(vector<Location> &moveCandidates, map<Location, Square> &board, Location &current, int fileoffset, int rankoffset){
        Location next = build(current, fileoffset, rankoffset);
        auto it = board.find(next);
        while (it != board.end()){
            if (it->second.currentpiece){
                if (it->second.currentpiece->getPieceColor() == board[current].currentpiece->getPieceColor()){
                    break;
                }
                moveCandidates.push_back(next);
                break;
            }
            moveCandidates.push_back(next);
            next = build(next, fileoffset, rankoffset);
        }
    }

};

class Knight : public AbstractPiece {
public:
    Knight(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("Knight");
    }

    vector<Location> getValidMoves(Square &currentsquare, Board &Gameboard){
        vector<Location> moveCandidates;
        Location current = currentsquare.getLocation();
        Location possibility = build(current, 2, 1);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, 2, -1);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, -2, 1);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, -2, -1);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, 1, 2);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, -1, 2);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, 1, -2);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, -1, -2);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        return moveCandidates;
    }

};

class Rook : public AbstractPiece {
public:
    Rook(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("Rook");
    }

    vector<Location> getValidMoves(Square &currentsquare, Board &Gameboard){
        vector<Location> moveCandidates;
        Location current = currentsquare.getLocation();
        map<Location, Square> board = Gameboard.getLocationSquareMap();
        getRankCandidates(moveCandidates, board, current, -1);
        getRankCandidates(moveCandidates, board, current, 1);
        getFileCandidates(moveCandidates, board, current, -1);
        getFileCandidates(moveCandidates, board, current, 1);
        return moveCandidates;
    }

    void getRankCandidates(vector<Location> &moveCandidates, map<Location, Square> &board, Location &current, int offset){
        Location next = build(current, current.getFile(), offset);
        auto it = board.find(next);
        while (it != board.end()){
            if (it->second.currentpiece){
                if (it->second.currentpiece->getPieceColor() == board[current].currentpiece->getPieceColor()){
                    break;
                }
                moveCandidates.push_back(next);
                break;
            }
            moveCandidates.push_back(next);
            next = build(next, next.getFile(), offset);
        }
    }

    void getFileCandidates(vector<Location> &moveCandidates, map<Location, Square> &board, Location &current, int offset){
        Location next = build(current, offset, static_cast<int>(current.getRank()));
        auto it = board.find(next);
        while (it != board.end()){
            if (it->second.currentpiece){
                if (it->second.currentpiece->getPieceColor() == board[current].currentpiece->getPieceColor()){
                    break;
                }
                moveCandidates.push_back(next);
                break;
            }
            moveCandidates.push_back(next);
            next = build(next, offset, static_cast<int>(next.getRank()));
        }
    }
};

class Queen : public AbstractPiece {
public:
    Queen(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("Queen");
    }

    vector<Location> getValidMoves(Square &currentsquare, Board &Gameboard){
        vector<Location> moveCandidates;
        Bishop bishop(currentsquare.currentpiece->getPieceColor());
        Rook rook(currentsquare.currentpiece->getPieceColor());
        vector<Location> A = bishop.getValidMoves(currentsquare, Gameboard);
        vector<Location> B = rook.getValidMoves(currentsquare, Gameboard);
        moveCandidates.insert(moveCandidates.end(), A.begin(), A.end());
        moveCandidates.insert(moveCandidates.end(), B.begin(), B.end());
        return moveCandidates;
    }
};

class King : public AbstractPiece {
public:
    King(PieceColor piececolorinput) : AbstractPiece(piececolorinput) {
        setName("King");
    }

    vector<Location> getValidMoves(Square &currentsquare, Board &Gameboard){
        vector<Location> moveCandidates;
        Location current = currentsquare.getLocation();
        Location possibility = build(current, 0, 1);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, 0, -1);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, 1, 0);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, -1, 0);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, -1, -1);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, 1, 1);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, 1, -1);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        possibility = build(current, -1, 1);
        possibleCandidates(moveCandidates, possibility, current, Gameboard);
        return moveCandidates;
    }
};




#endif