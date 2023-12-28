#ifndef LOCATION_H
#define LOCATION_H
#include <iostream>

enum File {
    A, B, C, D, E, F, G, H
};

class Location{
    private:
    File file;
    size_t Rank;

    public:
    Location() {}
    Location(File file, size_t Rank) : file(file), Rank(Rank) {}

    bool operator<(const Location& rhs) const {
        if (this->getRank() < rhs.getRank()) {
            return true;
        } else if (this->getRank() > rhs.getRank()) {
            return false;
        }

        return this->getFile() < rhs.getFile();
    }


    static std::string fileToString(File file) {
        switch (file) {
            case A: return "A";
            case B: return "B";
            case C: return "C";
            case D: return "D";
            case E: return "E";
            case F: return "F";
            case G: return "G";
            case H: return "H";
            default: return "Unknown";
        }
    }   

    static File CharToFile(char letter) {
        switch (letter) {
            case A: return A;
            case B: return B;
            case C: return C;
            case D: return D;
            case E: return E;
            case F: return F;
            case G: return G;
            case H: return H;
            default: return A;
        }
    } 

    size_t getRank() const{
        return Rank;
    }

    File getFile() const{
        return file;
    }

    void setRank(size_t r) {
        Rank = r;
    }

    void setFile(File f) {
        file = f;
    }
    
    bool operator== (const Location &rhs){
        return (rhs.file == this->file && rhs.Rank == this->Rank);
    }




};
#endif