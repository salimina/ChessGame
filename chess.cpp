#include <getopt.h>
#include <iostream>
#include <vector>
using namespace std;
#include "Location.h"
#include "AbstractPiece.h"
#include "Square.h"
#include "Board.h"

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
        Board gameboard;
        
        void printBoard(Board &board) const {
            for (size_t i = 0; i < board.Gameboard[0].size(); ++i) {
                cout << board.Gameboard[0].size()-i << " ";
                for(size_t j = 0; j < board.Gameboard[i].size(); ++j) {
                    if (board.Gameboard[i][j].currentpiece){
                        cout << board.Gameboard[i][j].currentpiece->name.at(0) << " ";
                    }
                    else {
                        cout << "- ";
                    }
                }
                std::cout << std::endl;
            }

            cout << "  ";
            for (int i = 0; i < 8; ++i){
                cout << static_cast<char>('A' + i) << " ";
            }
    }

    void creation(){
        for (size_t i = 0; i < 8; ++i) {
            std::unique_ptr<AbstractPiece> whitepawn = std::make_unique<Pawn>(WHITE);
            std::unique_ptr<AbstractPiece> blackpawn = std::make_unique<Pawn>(BLACK);

            gameboard.Gameboard[6][i].setAbstractPiece(std::move(whitepawn));
            gameboard.Gameboard[1][i].setAbstractPiece(std::move(blackpawn));
        }
            std::unique_ptr<AbstractPiece> whiterook = std::make_unique<Rook>(WHITE);
            std::unique_ptr<AbstractPiece> blackrook = std::make_unique<Rook>(BLACK);
            std::unique_ptr<AbstractPiece> whiterook2 = std::make_unique<Rook>(WHITE);
            std::unique_ptr<AbstractPiece> blackrook2 = std::make_unique<Rook>(BLACK);
            gameboard.Gameboard[0][0].setAbstractPiece(std::move(whiterook));
            gameboard.Gameboard[0][7].setAbstractPiece(std::move(whiterook2));
            gameboard.Gameboard[7][0].setAbstractPiece(std::move(blackrook));
            gameboard.Gameboard[7][7].setAbstractPiece(std::move(blackrook2));

            std::unique_ptr<AbstractPiece> whiteknight = std::make_unique<Knight>(WHITE);
            std::unique_ptr<AbstractPiece> blackknight = std::make_unique<Knight>(BLACK);
            std::unique_ptr<AbstractPiece> whiteknight2 = std::make_unique<Knight>(WHITE);
            std::unique_ptr<AbstractPiece> blackknight2 = std::make_unique<Knight>(BLACK);
            gameboard.Gameboard[0][1].setAbstractPiece(std::move(whiteknight));
            gameboard.Gameboard[0][6].setAbstractPiece(std::move(whiteknight2));
            gameboard.Gameboard[7][1].setAbstractPiece(std::move(blackknight));
            gameboard.Gameboard[7][6].setAbstractPiece(std::move(blackknight2));

            std::unique_ptr<AbstractPiece> whitebishop = std::make_unique<Bishop>(WHITE);
            std::unique_ptr<AbstractPiece> blackbishop = std::make_unique<Bishop>(BLACK);
            std::unique_ptr<AbstractPiece> whitebishop2 = std::make_unique<Bishop>(WHITE);
            std::unique_ptr<AbstractPiece> blackbishop2 = std::make_unique<Bishop>(BLACK);
            gameboard.Gameboard[0][2].setAbstractPiece(std::move(whitebishop));
            gameboard.Gameboard[0][5].setAbstractPiece(std::move(whitebishop2));
            gameboard.Gameboard[7][2].setAbstractPiece(std::move(blackbishop));
            gameboard.Gameboard[7][5].setAbstractPiece(std::move(blackbishop2));

            std::unique_ptr<AbstractPiece> whitequeen = std::make_unique<Queen>(WHITE);
            std::unique_ptr<AbstractPiece> blackqueen = std::make_unique<Queen>(BLACK);
            gameboard.Gameboard[0][4].setAbstractPiece(std::move(whitequeen));
            gameboard.Gameboard[7][3].setAbstractPiece(std::move(blackqueen));

            std::unique_ptr<AbstractPiece> whiteking = std::make_unique<King>(WHITE);
            std::unique_ptr<AbstractPiece> blackking = std::make_unique<King>(BLACK);
            gameboard.Gameboard[0][3].setAbstractPiece(std::move(whiteking));
            gameboard.Gameboard[7][4].setAbstractPiece(std::move(blackking));
    
    }


    

    };



int main (){
    Chess obj;
    obj.creation();
    obj.printBoard(obj.gameboard);
}