#include "forma.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{
    Forma F1;

    F1.CreaFormaAleatoria();

    printf("%i %i %i %i \n",F1.x(0),F1.x(1),F1.x(2),F1.x(3));
    printf("%i %i %i %i \n",F1.y(0),F1.y(1),F1.y(2),F1.y(3));
    printf("%i",F1.TreuForma());

    Forma F2;

    F2.CreaFormaAleatoria();

    printf("%i %i %i %i \n",F2.x(0),F2.x(1),F2.x(2),F2.x(3));
    printf("%i %i %i %i \n",F2.y(0),F2.y(1),F2.y(2),F2.y(3));
    printf("%i",F2.TreuForma());

    return 0;
}
