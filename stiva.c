#include "fct.h"

// Corcodel Alexandra Andreea 315cb

TStiva InitS()
{ // initializare stiva
    TStiva vf = NULL;
    vf = (TStiva)malloc(sizeof(TStiva)); // alocare o noua celula
    if (!vf)
        return NULL; // test alocare esuata
    (vf)->urm = NULL;
    vf->info = 0;
    return vf;
}

// implementare stiva, adaugare element in stiva
int Push(TStiva *vf, int x)
{
    TStiva aux = (TStiva)malloc(sizeof(TCelulaStiva)); // alocare o noua celula
    if (!aux)
        return 0; // test alocare esuata
    aux->info = x;
    aux->urm = NULL;
    aux->urm = *vf;
    *vf = aux;
    return 1;
}

// extragere element din stiva
int Pop(TStiva *vf, int *ax)
{
    TStiva aux = NULL;
    if (*vf == NULL)
        return 0;
    *ax = (*vf)->info;
    aux = *vf;
    *vf = aux->urm;
    free(aux); // eliberare celula
    return 1;
}

// distrugere stiva

void DistrugereS(TStiva *vf)
{
    TStiva aux = NULL;
    while (*vf)
    { // parcurgere stiva
        aux = *vf;
        *vf = (*vf)->urm;
        free(aux);
    }
}