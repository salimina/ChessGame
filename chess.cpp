#include <getopt.h>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
#include "Location.h"
#include "AbstractPiece.h"
#include "Board.h"
#include "memory.h"


    enum Color{
        white,
        black
    };

    struct Moves{
        Location start;
        Location end;
        int value;
    };

    class Chess{
        public:
        Board gameboard;
        void printBoard(Board &board) const {
            for (size_t i = 0; i < board.Gameboard[0].size(); ++i) {
                cout << static_cast<char>('A' + i) << " ";
                for(size_t j = 0; j < board.Gameboard[i].size(); ++j) {
                    if (board.Gameboard[i][j]){
                        cout << (board.Gameboard[i][j]->name == "Knight" ? 'N' : board.Gameboard[i][j]->name.at(0)) <<  " " ;
                    }
                    else {
                        cout << "- ";
                    }
                }
                std::cout << std::endl;
            }

            cout << "  ";
            for (size_t i = 0; i < 8; ++i){
                cout << board.Gameboard[0].size()-i << " ";
            }
            cout << "\n";
    }

    void creation(){
         Location L (A, 0);
        for (size_t i = 0; i < 8; ++i) {
            L.setFile(G);
            L.setRank(i);
           auto blackpawn = std::make_shared<Pawn>(BLACK, L);
            L.setFile(B);
           auto whitepawn = std::make_shared<Pawn>(WHITE, L);
            gameboard.setPiece(blackpawn, 6, i);
            gameboard.setPiece(whitepawn, 1, i);
        }
           L.setFile(A);
           L.setRank(0);
           auto whiterook = std::make_shared<Rook>(WHITE, L);
           L.setRank(7);
           auto whiterook2 = std::make_shared<Rook>(WHITE, L);
           L.setFile(H);
           auto blackrook2 = std::make_shared<Rook>(BLACK, L);  
           L.setRank(0); 
           auto blackrook = std::make_shared<Rook>(BLACK, L);
           
            gameboard.setPiece(whiterook, 0, 0);
            gameboard.setPiece(whiterook2, 0, 7);
            gameboard.setPiece(blackrook2, 7, 7);
            gameboard.setPiece(blackrook, 7, 0);

           L.setFile(A);
           L.setRank(1);
           auto whiteknight = std::make_shared<Knight>(WHITE, L);
           L.setRank(6);
           auto whiteknight2 = std::make_shared<Knight>(WHITE, L);
           L.setFile(H);
           auto blackknight = std::make_shared<Knight>(BLACK, L);
           L.setRank(1);
           auto blackknight2 = std::make_shared<Knight>(BLACK, L);
            gameboard.setPiece(whiteknight, 0, 1);
            gameboard.setPiece(whiteknight2, 0, 6);
            gameboard.setPiece(blackknight, 7, 6);
            gameboard.setPiece(blackknight2, 7 , 1);

           L.setFile(A);
           L.setRank(2);
           auto whitebishop = std::make_shared<Bishop>(WHITE, L);
           L.setRank(5);
           auto whitebishop2 = std::make_shared<Bishop>(WHITE, L);
           L.setFile(H);
           auto blackbishop = std::make_shared<Bishop>(BLACK, L);
           L.setRank(2);
           auto blackbishop2 = std::make_shared<Bishop>(BLACK, L);
            gameboard.setPiece(whitebishop, 0, 2);
            gameboard.setPiece(whitebishop2, 0, 5);
            gameboard.setPiece(blackbishop, 7, 5);
            gameboard.setPiece(blackbishop2, 7, 2);

           L.setFile(A);
           L.setRank(4);
           auto whitequeen = std::make_shared<Queen>(WHITE, L);
           L.setFile(H);
           L.setRank(3);
           auto blackqueen = std::make_shared<Queen>(BLACK, L);
            gameboard.setPiece(whitequeen, 0, 4);
            gameboard.setPiece(blackqueen, 7, 3);

           L.setFile(A);
           L.setRank(3);
           auto whiteking = std::make_shared<King>(WHITE,L);
           L.setFile(H);
           L.setRank(4);
           auto blackking = std::make_shared<King>(BLACK, L);
            gameboard.setPiece(whiteking, 0, 3);
            gameboard.setPiece(blackking, 7, 4);
    
    }

    void play(int depth, Color maximizingcolor){
        // bool isGameOver = false;
        if (depth == 0) return;
        // while (!isGameOver){
            possiblemoves();
            evaluate(maximizingcolor);
        // }
    }

    void possiblemoves(){
        vector<Location> allmoves;
        vector<Location> forpiece;
        for (size_t i = 0; i < gameboard.Gameboard[0].size(); ++i ){
            for(size_t j = 0; j < gameboard.Gameboard[i].size(); ++j) {
                if (gameboard.Gameboard[i][j]){
                    if (gameboard.Gameboard[i][j]->getPieceColor() == WHITE){
                        forpiece = gameboard.Gameboard[i][j]->getValidMoves(gameboard);
                        allmoves.insert(allmoves.begin(), forpiece.begin(), forpiece.end());
                    }
                }
            }
        }


    //    for (size_t i = 0; i < allmoves.size(); ++i){
    //     cout << i << ": " << allmoves[i].getFile() << ", " << allmoves[i].getRank() << "\n";
    //    }
    }

    int evaluate(Color maximizingcolor){
        if (maximizingcolor == white) return gameboard.whitescore - gameboard.blackscore;
        else return gameboard.blackscore - gameboard.whitescore;
    }

    


    

    };



int main (){
    Chess obj;
    obj.creation();
    obj.printBoard(obj.gameboard);
    obj.play(6, white);
}