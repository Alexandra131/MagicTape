#include "fct.h"

// Corcodel Alexandra Andreea 315cb

/* Aloca un element de tip TCelula2 si returneaza pointerul aferent */
TLista2 AlocCelula2(char x) {
    TLista2 aux = (TLista2)malloc(sizeof(TCelula2));
    if (!aux) {
        return NULL;
    }
    aux->info = x;
    aux->pre = aux->urm = NULL;
    return aux;
}

/* Creeaza santinela pentru lista folosita */
TLista2 InitLista2() {
    TLista2 aux = (TLista2)malloc(sizeof(TCelula2));
    if (!aux) {
        return NULL;
    }
    aux->info = 0; /* informatia din santinela are valoarea 0 */
    aux->pre = NULL;
    aux->urm = NULL;
    return aux;
}

/* Citeste de la tastatura numere de adaugat in lista */
TLista2 CitireLista2(int *dimLista) {
    TLista2 L = NULL, aux = NULL, ultim = NULL;
    int x = 0;

    *dimLista = 0;
    L = InitLista2(); /* creeaza santinela */
    if (!L)
        return NULL;
    ultim = L;
    printf("Introduceti numerele de adaugat in lista:\n");
    while (scanf("%i", &x) == 1)
    { /* se citesc numere pana cand se citeste un caracter */
        aux = AlocCelula2(x);
        if (!aux)
            return L;
        ultim->urm = aux;
        aux->pre = ultim;
        ultim = aux;

        (*dimLista)++;
    }

    return L;
}

/* Afisare continut lista */

/* Distrugere lista */
void DistrugeLista2(TLista2 *aL)
{
    TLista2 p = (*aL)->urm, aux = NULL;
    while (p != NULL)
    { /* distrugere elementele listei */
        aux = p;
        p = p->urm;
        free(aux);
    }

    free(*aL); /* distrugere santinela */
    *aL = NULL;
}
