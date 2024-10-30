#include "fct.h"

// Corcodel Alexandra Andreea 315cb

TCoada *InitQ() { /* creeaza coada vida cu elemente de dimensiune d;
         anumite implementari pot necesita si alti parametri */ 
  TCoada *c = NULL; /* spatiu pentru descriptor coada */
  c = (TCoada *)malloc(sizeof(TCoada));
  if (!c)
    return NULL; /* nu exista spatiu -> "esec" */

  c->inc = c->sf = NULL;
  return c; /* intoarce adresa descriptorului cozii */
}

int IntrQ(TCoada *c, int x, char y) /* adauga element la sfarsitul cozii */ {
  TLista aux = NULL;
  aux = (TLista)malloc(sizeof(TCelula)); /* aloca o noua celula */
  if (!aux)
    return 0; /* alocare imposibila -> "esec" */

  aux->info = x;
  aux->urm = NULL;
  aux->valoare = y;
  if (c->sf != NULL)  /* coada nevida */
    c->sf->urm = aux; /* -> leaga celula dupa ultima din coada */
  else                /* coada vida */
    c->inc = aux;     /* -> noua celula se afla la inceputul cozii */
  c->sf = aux;        /* actualizeaza sfarsitul cozii */
  return 1;           /* operatie reusita -> "succes" */
}

int ExtrQ(TCoada *c)
{ // extragere element din coada
  TLista aux = NULL;
  if (c->inc->urm == NULL)
  { // coada care contine un sg element
    aux = c->inc;
    free(aux); // eliberare celula
    c->inc = NULL;
    c->sf = NULL;
    return 1;
  }
  else if (c->inc->urm != NULL)
  { // coada care nu contine un sg el
    aux = c->inc;
    c->inc = aux->urm;
    free(aux); // eliberare celula
    return 1;
  }
  return 0;
}

void DistrQ(TCoada **c) /* distruge coada */
{
  TLista p = NULL, aux = NULL;
  p = (*c)->inc;
  while (p) // parcurgere
  {
    aux = p;
    p = p->urm;
    free(aux); // eliberare celula
  }
  free(*c);
  *c = NULL;
}

void AfisareQ(TCoada *c) /* afisare elementele cozii */
{
  TLista p = NULL;
  if (c->inc == NULL) /* coada vida */
  {
    printf("Coada vida\n");
    return;
  }
  printf("Elementele cozii: ");
  for (p = c->inc; p != NULL; p = p->urm)
    printf("%d %c ", p->info, p->valoare);
  printf("\n");
}
