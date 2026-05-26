#include "functii_task3.h"
char actiuni[10][MAX_SYM];
int h_arbore;
vector v[10];

TreeNode *creare_nod_arbore()
{
    TreeNode *new_node;
    new_node = (TreeNode *)malloc(sizeof(TreeNode));
    if (new_node == NULL)
        exit(1);
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->stocks = NULL;
    return new_node;
}

void citire_task3(FILE *f1, TreeNode *root)
{
    for (int i = 0; i < n_t3; i++)
    {
        v[i].ultima_val = -1;
        v[i].drum[0] = '\0';
    }

    for (int i = 0; i < n_t3; i++)
    {
        char s[5], car;
        for (int j = 0; j < 4; j++)
        {
            fscanf(f1, "%c", &car);
            s[j] = car;
        }
        fgetc(f1);
        s[4] = '\0';

        v[i].nod_ultim = root;
        strcpy(actiuni[i], s);

        StockList *new_stock;
        new_stock = (StockList *)malloc(sizeof(StockList));
        if (new_stock == NULL)
            exit(1);
        new_stock->indice_actiune = i;
        new_stock->next = root->stocks;
        root->stocks = new_stock;
    }

    double x;
    h_arbore = -1;
    while (fscanf(f1, "%lf", &x) == 1)
    {
        h_arbore++;
        if (v[0].ultima_val == -1)
            v[0].ultima_val = x;
        else
        {
            if (v[0].nod_ultim->left == NULL)
            {
                v[0].nod_ultim->left = creare_nod_arbore();
                v[0].nod_ultim->right = creare_nod_arbore();
            }
            if (x >= v[0].ultima_val)
            {
                v[0].nod_ultim = v[0].nod_ultim->right;
                v[0].drum[h_arbore - 1] = 'r';
                v[0].drum[h_arbore] = '\0';
            }
            else
            {
                v[0].nod_ultim = v[0].nod_ultim->left;
                v[0].drum[h_arbore - 1] = 'l';
                v[0].drum[h_arbore] = '\0';
            }

            StockList *new_stock;
            new_stock = (StockList *)malloc(sizeof(StockList));
            if (new_stock == NULL)
                exit(1);
            new_stock->indice_actiune = 0;
            new_stock->next = v[0].nod_ultim->stocks;
            v[0].nod_ultim->stocks = new_stock;
            v[0].ultima_val = x;
        }

        for (int i = 1; i < n_t3; i++)
        {
            fgetc(f1);
            fscanf(f1, "%lf", &x);
            if (v[i].ultima_val == -1)
                v[i].ultima_val = x;
            else
            {
                if (v[i].nod_ultim->left == NULL)
                {
                    v[i].nod_ultim->left = creare_nod_arbore();
                    v[i].nod_ultim->right = creare_nod_arbore();
                }
                if (x >= v[i].ultima_val)
                {
                    v[i].nod_ultim = v[i].nod_ultim->right;
                    v[i].drum[h_arbore - 1] = 'r';
                    v[i].drum[h_arbore] = '\0';
                }
                else
                {
                    v[i].nod_ultim = v[i].nod_ultim->left;
                    v[i].drum[h_arbore - 1] = 'l';
                    v[i].drum[h_arbore] = '\0';
                }

                StockList *new_stock;
                new_stock = (StockList *)malloc(sizeof(StockList));
                if (new_stock == NULL)
                    exit(1);
                new_stock->indice_actiune = i;
                new_stock->next = v[i].nod_ultim->stocks;
                v[i].nod_ultim->stocks = new_stock;
                v[i].ultima_val = x;
            }
        }
    }
}

static void afisare_indice_superior(FILE *f2, int i, StockList *aux_lista, int *prim)
{
    if (aux_lista != NULL)
    {
        afisare_indice_superior(f2, i, aux_lista->next, prim);
        if (aux_lista->indice_actiune > i)
        {
            if (*prim != 0)
                fprintf(f2, "\n");
            else
                *prim = 1;

            fprintf(f2, "%s-%s", actiuni[i], actiuni[aux_lista->indice_actiune]);
        }
    }

    return;
}

void rezolvare_cerinta_task3(FILE *f2, TreeNode *root)
{
    int prim = 0;
    for (int i = 0; i < 10; i++)
    {
        TreeNode *aux;
        aux = root;
        int j = 0;
        while (v[i].drum[j] != '\0' && aux != NULL)
        {
            if (v[i].drum[j] == 'r')
                aux = aux->left;
            else
                aux = aux->right;
            j++;
        }
        if (aux != NULL)
            afisare_indice_superior(f2, i, aux->stocks, &prim);
    }
}
void eliberare_memorie(TreeNode *root)
{
    if (root == NULL)
        return;
    eliberare_memorie(root->left);
    eliberare_memorie(root->right);

    while (root->stocks != NULL)
    {
        StockList *aux;
        aux = root->stocks;
        root->stocks = root->stocks->next;
        free(aux);
        aux = NULL;
    }
    free(root);
}
