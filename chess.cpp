#include <getopt.h>
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
#include "Location.h"
#include "AbstractPiece.h"
#include "Board.h"
#include "memory.h"
#include <limits>
#include <set>

enum Color
{
    white,
    black
};

struct Moves;

struct Checks{
    Location piecelocation;
    size_t xdirection;
    size_t ydirection;


    Checks(Location piecelocationinput, size_t xdirectioninput, size_t ydirectioninput) : 
    piecelocation(piecelocationinput), xdirection(xdirectioninput), ydirection(ydirectioninput) {}
};

class Chess
{
public:
    Board gameboard;
    Color computercolor;
    Color humancolor;
    int whitescore = 1290;
    int blackscore = 1290;
    bool computerturn = false;
    bool checkmate = false;
    bool stalemate = false;
    Color winningplayer;
    shared_ptr<AbstractPiece> lastpiecemoved;
    Moves bestcompmove;
    Moves besthumanmove;
    Location whitekinglocation;
    Location blackkinglocation;
    vector<Moves> movelog;
    vector<Moves> pinsmain;
    vector<Checks> checksmain;
    bool check = false;

    void printBoard() const
    {
        for (size_t i = 0; i < gameboard.Gameboard[0].size(); ++i)
        {
            cout << static_cast<char>('A' + i) << " ";
            for (size_t j = 0; j < gameboard.Gameboard[i].size(); ++j)
            {
                if (gameboard.Gameboard[i][j])
                {
                    cout << (gameboard.Gameboard[i][j]->name == "Knight" ? 'N' : gameboard.Gameboard[i][j]->name.at(0)) << " ";
                }
                else
                {
                    cout << "- ";
                }
            }
            std::cout << std::endl;
        }

        cout << "  ";
        for (size_t i = 0; i < 8; ++i)
        {
            cout << gameboard.Gameboard[0].size() - (gameboard.Gameboard[0].size() - i) << " ";
        }
        cout << "\n";
    }

    void creation()
    {
        Location L(A, 0);
        for (size_t i = 0; i < 8; ++i)
        {
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
        gameboard.setPiece(blackknight2, 7, 1);

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
        blackkinglocation.setFile(A);
        blackkinglocation.setRank(3);
        auto whiteking = std::make_shared<King>(WHITE, L);
        L.setFile(H);
        L.setRank(4);
        whitekinglocation.setFile(H);
        whitekinglocation.setRank(4);
        auto blackking = std::make_shared<King>(BLACK, L);
        gameboard.setPiece(whiteking, 0, 3);
        gameboard.setPiece(blackking, 7, 4);
    }

    int choosemove(int depth, bool computerturn, Color computercolor){
        Moves bestmove;
        vector<Moves> allMoves;
        int curr_eval = 0;
        int alpha = 0;
        int beta = 0;
        if (depth == 0)
            return evaluate(computercolor);
        allMoves = actualmoves();
        if (allMoves.size() == 0){
            return 0;
        }


        bestmove = allMoves[0];

        if (computerturn)
        {
            int max_eval = -(numeric_limits<int>::max());
            for (auto move : allMoves)
            {
                makeMove(move);
                curr_eval = choosemove(depth - 1, false, computercolor);
                unmakeMove(move);
                if (curr_eval > max_eval)
                {
                    max_eval = curr_eval;
                    bestmove = move;
                }
                alpha = max(alpha, curr_eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
            return curr_eval;
        }
        else
        {
            int min_eval = numeric_limits<int>::max();
            for (auto move : allMoves)
            {
                makeMove(move);
                curr_eval = choosemove(depth - 1, true, computercolor);
                unmakeMove(move);
                if (curr_eval > min_eval)
                {
                    min_eval = curr_eval;
                    bestmove = move;
                }
                beta = min(beta, curr_eval);
                if (beta <= alpha)
                {
                    break;
                }
            }
            return curr_eval;
        }
        // }
    }

    int evaluate(Color maximizingcolor){
        if (maximizingcolor == white)
            return whitescore - blackscore;
        else
            return blackscore - whitescore;
    }

    void makeMove(Moves move){
        if (gameboard.Gameboard[static_cast<size_t>(move.start.getFile())][move.start.getRank()]->getName() == "King" &&
            gameboard.Gameboard[static_cast<size_t>(move.start.getFile())][move.start.getRank()]->getPieceColor() == WHITE){
                whitekinglocation = move.end;
        }
        else {
            blackkinglocation = move.end;
        }
        if (gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()]){
            if (gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()]->getPieceColor() == WHITE){
                whitescore -= gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()]->Points;
            }
            else {
                blackscore -= gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()]->Points;
            }
        }
        lastpiecemoved = gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()];
        gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()] = gameboard.Gameboard[static_cast<size_t>(move.start.getFile())][move.start.getRank()];
        gameboard.Gameboard[static_cast<size_t>(move.start.getFile())][move.start.getRank()] = nullptr;
    }

    void unmakeMove(Moves move){
        // Moves move = movelog.back();
        // movelog.pop_back();
        if (gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()]->getName() == "King"){
            if (gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()]->getPieceColor() == WHITE){
                whitekinglocation = move.start;
            }
            else {
                blackkinglocation = move.start;
            }
        }
        if (lastpiecemoved->getPieceColor() == WHITE){
            whitescore += lastpiecemoved->Points;
        }
        else if (lastpiecemoved->getPieceColor() == BLACK){
            blackscore += lastpiecemoved->Points;
        }
        gameboard.Gameboard[static_cast<size_t>(move.start.getFile())][move.start.getRank()] = gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()];
        gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()] = lastpiecemoved;
    }

    void play(){
        Moves move = computerturn ? bestcompmove : besthumanmove;
        // movelog.push_back(move);
        //not needed if lastpiecemoved pointer is there
        if (gameboard.Gameboard[static_cast<size_t>(move.start.getFile())][move.start.getRank()]->getName() == "King" &&
            gameboard.Gameboard[static_cast<size_t>(move.start.getFile())][move.start.getRank()]->getPieceColor() == WHITE){
                whitekinglocation = move.end;
        }
        else {
            blackkinglocation = move.end;
        }
        lastpiecemoved = gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()];
        gameboard.Gameboard[static_cast<size_t>(move.end.getFile())][move.end.getRank()] = gameboard.Gameboard[static_cast<size_t>(move.start.getFile())][move.start.getRank()];
        gameboard.Gameboard[static_cast<size_t>(move.start.getFile())][move.start.getRank()] = nullptr;

    }

    vector<Moves> possiblemoves(){
        vector<Moves> allmoves;
        vector<Moves> forpiece;
        PieceColor analyze;
        if (computerturn)
            analyze = computercolor == white ? WHITE : BLACK;
        else
            analyze = computercolor == white ? WHITE : BLACK;
        //shud probably just be a computer 
        for (size_t i = 0; i < gameboard.Gameboard[0].size(); ++i){
            for (size_t j = 0; j < gameboard.Gameboard[i].size(); ++j){
                if (gameboard.Gameboard[i][j]){
                    if (gameboard.Gameboard[i][j]->getPieceColor() == analyze){
                        forpiece = gameboard.Gameboard[i][j]->getValidMoves(gameboard);
                        allmoves.insert(allmoves.begin(), forpiece.begin(), forpiece.end());
                    }
                }
            }
        }
        return allmoves;
    }

    void checkforpinsandchecks(){
        vector<Moves> pins;
        vector<Checks> checks;
        bool incheck = false;
        PieceColor enemy;
        PieceColor ally;
        Moves scrutinize;
        if (computerturn){
            if (computercolor == white){
                enemy = BLACK;
                ally = WHITE;
            }
            else {
                enemy = WHITE;
                ally = BLACK;
            }
        }
        else {
            if (humancolor == white){
                enemy = BLACK;
                ally = WHITE;
            }
            else {
                enemy = WHITE;
                ally = BLACK;
            }
        }
        scrutinize.start = ally == WHITE ? whitekinglocation : blackkinglocation;
        vector<pair<int, int>> directions {{0,1}, {0,-1}, {1,0}, {-1,0}, {-1,-1}, {1,1}, {1,-1}, {-1,1}};
        for (size_t i = 0; i < directions.size(); ++i){
            pair<int, int> d = directions[i];
            pins.clear();
            for (size_t j = 0; j < 8; ++j){
                if (AbstractPiece::InBounds(scrutinize.start, d.first * static_cast<int>(i), d.second * static_cast<int>(i))){
                    scrutinize.end.setFile(Location::IntToFile(static_cast<int>(scrutinize.start.getFile()) + d.first * static_cast<int>(i)));
                    scrutinize.end.setRank(scrutinize.start.getRank() + static_cast<size_t>(d.second) * i);
                    if (gameboard.Gameboard[static_cast<size_t>(scrutinize.end.getFile())][scrutinize.end.getRank()]){
                        shared_ptr<AbstractPiece> meowmeow = gameboard.Gameboard[static_cast<size_t>(scrutinize.end.getFile())][scrutinize.end.getRank()];
                        if (meowmeow->getPieceColor() == ally){
                            if (pins.empty()){
                                pins.push_back(scrutinize);
                            }
                            else {
                                break;
                            }
                        }
                        else if (meowmeow->getPieceColor() == enemy){
                            string name = meowmeow->getName();
                            if ((0 <= i && i <= 3 && name == "ROOK") || (4 <= i && i <= 7 && name == "BISHOP") || 
                            (j == 1 && name == "PAWN" && ((enemy == WHITE && 6 <= i && i <= 7) || (enemy == BLACK && 4 <= i && i <= 5))) || 
                            (name == "QUEEN") || (j == 1 && name == "KING")){
                                if (pins.empty()){
                                    incheck = true;
                                    Checks check (scrutinize.end, static_cast<size_t>(d.first), static_cast<size_t>(d.second)); 
                                    checks.push_back(check);
                                    break;
                                }
                                else {
                                    pins.push_back(scrutinize);
                                }
                            }
                            else {
                                break;
                            }
                        }
                    }

                }
                else {
                    break;
                }
            }
        }
        vector<pair<int, int>> knightdirections {{-2,-1}, {-2,1}, {-1,-2}, {-1,2}, {1,-2}, {1,2}, {2,-1}, {2,1}};
        for (auto k : knightdirections){
            if (AbstractPiece::InBounds(scrutinize.start, k.first, k.second)){
                scrutinize.end.setFile(Location::IntToFile(static_cast<int>(scrutinize.start.getFile()) + k.first));
                scrutinize.end.setRank(scrutinize.start.getRank() + static_cast<size_t>(k.second));
                if (gameboard.Gameboard[static_cast<size_t>(scrutinize.end.getFile())][scrutinize.end.getRank()]){
                    shared_ptr<AbstractPiece> meowmeow = gameboard.Gameboard[static_cast<size_t>(scrutinize.end.getFile())][scrutinize.end.getRank()];
                    if (meowmeow->getName() == "KNIGHT" && meowmeow->getPieceColor() == enemy){
                        incheck = true;
                        Checks check (scrutinize.end, static_cast<size_t>(k.first), static_cast<size_t>(k.second)); 
                        checks.push_back(check);
                }

                }
            }

        }
        check = incheck;
        checksmain = checks;
        pinsmain = pins;

    }

    vector<Moves> actualmoves(){
        checkforpinsandchecks();
        Location scrutinize;
        vector<Moves> moves;
        vector<Moves> actualmoves;
        if (computerturn){
            scrutinize = computercolor == white ? whitekinglocation : blackkinglocation;
        }
        else {
            scrutinize = humancolor == white ? whitekinglocation : blackkinglocation; 
        }

        if (check){
            if (checksmain.size() == 1){
                moves = possiblemoves();
                shared_ptr<AbstractPiece> piecechecking = gameboard.Gameboard[static_cast<size_t>(checksmain[0].piecelocation.getFile())][checksmain[0].piecelocation.getRank()];
                set<Location> validsquares;
                if (piecechecking->getName() == "KNIGHT"){
                    validsquares.insert(checksmain[0].piecelocation);
                }
                else {
                    for (size_t i = 0; i < 8; ++i){
                        Location validsquare;
                        validsquare.setFile(Location::IntToFile(static_cast<int>(scrutinize.getFile()) + static_cast<int>(checksmain[0].xdirection * i)));
                        validsquare.setRank(scrutinize.getFile() + checksmain[0].ydirection * i);
                        validsquares.insert(validsquare);
                        if (validsquare == scrutinize){
                            break;
                        }
                    }
                }
                vector<Moves> actualmoves;
                for (size_t i = 0; i < moves.size(); ++i){
                    if (gameboard.Gameboard[moves[i].start.getFile()][moves[i].start.getRank()]->getName() != "KING"){
                        auto it = validsquares.find(moves[i].start);
                        if (it == validsquares.end()){
                            actualmoves.push_back(moves[i]);
                        }
                    }
                }
                return actualmoves;
            }
            else {
                moves = gameboard.Gameboard[scrutinize.getFile()][scrutinize.getRank()]->getValidMoves(gameboard);
            }

        }
        else {
            moves = possiblemoves();
        }

    return moves;

        // for (size_t i = 0; i < moves.size(); ++i){
        //     makeMove(moves[i]);
        //     // computerturn = computerturn ? false : true;
        //     // //switch turns momentarily
        //     if (!incheck()){
        //         actualmoves.push_back(moves[i]);
        //     }

        //     unmakeMove(moves[i]);

        // }

        // if (actualmoves.size() == 0){
        //     if (incheck()){ checkmate = true;} 
        //     else {stalemate = true;}
        // }
        // else {
        //     checkmate = false;
        //     stalemate = false;
        // }      

    }

    bool squareunderattack(){
        computerturn = computerturn ? false : true;
        //switch turns momentarily

        Location scrutiny;   
        if (computerturn){
            scrutiny = computercolor == white ? whitekinglocation : scrutiny = blackkinglocation;
        }
        else {
            scrutiny = humancolor == white ? whitekinglocation : scrutiny = blackkinglocation;
        }

        vector<Moves> opps = possiblemoves();
        computerturn = computerturn ? false : true;

        for (size_t i = 0; i < opps.size(); ++i){
            if (opps[i].end == scrutiny){ 
                //switch turns back
                // cout << (computerturn ? computercolor : humancolor) << "is in check! Protect your king.\n";
                return true;
            }
        }
        return false;

    }

    bool incheck(){
        if (computerturn){
            return computercolor == white ? squareunderattack() : squareunderattack();
        }
        else {
            return humancolor == white ? squareunderattack() : squareunderattack();
        }
    }


    void prompter(){
        char filestart;
        size_t rankstart;
        char fileend;
        size_t rankend;
        char junk;
        int val = 0;
        string humancolorstring;

        cout << "Welcome to Sana's AI chess!\n Please specify which color you want to be [WHITE/BLACK]:\n";
        while (humancolorstring != "WHITE" && humancolorstring != "BLACK" ){
            cin >> humancolorstring;

            if (humancolorstring == "WHITE"){
                humancolor = white;
                computercolor = black;
            }
            else if (humancolorstring == "BLACK"){
                humancolor = black;
                computercolor = white;
            }
            else {
                humancolorstring.erase();
                cout << "Unknown input. Try Again: \n";
            }
        }


        if (computercolor == white){
            computerturn = true;
        }

        while (!checkmate || !stalemate){
            if (computerturn){
                val = choosemove(2, true, computercolor);
                play();
                computerturn = false;
            }
            else{
                cout << "Choose a piece to move. Reply in [file number rank number], [file number rank number], ex. A5, C6.\n";
                while ((filestart != 'A' && filestart != 'B' && filestart != 'C' && filestart != 'D' && filestart != 'E'&& 
                filestart != 'F'&& filestart != 'G' && filestart != 'H') || (fileend != 'A' && fileend != 'B' && fileend != 'C' &&
                fileend != 'D' && fileend != 'E' && fileend != 'F'&& fileend != 'G' && fileend != 'H') || (rankstart != 0 && 
                rankstart != 1 && rankstart != 2 && rankstart != 3 && rankstart != 4 && rankstart != 5 && rankstart != 6 && 
                rankstart != 7) || (rankend != 0 && rankend != 1 && rankend != 2 && rankend != 3 && rankend != 4 && 
                    rankend != 5 && rankend != 6 && rankend != 7)){
                    cin >> filestart;
                    cin >> rankstart;
                    cin >> junk;
                    cin >> fileend;
                    cin >> rankend;

                    bool tryagain = false;
                    if (filestart != 'A' && filestart != 'B' && filestart != 'C' && filestart != 'D' && filestart != 'E'&& 
                    filestart != 'F'&& filestart != 'G' && filestart != 'H' ){
                        filestart = ' ';
                        cout << "Invalid file start.\n";
                        tryagain = true;
                    }

                    if (fileend != 'A' && fileend != 'B' && fileend != 'C' && fileend != 'D' && fileend != 'E'&& 
                    fileend != 'F'&& fileend != 'G' && fileend != 'H' ){
                        filestart = ' ';
                        cout << "Invalid file end.\n";
                        tryagain = true;
                    }

                    if (rankstart != 0 && rankstart != 1 && rankstart != 2 && rankstart != 3 && rankstart != 4 && 
                    rankstart != 5 && rankstart != 6 && rankstart != 7 ){
                        cout << "Invalid rank start.\n";
                        tryagain = true;
                    }

                    if (rankend != 0 && rankend != 1 && rankend != 2 && rankend != 3 && rankend != 4 && 
                    rankend != 5 && rankend != 6 && rankend != 7 ){
                        cout << "Invalid rank end.\n";
                        tryagain = true;
                    }

                    if (tryagain){
                        cout << "Try again: \n"; 
    
                    }
                }

                Location start(Location::CharToFile(filestart), rankstart);
                Location end(Location::CharToFile(fileend), rankend);
                besthumanmove.setMove(start, end);
                play();
                printBoard();
                computerturn = true;
            }
        }
        

        cout << "Game Over! " << winningplayer << "wins.\n";
    }
};

int main(){
    Chess obj;
    obj.creation();
    obj.printBoard();
    obj.prompter();
}