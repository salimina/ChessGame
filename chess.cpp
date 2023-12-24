#include <getopt.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Location.h"
#include "AbstractPiece.h"
#include "Square.h"
#include "Board.h"
// #include "Boardfactory.h"

    void getOptions(int argc, char **argv){
        opterr = false;
        int option_index = 0;
        int choice = 0;

        struct option longOpts[] = {{"help", no_argument, nullptr, 'h'},
                                    {"mode", required_argument, nullptr, 'm'},
                                    {nullptr, 0, nullptr, '\0'}};

        while ((choice = getopt_long(argc, argv, "p", longOpts, &option_index)) != -1){
            switch (choice) {
                case 'p': {
                break;
                }
                case 'm': {
                    break;
                }
                default: {
                    cerr << "invalid input on command line\n";
                    exit(1);
                }
            }
        }
    }

    class Chess{
        public:
        Board board;
        
        void printBoard() const {
            for (size_t i = 0; i < board.Gameboard[0].size(); ++i) {
                cout << board.Gameboard[0].size()-i;
                for(size_t j = 0; j < board.Gameboard[i].size(); ++j) {
                    if (board.Gameboard[i][j].currentpiece){
                        cout << board.Gameboard[i][j].currentpiece->name << "\n";
                    }
                    else {
                        cout << "- ";
                    }
                }
                std::cout << std::endl;
            }

            for (int i = 0; i < 8; ++i){
                cout << static_cast<char>('A' + i) <<  " ";
            }
    }

    void creation(){
        for (size_t i = 0; i < 8; ++i) {
            Pawn whitepawn(WHITE);
            Pawn blackpawn(BLACK);
            board.Gameboard[i][6].setAbstractPiece(whitepawn);
            board.Gameboard[i][1].setAbstractPiece(blackpawn);
        }

        // Rook whiterook(WHITE);
        // Rook blackrook(BLACK);
        // Gameboard[0][0].setAbstractPiece(whiterook);
        // Gameboard[0][7].setAbstractPiece(whiterook);
    }

    };



int main (){
    Chess obj;
    obj.creation();
    obj.printBoard();

}