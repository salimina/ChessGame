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

class AbstractPiece {
public:
    string name;
    PieceColor piececolor;
    Location location;

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
        return Location(static_cast<File>(current.getFile() + Fileoffset), current.getRank() + static_cast<size_t>(Rankoffset));
    }

    virtual vector<Location> getValidMoves(Board &Gameboard) = 0;

    void possibleCandidates(vector<Location> &moveCandidates, Location &possibility, Location &current, Board &board) {
        // map<Location, shared_ptr<AbstractPiece>> board = Gameboard.getLocationSquareMap();
        if (possibility.getRank() < 8 && possibility.getFile() < static_cast<File>(8)) {
            if (!board.Gameboard[current.getFile()][current.getRank()]) {
                moveCandidates.push_back(possibility);
            } else {
                if (board.Gameboard[current.getFile()][current.getRank()]->getPieceColor() != board.Gameboard[current.getFile()][current.getRank()]->getPieceColor()) {
                    moveCandidates.push_back(possibility);
                }
            }
        }
    }


    void possibleSlidingCandidates(vector<Location> &moveCandidates, Board &board, Location &current, int fileoffset, int rankoffset){
        Location next = build(current, fileoffset, rankoffset);
        File row = next.getFile();
        size_t col = next.getRank();
        while (board.Gameboard[row][col]){
            if (board.Gameboard[row][col]->getPieceColor() == board.Gameboard[row][col]->getPieceColor()){
                break;
            }
            moveCandidates.push_back(current);
            next = build(next, fileoffset, rankoffset);
            row = current.getFile();
            col = current.getRank();
        }
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
    }

    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<Pawn>(*this);
    }

    vector<Location> getValidMoves(Board &Gameboard) override{
        vector<Location> moveCandidates;
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
    }

    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<Bishop>(*this);
    }
    vector<Location> getValidMoves (Board &Gameboard)override{
        vector<Location> moveCandidates;
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
    }

    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<Knight>(*this);
    }

    vector<Location> getValidMoves(Board &Gameboard) override{
        vector<Location> moveCandidates;
        Location possibility = build(location, 2, 1);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, 2, -1);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, -2, 1);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, -2, -1);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, 1, 2);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, -1, 2);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, 1, -2);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, -1, -2);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        return moveCandidates;
    }

};

class Board;
class Rook : public AbstractPiece {
public:
    Rook(PieceColor piececolorinput, Location locationinput) : AbstractPiece(piececolorinput, locationinput) {
        setName("Rook");
    }

    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<Rook>(*this);
    }

    vector<Location> getValidMoves(Board &Gameboard) override{
        vector<Location> moveCandidates;
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
    }

    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<Queen>(*this);
    }

    vector<Location> getValidMoves(Board &board) override{
        vector<Location> moveCandidates;
        Bishop bishop (board.Gameboard[static_cast<size_t>(location.getFile())][location.getRank()]->getPieceColor(), location);
        Rook rook(board.Gameboard[static_cast<size_t>(location.getFile())][location.getRank()]->getPieceColor(), location);
        vector<Location> A = bishop.getValidMoves(board);
        vector<Location> B = rook.getValidMoves(board);
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
    }
    std::shared_ptr<AbstractPiece> clone() const override {
        return std::make_shared<King>(*this);
    }

    vector<Location> getValidMoves(Board &Gameboard) override{
        vector<Location> moveCandidates;
        Location possibility = build(location, 0, 1);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, 0, -1);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, 1, 0);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, -1, 0);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, -1, -1);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, 1, 1);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, 1, -1);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        possibility = build(location, -1, 1);
        possibleCandidates(moveCandidates, possibility, location, Gameboard);
        return moveCandidates;
    }
};




#endif