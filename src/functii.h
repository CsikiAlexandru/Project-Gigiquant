#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <string.h>

struct Nod
{
    double valoare;
    double randament;
    struct Nod *next;
};
struct Elem
{
    double val;
    struct Elem *next;
};
struct Elem_coada
{
    int ziua;
    double val;
    char nume_oras[20];
    struct Elem_coada *next;
};
typedef struct Nod nod;
typedef struct Elem nod_stiva;
typedef struct Elem_coada nod_coada;

struct Q
{
    nod_coada *front, *rear;
};
typedef struct Q Queue;

nod *creare_nod();

void citire(FILE *f, nod *head, int *n);
void afisare(nod *head);
void calcul_randament_mediu(nod *head, int n, double *rand_mediu);
void calcul_volatilitate(nod *head, int n, double rand_mediu, double *volat);
void calcul_shape_ratio(double rand_mediu, double volat, double *shape_ratio);
void afisare_fisier(FILE *f2, double rand_mediu, double volat, double shape_ratio);
void stergere_lista(nod **head);

// void push(nod_stiva **top, double v);
// int isEmpty_stiva(nod_stiva *top);
// double pop(nod_stiva **top);
void deleteStack(nod_stiva **top);

Queue *createQueue();
// int isEmpty_coada(Queue *q);
// void enQueue(Queue *q,int zi, double v, char nume_oras[20]);
// void deQueue(Queue *q, FILE *f);
void deleteQueue(Queue **q);

void citire_stive(FILE *f1, nod_stiva **vector_stive, char nume_oras[][20]);
void rezolvare_cerinta(nod_stiva **vector_stive, char nume_oras[3][20], Queue *coada);
void afisare_coada(Queue *coada, FILE *f2);