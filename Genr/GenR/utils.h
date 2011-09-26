#ifndef UTILS_H
#define UTILS_H

#include "taulell.h"
#include "objecte.h"

struct buff {
    Taulell *tempT;
    bool *llest;
    Objecte *O;
};

struct buff_multi {
    Taulell *tempT;
    bool *llest;
    Objecte *O1;
    Objecte *O2;
};

#endif
