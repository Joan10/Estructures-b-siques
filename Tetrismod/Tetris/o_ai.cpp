#include "taulell.h"
#include "o_ai.h"

using namespace std;

static void* do_loop(void* TO)
{
   // dTaulellObjecte *buff = ((dTaulellObjecte*)TO);

 //   Objecte *O = (*buff).pO;
    printf("id1: %i \n", 5);

//    for ( int i = 0; i<255; i++){
//        for ( int j = 0; j<255; j++){
//            for ( int k = 0; k<255; k++){
//                O->CanviaColor(i,j,k);
//                printf("provant: %i \n", O->treuId());
//            }
//        }
//    }


    /* terminate the thread */
    pthread_exit(NULL);
}
