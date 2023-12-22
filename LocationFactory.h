#include "Location.h"
#ifndef LOCATIONFACTORY_H
#define LOCATIONFACTORY_H

class LocationFactory{
    public:
    static Location build(Location current, int Fileoffset, int Rankoffset){
        return Location(static_cast<File>(current.getFile() + Fileoffset), current.getRank() + static_cast<size_t>(Rankoffset));
    }

};
#endif