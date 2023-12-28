#ifndef ABSTRACT_PIECE_H
#define ABSTRACT_PIECE_H
#include <map>
#include <iostream>
#include <vector>
#include <memory>  // Include memory header for shared_ptr
#include "Board.h"
using namespace std;

class Board;
enum PieceColor {
    WHITE,
    BLACK
};

struct Moves{
    Location start;
    Location end;

    void setMove(Location startinput, Location endinput){
        start = startinput;
        end = endinput;
    }
};

class AbstractPiece {
public:
    string name;
    PieceColor piececolor;
    Location location;
    int Points;

    AbstractPiece() {}

    AbstractPiece(PieceColor piececolorinput, Location locationinput) : piececolor(piececolorinput), location(locationinput) {}

    void setName(const string &pieceName) {
        name = pieceName;
    }

    string getName() {
        return name;
    }

    PieceColor getPieceColor() {
        return piececolor;
    }

    static std::string PieceColortoString(PieceColor piececolor) {
        switch (piececolor) {
            case WHITE: return "WHITE";
            case BLACK: return "BLACK";
            default: return "Unknown";
        }
    }

    Location build(Location current, int Fileoffset, int Rankoffset) {
        return Location(static_cast<File>(static_cast<int>(current.getFile()) + Fileoffset), current.getRank() + static_cast<size_t>(Rankoffset));
    }

    virtual vector<Moves> getValidMoves(Board &Gameboard) = 0;

    void possibleCandidates(vector<Moves> &moveCandidates, Location &possibility, Location &current, Board &board) {
        if (possibility.getRank() < 8 && possibility.getFile() < static_cast<File>(8)) {
            if (!board.Gameboard[possibility.getFile()][possibility.getRank()]) {
                moveCandidates.push_back({current, possibility});
            } else {
                if (board.Gameboard[possibility.getFile()][possibility.getRank()]->getPieceColor() != board.Gameboard[current.getFile()][current.getRank()]->getPieceColor()) {
                    moveCandidates.push_back({current, possibility});
                }
            }
        }
    }

    bool InBounds (Location current, int fileoffset, int rankoffset){
        bool a = (static_cast<int>(current.getFile()) + fileoffset) < 8 ;
        bool b = (static_cast<int>(current.getFile()) + fileoffset) >= 0;
        bool c = (static_cast<int>(current.getRank()) + rankoffset) < 8;
        bool d = (static_cast<int>(current.getRank()) + rankoffset) >= 0;
        return (a &&
        b && c && d);
    }

    void possibleSlidingCandidates(vector<Moves> &moveCandidates, Board &board, Location &current, int fileoffset, int rankoffset){
        Location next = current;

        while (InBounds(current, fileoffset, rankoffset)){
            next = build(current, fileoffset, rankoffset);
            File row = next.getFile();
            size_t col = next.getRank();
            if (!board.Gameboard[row][col]){
                moveCandidates.push_back({current, next});
            }  
            else if (board.Gameboard[row][col] && board.Gameboard[row][col]->getPieceColor() != board.Gameboard[current.getFile()][current.getRank()]->getPieceColor()) {
                moveCandidates.push_back({current, next});
                    
            }

            else {
                break;
            }

        }

        return;

    }

    virtual std::shared_ptr<AbstractPiece> clone() const = 0;

    virtual ~AbstractPiece() {}

};

class Board;
class Pawn : public AbstractPiece {
public:
    bool isFirstMove = true;
    
    Pawn(PieceColor piececolorinput, Location locationinput) : AbstractPiece(piececolorinput, locationinput) {
        setName("Pawn");
        Points = 10;
    }

    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<Pawn>(*this);
    }

    vector<Moves> getValidMoves(Board &Gameboard) override{
        vector<Moves> moveCandidates;
        Location possibility = build(location, 0, 1);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        if(isFirstMove){
            Location possibility = build(location, 0, 2);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
            possibility = build(location, 1, 1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
            possibility = build(location, -1, 1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        
        return moveCandidates;
    }
};
class Board;
class Bishop : public AbstractPiece {
public:
    Bishop(PieceColor piececolorinput, Location locationinput) : AbstractPiece(piececolorinput, locationinput) {
        setName("Bishop");
        Points = 30;
    }

    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<Bishop>(*this);
    }
    vector<Moves> getValidMoves (Board &Gameboard)override{
        vector<Moves> moveCandidates;
        // map<Location, shared_ptr<AbstractPiece>> board = Gameboard.getLocationSquareMap();
        possibleSlidingCandidates(moveCandidates, Gameboard, location, 1, 1);
        possibleSlidingCandidates(moveCandidates, Gameboard, location, 1, -1);
        possibleSlidingCandidates(moveCandidates, Gameboard, location, -1, -1);
        possibleSlidingCandidates(moveCandidates, Gameboard, location, -1, 1);
        return moveCandidates;
    }

};

class Board;
class Knight : public AbstractPiece {
public:
    Knight(PieceColor piececolorinput, Location locationinput) : AbstractPiece(piececolorinput, locationinput) {
        setName("Knight");
        Points = 30;
    }

    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<Knight>(*this);
    }

    vector<Moves> getValidMoves(Board &Gameboard) override{
        vector<Moves> moveCandidates;
        Location possibility = location;
        if (InBounds(location, 2, 1)) {
            possibility = build(location, 2, 1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, 2, -1)) {
            possibility = build(location, 2, -1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, -2, 1)) {
            possibility = build(location, -2, 1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, -2, -1)) {
            possibility = build(location, -2, -1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, 1, 2)) {
            possibility = build(location, 1, 2);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, -1, 2)) {
            possibility = build(location, -1, 2);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, 1, -2)) {
            possibility = build(location, 1, -2);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, -1, -2)) {
            possibility = build(location, -1, -2);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        return moveCandidates;
    }

};

class Board;
class Rook : public AbstractPiece {
public:
    Rook(PieceColor piececolorinput, Location locationinput) : AbstractPiece(piececolorinput, locationinput) {
        setName("Rook");
        Points = 50;
    }

    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<Rook>(*this);
    }

    vector<Moves> getValidMoves(Board &Gameboard) override{
        vector<Moves> moveCandidates;
        possibleSlidingCandidates(moveCandidates, Gameboard, location, 0, -1);
        possibleSlidingCandidates(moveCandidates, Gameboard, location, 0, 1);
        possibleSlidingCandidates(moveCandidates, Gameboard, location, -1, 0);
        possibleSlidingCandidates(moveCandidates, Gameboard, location, 1, 0);
        return moveCandidates;
    }
};

class Board;
class Queen : public AbstractPiece {
public:
    Queen(PieceColor piececolorinput, Location locationinput) : AbstractPiece(piececolorinput, locationinput) {
        setName("Queen");
        Points = 90;
    }

    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<Queen>(*this);
    }

    vector<Moves> getValidMoves(Board &board) override{
        vector<Moves> moveCandidates;
        Bishop bishop (board.Gameboard[static_cast<size_t>(location.getFile())][location.getRank()]->getPieceColor(), location);
        Rook rook(board.Gameboard[static_cast<size_t>(location.getFile())][location.getRank()]->getPieceColor(), location);
        vector<Moves> A = bishop.getValidMoves(board);
        vector<Moves> B = rook.getValidMoves(board);
        moveCandidates.insert(moveCandidates.end(), A.begin(), A.end());
        moveCandidates.insert(moveCandidates.end(), B.begin(), B.end());
        return moveCandidates;
    }
};

class Board;
class King : public AbstractPiece {
public:
    King(PieceColor piececolorinput, Location locationinput) : AbstractPiece(piececolorinput, locationinput) {
        setName("King");
        Points = 900;
    }
    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<King>(*this);
    }

    vector<Moves> getValidMoves(Board &Gameboard) override{
        vector<Moves> moveCandidates;
        Location possibility = location;
        if (InBounds(location, 0, 1)) {
            possibility = build(location, 0, 1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, 0, -1)) {
            possibility = build(location, 0, -1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, 1, 0)) {
            possibility = build(location, 0, 1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, -1, 0)) {
            possibility = build(location, -1, 0);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, -1, -1)) {
            possibility = build(location, -1, -1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, 1, 1)) {
            possibility = build(location, 1, 1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, 1, -1)) {
            possibility = build(location, 1, -1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        if (InBounds(location, -1, 1)) {
            possibility = build(location, -1, 1);
            possibleCandidates(moveCandidates, possibility, location, Gameboard);
        }
        return moveCandidates;
    }
};




#endif