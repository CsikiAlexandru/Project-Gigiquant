#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

#define MAX_SYM 5
#define n_t3 10

typedef struct StockList
{
    int indice_actiune;
    struct StockList *next;
} StockList;

typedef struct TreeNode
{
    StockList *stocks;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct vector
{
    double ultima_val; // pt fiecare actiune stocam ultima ei valoare, si ultimul nod care o cracterizeaza
    TreeNode *nod_ultim;
    char drum[10]; // stim sigur ca nu vor fi mai mult de 9 zile!!! ( poate ar fi cazul sa implementam dinamic )
} vector;

TreeNode *creare_nod_arbore();
void citire_task3(FILE *f1, TreeNode *root);
// void afisare_indice_superior(FILE *f2, int i, StockList *aux_lista, int *prim);
void rezolvare_cerinta_task3(FILE *f2, TreeNode *root);
void eliberare_memorie(TreeNode *root);