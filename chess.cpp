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



int main (){
    Board obj;
    AbstractPiece obj2(BLACK);
    Pawn Pawnz = Pawn(BLACK);
    obj.printBoard();
    obj2.printPiece(Pawnz);

}