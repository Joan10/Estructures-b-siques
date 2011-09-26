#include "taulell.h"


using namespace std;

Taulell::Taulell (int cas_x, int cas_y){

//    m_stsbar = parent->GetStatusBar();
    try {

        if (cas_x >= MAX_OBJ_X || cas_y >= MAX_OBJ_Y ) throw ResolucioNoValida;

        numObjectes = 0;

        for (int i = 0; i < MAX_OBJ_X; i++) {
            for (int j = 0; j < MAX_OBJ_Y; j++) {
                v_taulell[i][j].actiu = false;
            }
        }

        this->CAS_X = cas_x;
        this->CAS_Y = cas_y;

        this->lastId = 0;
        OAct = NULL;
        IdAct = 0;
        this->v_upd = true;
    } catch(exceptions e) {
        printf("Taulell::Taulell (wxFrame *parent, int res_x, int res_y, wxStatusBar *s) => Resolució incorrecte! \n ");

    }

}


Taulell::~Taulell() {

    delete OAct;

    for (int i = 0; i < MAX_OBJ_X; i++) {
        for (int j = 0; j < MAX_OBJ_Y; j++) {
            delete v_taulell[i][j].pO;
        }
    }

}

void Taulell::Posa(Objecte *O, Punt P){

    try{
        this->PosaEf(O, P);

    }catch(exceptions e){
        printf("Taulell::Posa(int x, int y, int Tipus) => No es pot col·locar a %i %i. \n", P.x(),P.y());
    }
    this->v_upd = true;
}

void Taulell::CanviaColor(Objecte *O, int R, int G, int B){

        O->CanviaColor(R,G,B);
        this->v_upd = true;
        //Refresh();

 }

void Taulell::Mou(Objecte *O, Punt Desti){

    try{
        this->MouEf(O, Desti);

    }catch(exceptions e){
        if (e == CoordBuida) printf("Taulell::Mou(T_ID id, int dest_x, int dest_y) => Identificador %i incorrecte! \n", O->treuId());
        else printf("Taulell::Mou(T_ID id, int dest_x, int dest_y) => No es pot moure a %i %i. \n", Desti.x(), Desti.y());
    }
    this->v_upd = true;
}


void Taulell::Mou(Punt Origen, Punt Desti){

    Objecte *O = ObjecteA(Origen);

    try{
        this->MouEf(O, Desti);

    }catch(exceptions e){

        if (e == CoordBuida) printf("Taulell::Mou(int x, int y, int dest_x, int dest_y) => Coordenada inicial %i %i incorrecte! \n", Origen.x(), Origen.y());
        else printf("Taulell::Mou(int x, int y, int dest_x, int dest_y) => No es pot moure a %i %i. \n",Desti.x(), Desti.y());
    }
    this->v_upd = true;
}



void Taulell::Rota(Objecte *O, sentit s){

    try {
        int x = O->pos_abs().x();
        int y = O->pos_abs().y();

        if (this->PotGirar(O,s)) {
            int i = O->it_primer();
            while (O->it_valid(i)) { //En haver comprovat que es pot girar, el treim del taulell.

                v_taulell[x+O->pos_rel(i).x()][y+O->pos_rel(i).y()].actiu = false;
                i = O->it_seg(i);
            }

            if (s == dreta ) O->RotaDret();
            else O->RotaEsq();

            i = O->it_primer();
            while (O->it_valid(i)) { //Llavors el giram i el tornam a col·locar.
                v_taulell[x+O->pos_rel(i).x()][y+O->pos_rel(i).y()].pO = O;
                v_taulell[x+O->pos_rel(i).x()][y+O->pos_rel(i).y()].actiu = true;
                i = O->it_seg(i);
            }

        }else { throw CoordIncorrecte; }

    }catch(exceptions e){

        if (s==dreta) printf("Taulell::Rota(T_ID id, sentit s) => No pot girar cap a la dreta! \n");
        else printf("Taulell::Rota(T_ID id, sentit s) => No pot girar cap a l'esquerra! \n");

    }
    this->v_upd = true;

//    Refresh();

}

void Taulell::TaulellBuit(){


    numObjectes = 0;
    for (int i = 0; i < MAX_OBJ_X; i++) {
        for (int j = 0; j < MAX_OBJ_Y; j++) {
            v_taulell[i][j].actiu = false;
        }
    }
    this->v_upd = true;


}

float Taulell::Distancia(Objecte *O1,Objecte *O2){


    Punt P1 = O1->posabs;
    Punt P2 = O2->posabs;

    int i1 = O1->it_primer();
    int i2 = O2->it_primer();

    int a,b,c,d;

    float val;
    float abs_min = 99999999;
    //Agafam les coordenades de cada quadre i les sumam a les de la posició on volem col·locar l'objecte per a tenir-lo sobre el taulell
    while (O1->it_valid(i1)) {
        while (O2->it_valid(i2)) {

            a = O1->pos_abs().x()+O1->pos_rel(i1).x();
            b = O2->pos_abs().x()+O2->pos_rel(i2).x();
            c = O1->pos_abs().y()+O1->pos_rel(i1).y();
            d = O2->pos_abs().y()+O2->pos_rel(i2).y();

            val = sqrt(pow((a - b),2) + pow((c - d),2)) ;
            if (val < abs_min) abs_min = val;

            i2 = O2->it_seg(i2);
        }
        i2 = O2->it_primer();
        i1 = O1->it_seg(i1);
    }

    return abs_min;
}




void Taulell::Pinta() {

    for (int j = -1; j <= numQuadresY(); j++) {
        for (int i = -1; i <= numQuadresX(); i++) {
            if (i == -1 || i == numQuadresX()) printf("|");
            else if (j == -1 || j == numQuadresY()) printf("--");

            if (i != -1 && i != numQuadresX() && j != -1  &&  j != numQuadresY()){
                if (v_taulell[i][j].actiu == true ) {
                    v_taulell[i][j].pO->Pinta();
                }else{
                    printf("0 ");
                }
            }

        }

        printf("\n");
    }


    //printf("Dist: %f \n", this->Distancia(ObjecteA(TaulaEq[0][0],TaulaEq[1][0]),ObjecteA(TaulaEq[0][1],TaulaEq[1][1])));

    printf("\n \n \n \n");
}


void Taulell::Pinta(Punt infesq, Punt supdret) {

    int x_infesq = infesq.x();
    int y_infesq = infesq.y();

    int x_supdret = supdret.x();
    int y_supdret = supdret.y();

    for (int j = y_infesq-1; j <= y_supdret; j++) {
        for (int i = x_infesq-1; i <= x_supdret; i++) {

            if (i == x_infesq-1 || i == x_supdret) printf("|");
            else if (j == y_infesq-1 || j == y_supdret) printf("--");

            if (i > x_infesq-1 && i < x_supdret && j > y_infesq-1  &&  j < y_supdret){
                if (v_taulell[i][j].actiu == true ) {
                    v_taulell[i][j].pO->Pinta();
                }else{
                    printf("0 ");
                }
            }

        }

        printf("\n");
    }
   // printf("Dist: %f \n", this->Distancia(ObjecteA(TaulaEq[0][0],TaulaEq[1][0]),ObjecteA(TaulaEq[0][1],TaulaEq[1][1])));

    printf("\n \n \n \n");
}



void Taulell::PosaEf(Objecte *O, Punt P){

        O ->Mou(P);
        int x = P.x();
        int y = P.y();

        lastId = lastId+1;
        O->assignaId(lastId); //Primer assignam l'identificador per poder reutilitzar el codi de esPotMoure, ja que si l'objecte
                              //no té ID no podem comparar i per tant no entrar al condicional de colisió de esPotMoure.

        if (!this->esPotMoure(O, P)) { throw CoordIncorrecte; }

        int i = O->it_primer();

        numObjectes++;

        //Agafam les coordenades de cada quadre i les sumam a les de la posició on volem col·locar l'objecte per a tenir-lo sobre el taulell
        while (O->it_valid(i)) {
            v_taulell[x+O->pos_rel(i).x()][y+O->pos_rel(i).y()].pO = O;
            v_taulell[x+O->pos_rel(i).x()][y+O->pos_rel(i).y()].actiu = true;

            i = O->it_seg(i);

        }

//        Refresh();



}

void Taulell::MouEf(Objecte *O, Punt Desti){


        int x = O->pos_abs().x();
        int y = O->pos_abs().y();

        if ( O == NULL) { throw CoordBuida; }
        if (!this->esPotMoure(O, Desti)) { throw CoordIncorrecte; }

        int i = O->it_primer();

        while (O->it_valid(i)) {
            v_taulell[x+O->pos_rel(i).x()][y+O->pos_rel(i).y()].actiu = false;
            i = O->it_seg(i);
        }

        O ->Mou(Desti);
        x = O->pos_abs().x();
        y = O->pos_abs().y();

        i = O->it_primer();

        while (O->it_valid(i)) {
            v_taulell[x+O->pos_rel(i).x()][y+O->pos_rel(i).y()].pO = O;
            v_taulell[x+O->pos_rel(i).x()][y+O->pos_rel(i).y()].actiu = true;
            i = O->it_seg(i);
        }

//        Refresh();

}


/*  Retorna vertader si lobjecte es pot moure a la posició donada. Cal tenir
    en compt que numQuadresX i numQuadresY retornen el número de quadres, però
    els començam a comptar des de 0, per tant no podem accedir al quadre número
    "numQuadresX()", "numQuadresY()"
    Llavors també cal mirar si a la posició ja hi ha un altre objecte (el node està actiu)
    sempre que aquest no sigui el mateix (comprovam que no ho siguin)
*/
bool Taulell::esPotMoure (Objecte *O,  Punt Desti){

    int dest_x = Desti.x();
    int dest_y = Desti.y();

    if (dest_x < 0 || dest_y < 0 || dest_x >= numQuadresX() || dest_y >=numQuadresY() ) return false;

    int it = O->it_primer();

    int x;
    int y;

    //Comprovam que no toqui els límits.
    while (O->it_valid(it)) {

        x = O->pos_rel(it).x()+dest_x;
        y = O->pos_rel(it).y()+dest_y;

        if (x >= numQuadresX() || x<0 || y>=numQuadresY()|| y<0)

            return false;

        if (this->v_taulell[x][y].actiu == true) && !(O->SomElMateix(this->v_taulell[x][y].pO))
            return false;

        if (v_taulell[x][y].p0->EnsTocam(O))
        //EnsTocam dirà si, donats dos objectes, les seves boundingbox es tocaran al proxim moviment.
        it = O->it_seg(it);
    }

//|| (this->v_taulell[x][y].actiu == true &&
//            !(O->SomElMateix(this->v_taulell[x][y].pO))))

    return true;
}

bool Taulell::PotGirar (Objecte *O, sentit s){


    int it = O->it_primer();

    int posActX = O->pos_abs().x();
    int posActY = O->pos_abs().y();
    int x;
    int y;

    while (O->it_valid(it)) {

        if (s == dreta ){
            x = -1*O->pos_rel(it).y() + posActX; //Calculam la nova posició per cada quadre.
            y = O->pos_rel(it).x() + posActY;
        }else{
            x = O->pos_rel(it).y() + posActX; //Calculam la nova posició per cada quadre.
            y = -1*O->pos_rel(it).x() + posActY;
        }

        if ((x >= numQuadresX() || x<0 || y>=numQuadresY()|| y<0) || (this->v_taulell[x][y].actiu == true &&
            !(O->SomElMateix(this->v_taulell[x][y].pO))))

            return false;

        it = O->it_seg(it);
    }
    return true;
}


bool Taulell::ExisteixObjecte (Punt P){
        int x = P.x();
        int y = P.y();
        if( x >= numQuadresX() || y >= numQuadresY() || x<0 || y<0) return false;
        if( v_taulell[x][y].actiu == false) return false;

        return v_taulell[x][y].actiu;

}




Objecte * Taulell::ObjecteA (Punt P){
    try{

        int x = P.x();
        int y = P.y();

        if( x >= numQuadresX() || y >= numQuadresY() || x<0 || y<0) throw CoordIncorrecte;
        if( v_taulell[x][y].actiu == false) throw CoordIncorrecte;

        return v_taulell[x][y].pO;

    }catch(exceptions e){
        printf("Taulell::ObjecteA (int x, int y) => Coordenades incorrectes! \n");
        return NULL;
    }
}



