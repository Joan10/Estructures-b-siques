#ifndef PUNT_H
#define PUNT_H

class Punt {

private:

    int X; int Y;

public:

    Punt operator=(Punt a) {

        this->X = a.x();
        this->Y = a.y();

        return *this;
    }

    Punt operator+(Punt a) {
        Punt *P = new Punt(a.x()+this->X,a.y()+this->Y);
        return *P;
    }

    bool operator==(const Punt P2) const {
        return(P2.X == this->X && P2.Y == this->Y);
    }

    Punt (int x, int y) { this->X = x; this->Y = y;}
    Punt () {}

    int x(){ return X;}
    int y(){ return Y;}

    void setX(int x) { this->X = x; }
    void setY(int y) { this->Y = y; }
    void set(int x, int y) { this->X = x; this->Y = y;}
};
#endif
