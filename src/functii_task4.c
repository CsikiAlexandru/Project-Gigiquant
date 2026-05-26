#include "functii_task4.h"

static graf *creare_graf(int dim)
{
    graf *g;
    g = (graf *)malloc(sizeof(graf));
    if (g == NULL)
        exit(1);
    g->dim = dim;

    g->prob = (frac *)malloc(sizeof(frac) * dim);
    if (g->prob == NULL)
        exit(1);

    g->m_adiac = (frac **)malloc(sizeof(frac *) * dim);
    if (g->m_adiac == NULL)
        exit(1);
    for (int i = 0; i < dim; i++)
    {
        g->m_adiac[i] = (frac *)malloc(sizeof(frac) * dim);
        if (g->m_adiac[i] == NULL)
            exit(1);
    }

    for (int i = 0; i < dim; i++)
    {
        g->prob[i].numarator = 0;
        g->prob[i].numitor = 1; // pt a fi siguri ca nu impartim la 0
        for (int j = 0; j < dim; j++)
        {
            g->m_adiac[i][j].numarator = 0;
            g->m_adiac[i][j].numitor = 1; // pt a fi siguri ca nu impartim la 0
        }
    }

    return g;
}

void delete_graf(graf **g)
{
    free((*g)->prob);
    for (int i = 0; i < (*g)->dim; i++)
        free((*g)->m_adiac[i]);
    free((*g)->m_adiac);
    free((*g));
    (*g) = NULL;
}

static void fractie_ireductibila(long long *a, long long *b)
{
    if (*a == 0)
    {
        *b = 1;
        return;
    }

    long long co_a = (*a);
    long long co_b = (*b);
    while (co_b != 0)
    {
        long long rest = co_a % co_b;
        co_a = co_b;
        co_b = rest;
    }
    (*a) = (*a) / co_a;
    (*b) = (*b) / co_a;
}

void citire_task4(FILE *f1, int *n, double *d, int *k, double *P_start, double *P_target, graf **g)
{
    fscanf(f1, "%d%lf%d%lf%lf", n, d, k, P_start, P_target);

    double v_temp[*n + 1];
    // gasire min si max
    double max = *P_start;
    double min = max;
    if (*P_target < min)
        min = *P_target;
    if (*P_target > max)
        max = *P_target;
    for (int i = 0; i < *n; i++)
    {
        fscanf(f1, "%lf", &v_temp[i]);
        if (v_temp[i] < min)
            min = v_temp[i];
        if (v_temp[i] > max)
            max = v_temp[i];
    }
    // gata cu gasirea

    int index_min = (int)((min / (*d)) + 0.0001);
    int index_max = (int)((max / (*d)) + 0.0001);

    int dim_graf;
    dim_graf = index_max - index_min + 1;
    *g = creare_graf(dim_graf);

    // urmeaza sa parcurgem v_temp si sa completam matricea asociata grafului
    int v_cedari[dim_graf];
    for (int i = 0; i < dim_graf; i++)
        v_cedari[i] = 0;
    for (int i = 1; i < *n; i++)
    {
        int i_primire, i_cedare;
        i_primire = (int)((v_temp[i] / (*d)) + 0.0001) - index_min;
        i_cedare = (int)((v_temp[i - 1] / (*d)) + 0.0001) - index_min;
        (*g)->m_adiac[i_cedare][i_primire].numarator++;
        v_cedari[i_cedare]++;
    }

    for (int i = 0; i < dim_graf; i++)
        for (int j = 0; j < dim_graf; j++)
            if ((*g)->m_adiac[i][j].numarator != 0)
            {
                (*g)->m_adiac[i][j].numitor = v_cedari[i];
                fractie_ireductibila(&((*g)->m_adiac[i][j].numarator), &((*g)->m_adiac[i][j].numitor));
            }

    (*P_start) = (int)((*P_start) / (*d) + 0.0001) - index_min;
    (*P_target) = (int)((*P_target) / (*d) + 0.0001) - index_min;
}

static void afis_probabilitate(FILE *f2, const graf *g, int index_target)
{
    if (g->prob[index_target].numarator == 0 || g->prob[index_target].numitor == 1)
        fprintf(f2, "%lld", g->prob[index_target].numarator);
    else
        fprintf(f2, "%lld/%lld", g->prob[index_target].numarator, g->prob[index_target].numitor);
}

void rezolvare_task4(FILE *f2, int d, int k, int index_start, int index_target, graf *g)
{

    g->prob[index_start].numarator = 1;
    afis_probabilitate(f2, g, index_target);

    int dim = g->dim;
    for (int i = 1; i < k; i++)
    {

        frac prob_viitor[dim];
        for (int j = 0; j < dim; j++)
        {
            prob_viitor[j].numarator = 0;
            prob_viitor[j].numitor = 1;
        }

        for (int j = 0; j < dim; j++)
        {
            if (g->prob[j].numarator != 0)
            {
                for (int index_mtr = 0; index_mtr < dim; index_mtr++)
                {
                    if (g->m_adiac[j][index_mtr].numarator != 0)
                    {
                        // prob_viitor += g.prob[j] * g->m_adiac[j][index_mtr]
                        long long numarator_aux;
                        long long numitor_aux;
                        numarator_aux = g->prob[j].numarator * g->m_adiac[j][index_mtr].numarator;
                        numitor_aux = g->prob[j].numitor * g->m_adiac[j][index_mtr].numitor;

                        prob_viitor[index_mtr].numarator = prob_viitor[index_mtr].numarator * numitor_aux + numarator_aux * prob_viitor[index_mtr].numitor;
                        prob_viitor[index_mtr].numitor = prob_viitor[index_mtr].numitor * numitor_aux;

                        fractie_ireductibila(&prob_viitor[index_mtr].numarator, &prob_viitor[index_mtr].numitor);
                    }
                }
            }
        }

        for (int j = 0; j < dim; j++)
        {
            g->prob[j].numarator = prob_viitor[j].numarator;
            g->prob[j].numitor = prob_viitor[j].numitor;
        }
        fprintf(f2, "\n");
        afis_probabilitate(f2, g, index_target);
    }
}
