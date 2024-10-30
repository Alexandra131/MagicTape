#include "fct.h"
#define sase 6
#define patru 4
// Corcodel Alexandra Andreea 315cb
// suprascrie val degetului
int WRITE(TBanda *banda, char caracter)
{
    if ((*banda)->deget->pre != NULL)
    { // se suprascrie doar  daca degetul e diferit de santinela
        (*banda)->deget->info = caracter;
        return 1;
    }
    return 0;
}

// afisare contiut banda
void SHOW(TBanda banda, FILE *fout)
{
    TLista2 p = banda->inceput->urm;
    while (p)
    {
        if (p == banda->deget)
            fprintf(fout, "|%c|", p->info); // in cazul in care dgetul se afla pe poz p->info
        else
            fprintf(fout, "%c", p->info);
        p = p->urm;
    }
    fprintf(fout, "\n");
}

// determinare caracter din pozitia degetului
void SHOW_CURRENT(TBanda *banda, FILE *fout)
{
    char r;
    r = (*banda)->deget->info;
    fprintf(fout, "%c\n", r);
}

// inserare caracter dreapta
int INSERT_RIGHT(TBanda *banda, char caracter)
{
    TLista2 aux = NULL;
    if ((*banda)->deget->urm == NULL)
    {                                // cazul in care ne aflam pe ultima celula
        aux = AlocCelula2(caracter); // alocam celula aux
        (*banda)->deget->urm = aux;
        aux->pre = (*banda)->deget;
        (*banda)->deget = (*banda)->deget->urm;
        return 1;
    }
    // cazul in care nu suntem pe ultima celula
    aux = AlocCelula2(caracter); // alocam celula aux
    aux->urm = (*banda)->deget->urm;
    aux->pre = (*banda)->deget;
    (*banda)->deget->urm = aux;
    aux->urm->pre = aux;
    (*banda)->deget = aux;
    return 0;
}

// inserare caracter stanga
int INSERT_LEFT(TBanda *banda, char caracter, FILE *fout)
{
    TLista2 aux = NULL;
    if ((*banda)->deget->pre->pre == NULL)
    {
        fprintf(fout, "ERROR\n");
        return 1; // degetl se afla langa santinela
    }
    aux = AlocCelula2(caracter); // alocare celula
    aux->urm = (*banda)->deget;
    aux->pre = (*banda)->deget->pre;
    aux->pre->urm = aux;
    (*banda)->deget->pre = aux;
    (*banda)->deget = aux;
    return 0;
}

// deplasarea la stanga pana la un anumit element
int MOVE_RIGHT_CHAR(TBanda *banda, char caracter)
{
    TLista2 aux = NULL;
    char x = '#';
    TLista2 copie_deget = (*banda)->deget; // folosim o copie a degetului
    if (copie_deget->info == caracter)
        return 0; // daca caracter =caract de pe poz degetului, nu se intampla nimic
    while (copie_deget->urm != NULL)
    { // parcurgem prin lista
        if (copie_deget->info != caracter)
        {
            copie_deget = copie_deget->urm;
        }
        else
            break;
    }
    if (copie_deget->urm == NULL && copie_deget->info == caracter)
    {                                  // caracterul se afla peultima pozitie din lista
        (*banda)->deget = copie_deget; // mutam degetul unde se afla copia
        return 1;
    }
    else if (copie_deget->urm == NULL)
    {                         // nu se gaseste caracterul sau avem doar o celula, diferita de caracter
        aux = AlocCelula2(x); // alocam celul a
        copie_deget->urm = aux;
        aux->pre = copie_deget;
        copie_deget = copie_deget->urm;
        (*banda)->deget = copie_deget;
        return 0;
    }
    else if (copie_deget->info == caracter)
    {
        (*banda)->deget = copie_deget; // daca se gaseste caracterul in lista
        return 1;
    }
}

// deplasarea la dreapta pana la un anumit element
int MOVE_LEFT_CHAR(TBanda *banda, char caracter, FILE *fout)
{
    TLista2 copie_deget = (*banda)->deget; // folosim copie
    if (copie_deget->info == caracter)
        return 0; // daca caracter =caract de pe poz degetului, nu se intampla nimic
    while (copie_deget != NULL)
    { // parcurgem prin lista
        if (copie_deget->info != caracter)
        {
            copie_deget = copie_deget->pre;
        }
        else
            break;
    }
    if (copie_deget == NULL)
    { // nu am gasit caracterul, si am parcurs toata lista
        fprintf(fout, "ERROR\n");
        return 0;
    }
    else if (copie_deget->info == caracter)
    {
        (*banda)->deget = copie_deget; // daca gasim caracterul dorit, mutam degetul
        return 1;
    }
}

// deplasarea la stanga a degetului
int MOVE_LEFT(TBanda *banda)
{
    if ((*banda)->deget->pre->pre == NULL)
    { // daca ne aflam langa santinela nu facem nimic
        return 0;
    }
    else if ((*banda)->deget->pre == NULL)
        return 0; // daca ne aflam pe santinela nu facem nimic
    else
    {
        (*banda)->deget = (*banda)->deget->pre; // degetul se muta la stanga
        return 1;
    }
}

// deplasarea la dreapta a el curent
int MOVE_RIGHT(TBanda *banda)
{
    TLista2 aux = NULL;
    char x = '#';
    if ((*banda)->deget->urm == NULL)
    {                         // daca suntem pe ultima celula
        aux = AlocCelula2(x); // alocare celula
        (*banda)->deget->urm = aux;
        aux->pre = (*banda)->deget;
        (*banda)->deget = (*banda)->deget->urm;
    }
    else
    {
        (*banda)->deget = (*banda)->deget->urm; // caz simplu, degetul se muta la dreapta
    }
    return 1;
}

// operatia de UNDO, care permite anularea ultiemie operatii
int UNDO(TStiva *vf_1, TStiva *vf_2, TBanda *banda, int *ax)
{
    Pop(vf_1, ax);   // extragem elementul din stiva vf_1
    Push(vf_2, *ax); // punem elementul extras in stiva vf_2
    if ((*ax) == patru)
    { // mutare la dreapta
        if ((*banda)->deget->urm == NULL)
            return 0;
        (*banda)->deget = (*banda)->deget->urm;
        return 1;
    }
    else if ((*ax) == sase)
    { // mutare la stanga
        MOVE_LEFT(banda);
        return 1;
    }
}
// operatia de REDO, care permite refacerea  ultiemie operatii
int REDO(TStiva *vf_2, TStiva *vf_1, TBanda *banda, int *ax)
{
    Pop(vf_2, ax);   // extragem elementul din stiva vf_2
    Push(vf_1, *ax); // punem elementul extras in stiva vf_1
    if ((*ax) == patru)
    {
        MOVE_LEFT(banda); // mutam degetul la stanga
        return 1;
    }
    else if ((*ax) == sase)
    { // mutare la dreapta
        if ((*banda)->deget->urm == NULL)
            return 0;
        (*banda)->deget = (*banda)->deget->urm;
        return 1;
    }
}