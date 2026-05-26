#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>
struct f
{
    long long numarator;
    long long numitor;
};
typedef struct f frac;
struct gr
{
    frac **m_adiac;
    frac *prob;
    int dim;
};
typedef struct gr graf;

// graf *creare_graf(int dim);
void delete_graf(graf **g);
// void fractie_ireductibila(long long *a, long long *b);
void citire_task4(FILE *f1, int *n, double *d, int *k, double *P_start, double *P_target, graf **g);
// void afis_probabilitate(FILE *f2,const graf *g, int index_target);
void rezolvare_task4(FILE *f2, int d, int k, int index_start, int index_target, graf *g);
