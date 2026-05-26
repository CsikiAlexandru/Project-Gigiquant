#include "functii.h"
#include "functii_task3.h"
#include "functii_task4.h"

static void task1(FILE *f1, FILE *f2)
{
    int n = 0;
    double rand_mediu, volat, shape_ratio;
    nod *head;
    head = creare_nod();
    citire(f1, head, &n);
    afisare(head);
    calcul_randament_mediu(head, n, &rand_mediu);
    calcul_volatilitate(head, n, rand_mediu, &volat);
    calcul_shape_ratio(rand_mediu, volat, &shape_ratio);
    afisare_fisier(f2, rand_mediu, volat, shape_ratio);

    stergere_lista(&head);
}

static void task2(FILE *f1, FILE *f2)
{
    nod_stiva **vector_stive = (nod_stiva **)malloc(3 * sizeof(nod_stiva *));
    if (vector_stive == NULL)
        exit(1);

    for (int i = 0; i < 3; i++)
        vector_stive[i] = NULL;

    char nume_oras[3][20];
    citire_stive(f1, vector_stive, nume_oras);

    Queue *coada;
    coada = createQueue();

    rezolvare_cerinta(vector_stive, nume_oras, coada);
    afisare_coada(coada, f2);

    deleteQueue(&coada);

    for (int i = 0; i < 3; i++)
        deleteStack(&vector_stive[i]);

    free(vector_stive);
}

static void task3(FILE *f1, FILE *f2)
{
    TreeNode *root;
    root = creare_nod_arbore();

    citire_task3(f1, root);

    rezolvare_cerinta_task3(f2, root);
    eliberare_memorie(root);
    root = NULL;
}

static void task4(FILE *f1, FILE *f2)
{
    int n, k;
    double d, P_start, P_target;
    graf *g;

    citire_task4(f1, &n, &d, &k, &P_start, &P_target, &g); // P_start si P_target se intorc ca indexi !!!!!!!
    int index_start = P_start;
    int index_target = P_target;
    rezolvare_task4(f2, d, k, index_start, index_target, g);
    delete_graf(&g);
}

int main(int argc, const char *argv[])
{

    FILE *f1 = fopen(argv[1], "r");
    if (f1 == NULL)
        exit(1);
    FILE *f2 = fopen(argv[2], "w");
    if (f2 == NULL)
        exit(1);

    if (strstr(argv[1], "data1.in") != NULL ||
        strstr(argv[1], "data2.in") != NULL ||
        strstr(argv[1], "data3.in") != NULL ||
        strstr(argv[1], "data4.in") != NULL ||
        strstr(argv[1], "data5.in") != NULL)
    {
        task1(f1, f2);
    }
    else if (strstr(argv[1], "data6.in") != NULL ||
             strstr(argv[1], "data7.in") != NULL ||
             strstr(argv[1], "data8.in") != NULL ||
             strstr(argv[1], "data9.in") != NULL ||
             strstr(argv[1], "data10.in") != NULL)
    {
        task2(f1, f2);
    }
    else if (strstr(argv[1], "data11.in") != NULL ||
             strstr(argv[1], "data12.in") != NULL ||
             strstr(argv[1], "data13.in") != NULL ||
             strstr(argv[1], "data14.in") != NULL ||
             strstr(argv[1], "data15.in") != NULL)
    {
        task3(f1, f2);
    }
    else if (strstr(argv[1], "data16.in") != NULL ||
             strstr(argv[1], "data17.in") != NULL ||
             strstr(argv[1], "data18.in") != NULL ||
             strstr(argv[1], "data19.in") != NULL ||
             strstr(argv[1], "data20.in") != NULL)
    {
        task4(f1, f2);
    }

    fclose(f1);
    fclose(f2);

    return 0;
}
