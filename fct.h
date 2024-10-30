
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Corcodel Alexandra Andreea 315cb

#define  F1 "WRITE"
#define  F2 "INSERT_LEFT"
#define  F3 "INSERT_RIGHT"
#define  F4 "MOVE_LEFT"
#define  F5 "MOVE_LEFT_CHAR"
#define  F6 "MOVE_RIGHT"
#define  F7 "MOVE_RIGHT_CHAR"
#define  F8 "EXECUTE"
#define F9 "SHOW_CURRENT"
#define F10 "SHOW"
#define F11 "UNDO"
#define F12 "REDO"

/* definire lista dublu inlantuita cu santinela */

typedef struct celula2 {
  int info;
  struct celula2 *pre, *urm;
} TCelula2, *TLista2;

typedef struct Banda {
  TLista2 inceput;
  TLista2 deget;
} TFila, *TBanda;


// structuriile pt coada
typedef struct celula {
  int info;
  char valoare;
  struct celula* urm;
} TCelula, *TLista;

typedef struct coada {
  TLista inc, sf;       /* adresa primei si ultimei celule */
} TCoada;

// structura pt stiva
typedef struct celst {
 int info;
 struct celst *urm;
} TCelulaStiva, *TStiva;

// fct stiva
TStiva  InitS();
int Push(TStiva * vf, int x);
int Pop(TStiva *vf, int *ax);
void DistrugereS (TStiva *vf);

TLista2 AlocCelula2(char x);
TLista2 InitLista2();
TLista2 CitireLista2(int* dimLista);
TLista2 CitireLista2(int* dimLista);
void DistrugeLista2(TLista2 *aL);
int WRITE(TBanda *banda, char caracter);
void SHOW(TBanda banda, FILE *fout);
void SHOW_CURRENT(TBanda *banda, FILE *fout);
int INSERT_RIGHT(TBanda *banda, char caracter);
int INSERT_LEFT(TBanda *banda, char caracter, FILE *fout);
int MOVE_RIGHT_CHAR(TBanda *banda, char caracter);
int MOVE_LEFT_CHAR(TBanda *banda, char caracter, FILE *fout);
int MOVE_LEFT(TBanda *banda);
int MOVE_RIGHT(TBanda *banda);
TCoada* InitQ();
int ExtrQ(TCoada *c);
int IntrQ(TCoada *c, int x, char y);
void DistrQ(TCoada **c);
TLista2 AfisareLista2( TLista2 L);
void AfisareQ(TCoada *c);
int UNDO(TStiva *vf_1, TStiva *vf_2, TBanda *banda, int *ax);
int REDO(TStiva *vf_2, TStiva *vf_1, TBanda *banda, int *ax);