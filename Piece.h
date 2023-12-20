#ifndef PIECE_H
#define PIECE_H

enum PieceName {
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    QUEEN,
    KING,
    EMPTY
};


struct Piece {
    size_t row;
    size_t col;
    PieceName piecename;
    Piece() : row(0), col(0), piecename(EMPTY) {}
};
#endif