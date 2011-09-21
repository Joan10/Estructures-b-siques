#include "taulell.h"


using namespace std;

Taulell::Taulell (int cas_x, int cas_y, wxStatusBar *s){

//    m_stsbar = parent->GetStatusBar();
    try {

        if (cas_x >= MAX_OBJ_X || cas_y >= MAX_OBJ_Y ) throw ResolucioNoValida;

        this->sb = s;

        numObjectes = 0;

        for (int i = 0; i < MAX_OBJ_X; i++) {
            for (int j = 0; j < MAX_OBJ_Y; j++) {
                v_taulell[i][j].actiu = false;
            }
        }

        for (int i = 0; i < MAX_OBJ_X * MAX_OBJ_Y; i++) {
            for (int j = 0; j < 2; j++) {
                TaulaEq[j][i] = -1; //Coordenada invàlida.
            }
        }

        this->CAS_X = cas_x;
        this->CAS_Y = cas_y;

        this->lastId = 0;
        OAct = NULL;
        IdAct = 0;

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

void Taulell::Posa(int x, int y, Objecte *O){

    try{
        this->PosaEf(O, x, y);

    }catch(exceptions e){
        printf("Taulell::Posa(int x, int y, int Tipus) => No es pot col·locar a %i %i. \n", x, y);
    }
}

 void Taulell::CanviaColor(Objecte *O, int R, int G, int B){

        O->CanviaColor(R,G,B);

        //Refresh();

 }


void Taulell::Mou(int x, int y, int dest_x, int dest_y){

    Objecte *O = ObjecteA(x,y);

    try{
        this->MouEf(O, dest_x, dest_y);

        TaulaEq[0][O->treuId()] = dest_x;
        TaulaEq[1][O->treuId()] = dest_y;

    }catch(exceptions e){

        if (e == CoordBuida) printf("Taulell::Mou(int x, int y, int dest_x, int dest_y) => Coordenada inicial %i %i incorrecte! \n", x, y);
        else printf("Taulell::Mou(int x, int y, int dest_x, int dest_y) => No es pot moure a %i %i. \n", dest_x, dest_y);
    }
}

void Taulell::Mou(Objecte *O, int dest_x, int dest_y){

    try{
        this->MouEf(O, dest_x, dest_y);

        TaulaEq[0][O->treuId()-1] = dest_x;
        TaulaEq[1][O->treuId()-1] = dest_y;

    }catch(exceptions e){
        if (e == CoordBuida) printf("Taulell::Mou(T_ID id, int dest_x, int dest_y) => Identificador %i incorrecte! \n", O->treuId());
        else printf("Taulell::Mou(T_ID id, int dest_x, int dest_y) => No es pot moure a %i %i. \n", dest_x, dest_y);
    }

}

void Taulell::Rota(Objecte *O, sentit s){

    try {
        int x = TaulaEq[0][O->treuId()-1];
        int y = TaulaEq[1][O->treuId()-1];

        if (this->PotGirar(O,x,y,s)) {

            int i = O->it_primer();
            while (O->it_valid(i)) { //En haver comprovat que es pot girar, el treim del taulell.
                v_taulell[x+O->Posx(i)][y+O->Posy(i)].actiu = false;

                i = O->it_seg(i);
            }

            if (s == dreta ) O->RotaDret();
            else O->RotaEsq();


            i = O->it_primer();
            while (O->it_valid(i)) { //Llavors el giram i el tornam a col·locar.
                v_taulell[O->Posx(i)+x][O->Posy(i)+y].pO = O;
                v_taulell[O->Posx(i)+x][O->Posy(i)+y].actiu = true;
                i = O->it_seg(i);
            }

        }else { throw CoordIncorrecte; }

    }catch(exceptions e){

        if (s==dreta) printf("Taulell::Rota(T_ID id, sentit s) => No pot girar cap a la dreta! \n");
        else printf("Taulell::Rota(T_ID id, sentit s) => No pot girar cap a l'esquerra! \n");

    }

//    Refresh();

}

void Taulell::TaulellBuit(){


    numObjectes = 0;
    for (int i = 0; i < MAX_OBJ_X; i++) {
        for (int j = 0; j < MAX_OBJ_Y; j++) {
            v_taulell[i][j].actiu = false;
        }
    }

    for (int i = 0; i < MAX_OBJ_X * MAX_OBJ_Y; i++) {
        for (int j = 0; j < 2; j++) {
            TaulaEq[j][i] = -1; //Coordenada invàlida.
        }
    }

}

float Taulell::Distancia(Objecte *O1,Objecte *O2){

    int x1 = TaulaEq[0][O1->treuId()-1];
    int y1 = TaulaEq[1][O1->treuId()-1];
    int x2 = TaulaEq[0][O2->treuId()-1];
    int y2 = TaulaEq[1][O2->treuId()-1];

    int i1 = O1->it_primer();
    int i2 = O2->it_primer();

    int a,b,c,d;

    float val;
    float abs_min = 99999999;
    //Agafam les coordenades de cada quadre i les sumam a les de la posició on volem col·locar l'objecte per a tenir-lo sobre el taulell
    while (O1->it_valid(i1)) {
        while (O2->it_valid(i2)) {

            a = x1+O1->Posx(i1);
            b = x2+O2->Posx(i2);
            c = y1+O1->Posy(i1);
            d = y2+O2->Posy(i2);

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
                    printf("  ");
                }
            }

        }

        printf("\n");
    }


    printf("Dist: %f \n", this->Distancia(ObjecteA(TaulaEq[0][0],TaulaEq[1][0]),ObjecteA(TaulaEq[0][1],TaulaEq[1][1])));

    printf("\n \n \n \n");
}


void Taulell::Pinta(int x_infesq, int y_infesq, int x_supdret, int y_supdret ) {


    for (int j = y_infesq-1; j <= y_supdret; j++) {
        for (int i = x_infesq-1; i <= x_supdret; i++) {

            if (i == -1 || i == x_supdret) printf("|");
            else if (j == -1 || j == y_supdret) printf("--");

            if (i != -1 && i != x_supdret && j != -1  &&  j != y_supdret){
                if (v_taulell[i][j].actiu == true ) {
                    v_taulell[i][j].pO->Pinta();
                }else{
                    printf("  ");
                }
            }

        }

        printf("\n");
    }
    printf("Dist: %f \n", this->Distancia(ObjecteA(TaulaEq[0][0],TaulaEq[1][0]),ObjecteA(TaulaEq[0][1],TaulaEq[1][1])));

    printf("\n \n \n \n");
}



void Taulell::PosaEf(Objecte *O, int x, int y){


        lastId = lastId+1;
        O->assignaId(lastId); //Primer assignam l'identificador per poder reutilitzar el codi de esPotMoure, ja que si l'objecte
                              //no té ID no podem comparar i per tant no entrar al condicional de colisió de esPotMoure.

        if (!this->esPotMoure(O, x, y)) { throw CoordIncorrecte; }

        TaulaEq[0][lastId-1] = x;
        TaulaEq[1][lastId-1] = y;

        int i = O->it_primer();

        numObjectes++;

        //Agafam les coordenades de cada quadre i les sumam a les de la posició on volem col·locar l'objecte per a tenir-lo sobre el taulell
        while (O->it_valid(i)) {
            v_taulell[O->Posx(i)+x][O->Posy(i)+y].pO = O;
            v_taulell[O->Posx(i)+x][O->Posy(i)+y].actiu = true;

            i = O->it_seg(i);

        }

//        Refresh();



}

void Taulell::MouEf(Objecte *O, int dest_x, int dest_y){


        if ( O == NULL) { throw CoordBuida; }
        if (!this->esPotMoure(O, dest_x, dest_y)) { throw CoordIncorrecte; }


        int x_anterior = TaulaEq[0][O->treuId()-1];
        int y_anterior = TaulaEq[1][O->treuId()-1];

        int i = O->it_primer();

        while (O->it_valid(i)) {
            v_taulell[x_anterior+O->Posx(i)][y_anterior+O->Posy(i)].actiu = false;
            i = O->it_seg(i);
            printf("@@ %i %i \n ", x_anterior+O->Posx(i), y_anterior+O->Posy(i));
        }

        i = O->it_primer();

        while (O->it_valid(i)) {
            v_taulell[O->Posx(i)+dest_x][O->Posy(i)+dest_y].pO = O;
            v_taulell[O->Posx(i)+dest_x][O->Posy(i)+dest_y].actiu = true;
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
bool Taulell::esPotMoure (Objecte *O, int dest_x, int dest_y){

    if (dest_x < 0 || dest_y < 0 || dest_x >= numQuadresX() || dest_y >=numQuadresY() ) return false;

    int it = O->it_primer();

    int x;
    int y;
    while (O->it_valid(it)) {
        x = O->Posx(it)+dest_x;
        y = O->Posy(it)+dest_y;
        if ((x >= numQuadresX() || x<0 || y>=numQuadresY()|| y<0) || (this->v_taulell[x][y].actiu == true &&
            this->v_taulell[x][y].pO->treuId() != O->treuId() ))

            return false;

        it = O->it_seg(it);
    }
    return true;
}

bool Taulell::PotGirar (Objecte *O, int posActX, int posActY, sentit s){


    int it = O->it_primer();

    int x;
    int y;

    while (O->it_valid(it)) {

        if (s == dreta ){
            x = -1*O->Posy(it) + posActX; //Calculam la nova posició per cada quadre.
            y = O->Posx(it) + posActY;
        }else{
            x = O->Posy(it) + posActX; //Calculam la nova posició per cada quadre.
            y = -1 * O->Posx(it) + posActY;
        }

        if ((x >= numQuadresX() || x<0 || y>=numQuadresY()|| y<0) || (this->v_taulell[x][y].actiu == true &&
            this->v_taulell[x][y].pO->treuId() != O->treuId() ))

            return false;

        it = O->it_seg(it);
    }
    return true;
}


bool Taulell::ExisteixObjecte (int x, int y){

        if( x >= numQuadresX() || y >= numQuadresY() || x<0 || y<0) return false;
        if( v_taulell[x][y].actiu == false) return false;

        return v_taulell[x][y].actiu;

}




Objecte * Taulell::ObjecteA (int x, int y){
    try{

        if( x >= numQuadresX() || y >= numQuadresY() || x<0 || y<0) throw CoordIncorrecte;
        if( v_taulell[x][y].actiu == false) throw CoordIncorrecte;

        return v_taulell[x][y].pO;

    }catch(exceptions e){
        printf("Taulell::ObjecteA (int x, int y) => Coordenades incorrectes! \n");
        return NULL;
    }
}



