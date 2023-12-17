#include <getopt.h>
#include <iostream>
#include <vector>
using namespace std;

enum Rank {
    PAWN,
    BISHOP,
    KNIGHT,
    ROOK,
    QUEEN,
    KING,
    EMPTY
};

enum Color {
    WHITE,
    BLACK
};

struct Piece {
    int row = 0;
    int col = 0;
    Color colorType;
    Rank rankType = EMPTY;
};

class Chess{
    private:
    int rowNum = 8;
    int colNum = 8;
    vector<vector<Piece>> Gameboard;

    public:

    Chess(){
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 8; ++j){
                // Gameboard[0][0] = 
        }
    }
    }



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

};

int main (){

}