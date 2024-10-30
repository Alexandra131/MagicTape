#include "fct.h"
#define doi 2
#define trei 3
#define patru 4
#define cinci 5
#define sase 6
#define sapte 7
#define opt 8
#define noua 9
#define zece 10
#define unsprezece 11
#define doisprezece 12
#define douazeci 20
// Corcodel Alexandra Andreea 315cb

// afiseaza elementele unei liste

TLista2 AfisareLista2(TLista2 L)
{
   TLista2 p = L->urm;
   while (p != NULL)
   { /* parcurgere lista */
      printf("%c", p->info);
      p = p->urm;
   }
}

int main()
{
   FILE *fin = fopen("tema1.in", "rt");
   FILE *fout = fopen("tema1.out", "w+");
   TBanda banda = malloc(sizeof(TFila));
   banda->inceput = InitLista2();
   banda->inceput->urm = AlocCelula2('#');
   banda->deget = banda->inceput->urm;
   banda->deget->pre = banda->inceput;

   TStiva vf_1 = NULL, vf_2 = NULL;
   vf_1 = InitS(); // stiva 1 pe care o folosim pentru UNDO
   vf_2 = InitS(); // stiva 2 pe care o folosim pentru REDO

   TCoada *coada = NULL;
   coada = InitQ(); // initializare cozii

   int n = 0, i = 0, ax = 0;
   int instr = 0;
   char functia[douazeci];

   fscanf(fin, "%d", &n);
   fgets(functia, douazeci, fin);
   for (i = 1; i <= n; i++)
   {
      int nr = 0;
      fgets(functia, douazeci, fin);
      if (strstr(functia, F1))
      {
         nr = 1;
      }
      else if (strstr(functia, F2))
      {
         nr = doi;
      }
      else if (strstr(functia, F3))
      {
         nr = trei;
      }
      else if (strstr(functia, F5))
      {
         nr = cinci;
      }
      else if (strstr(functia, F7))
      {
         nr = sapte;
      }
      else if (strstr(functia, F4))
      {
         nr = patru;
      }
      else if (strstr(functia, F6))
      {
         nr = sase;
      }
      else if (strstr(functia, F8))
      {
         nr = opt;
      }
      else if (strstr(functia, F9))
      {
         nr = noua;
      }
      else if (strstr(functia, F10))
      {
         nr = zece;
      }
      else if (strstr(functia, F11))
      {
         nr = unsprezece;
      }
      else if (strstr(functia, F12))
      {
         nr = doisprezece;
      }

      if (nr >= 1 && nr <= sapte)
      {
         IntrQ(coada, nr, *(functia + strlen(functia) - doi)); // punem nr in coada care reprezinta functia
      }
      else if (nr == opt) // se executa operatiile din coada
      {
         if (coada->inc->info == 1)
         {
            WRITE(&banda, coada->inc->valoare);
         }
         else if (coada->inc->info == doi)
         {
            INSERT_LEFT(&banda, coada->inc->valoare, fout);
         }
         else if (coada->inc->info == trei)
         {
            INSERT_RIGHT(&banda, coada->inc->valoare);
         }
         else if (coada->inc->info == patru)
         {
            MOVE_LEFT(&banda);
            Push(&vf_1, patru);
         }
         else if (coada->inc->info == sase)
         {
            MOVE_RIGHT(&banda);
            Push(&vf_1, sase);
         }
         else if (coada->inc->info == sapte)
         {
            MOVE_RIGHT_CHAR(&banda, coada->inc->valoare);
         }
         else if (coada->inc->info == cinci)
         {
            MOVE_LEFT_CHAR(&banda, coada->inc->valoare, fout);
         }
         ExtrQ(coada);
      }

      else if (nr == noua)
      {
         SHOW_CURRENT(&banda, fout);
      }
      else if (nr == zece)
      {
         SHOW(banda, fout);
      }
      if (nr == unsprezece)
      {
         UNDO(&vf_1, &vf_2, &banda, &ax);
      }
      else if (nr == doisprezece)
      {
         REDO(&vf_2, &vf_1, &banda, &ax);
      }
   }
   fclose(fin);
   fclose(fout);
   DistrQ(&coada);
   DistrugereS(&vf_1);
   DistrugereS(&vf_2);
   DistrugeLista2(&(banda)->inceput);
   return 0;
}