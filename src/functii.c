#include "functii.h"
// inceput functii pentru task1
nod *creare_nod()
{
    nod *new_node;
    new_node = (nod *)malloc(sizeof(nod));
    if (new_node == NULL)
        exit(1);
    new_node->next = NULL;
    new_node->randament = 0;
    new_node->valoare = 0;
    return new_node;
}
void citire(FILE *f, nod *head, int *n)
{
    nod *aux;
    aux = head;

    fscanf(f, "%d", n);
    if ((*n) > 1)
    {
        fscanf(f, "%lf", &aux->valoare); // initializarea primului nod este diferita fata de celelalte deoarece acesta nu are randament
    }

    for (int i = 1; i < *n; i++) // pentru a putea calcula randamentul fiecarui nod in timpul citirii, ne folosim de aux, unde se afla ultimul nod
    {
        nod *new_node;
        new_node = creare_nod();
        fscanf(f, "%lf", &new_node->valoare);
        new_node->randament = ((new_node->valoare - aux->valoare) / aux->valoare);
        aux->next = new_node;
        aux = aux->next;
    }
    return;
}
void afisare(nod *head)
{
    nod *aux;
    aux = head;

    while (aux != NULL)
    {
        printf("%lf %lf -> ", aux->valoare, aux->randament);
        aux = aux->next;
    }
    return;
}
void calcul_randament_mediu(nod *head, int n, double *rand_mediu)
{
    nod *aux;
    aux = head->next;
    double suma = 0;
    while (aux != NULL)
    {
        suma += aux->randament;
        aux = aux->next;
    }

    *rand_mediu = suma / (n - 1);
    return;
}
void calcul_volatilitate(nod *head, int n, double rand_mediu, double *volat)
{
    double sum = 0;
    nod *aux = head->next;

    while (aux != NULL)
    {
        sum += pow(aux->randament - rand_mediu, 2);
        aux = aux->next;
    }
    *volat = sqrt(sum / (n - 1));
    return;
}
void calcul_shape_ratio(double rand_mediu, double volat, double *shape_ratio)
{
    *shape_ratio = rand_mediu / volat;

    return;
}
void afisare_fisier(FILE *f2, double rand_mediu, double volat, double shape_ratio)
{
    volat = trunc((volat) * 1000.0) / 1000.0; // setam precizia la fix 3 zecimale
    shape_ratio = trunc((shape_ratio) * 1000.0) / 1000.0;
    rand_mediu = trunc((rand_mediu) * 1000.0) / 1000.0;

    fprintf(f2, "%.3lf\n%.3lf\n%.3lf\n", rand_mediu, volat, shape_ratio);
    return;
}
void stergere_lista(nod **head)
{
    nod *aux = (*head)->next;
    while (aux != NULL)
    {
        nod *aux2;
        aux2 = aux;
        aux = aux->next;
        free(aux2);
    }
    free(*head);
    *head = NULL;
    return;
}
// sfarsit functii pentru task1
// inceput functii pentru task2
// functii pentru implementare stiva
static nod_stiva *creare_nod_stiva()
{
    nod_stiva *nod_st;
    nod_st = (nod_stiva *)malloc(sizeof(nod_stiva));
    if (nod_st == NULL)
        exit(1);
    nod_st->next = NULL;
    nod_st->val = -1;

    return nod_st;
}
static void push(nod_stiva **top, double v)
{
    nod_stiva *newNode;
    newNode = creare_nod_stiva();
    newNode->val = v;
    newNode->next = *top;
    *top = newNode;
}
static int isEmpty_stiva(const nod_stiva *top)
{
    return top == NULL;
}
static double pop(nod_stiva **top)
{
    if (isEmpty_stiva(*top))
        return INT_MIN;

    nod_stiva *temp = (*top);
    double aux = temp->val;
    *top = (*top)->next;
    free(temp);
    return aux;
}
void deleteStack(nod_stiva **top)
{

    while ((*top) != NULL)
    {
        nod_stiva *temp;
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}

// functii pentru implementare coada
Queue *createQueue()
{
    Queue *q;
    q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
        exit(1);
    q->front = q->rear = NULL;
    return q;
}
static int isEmpty_coada(const Queue *q)
{
    return (q->front == NULL);
}
static void enQueue(Queue *q, int zi, double v, const char nume_oras[20])
{
    nod_coada *newNode = (nod_coada *)malloc(sizeof(nod_coada));
    if (newNode == NULL)
        exit(1);
    newNode->ziua = zi;
    newNode->val = v;
    strcpy(newNode->nume_oras, nume_oras);
    newNode->next = NULL;

    if (q->rear == NULL)
        q->rear = newNode;
    else
    {
        (q->rear)->next = newNode;
        (q->rear) = newNode;
    }

    if (q->front == NULL)
        q->front = q->rear;
}
static void deQueue(Queue *q, FILE *f) // elimina elementul si il scrie in fisier
{
    nod_coada *aux;
    if (isEmpty_coada(q))
        return;
    aux = q->front;
    q->front = (q->front)->next;
    if (q->front == NULL)
        q->rear = NULL;

    fprintf(f, "ziua %d - %.2lf - %s\n", aux->ziua, aux->val, aux->nume_oras);

    free(aux);
    return;
}
void deleteQueue(Queue **q)
{

    while (!isEmpty_coada(*q))
    {
        nod_coada *aux;
        aux = (*q)->front;
        (*q)->front = (*q)->front->next;
        free(aux);
    }
    free(*q);
    *q = NULL;
}
// functii pentru rezolvarea cerintei efective
void citire_stive(FILE *f1, nod_stiva **vector_stive, char nume_oras[][20])
{
    for (int i = 0; i < 3; i++)
    {
        fgets(nume_oras[i], 20, f1);
        nume_oras[i][strlen(nume_oras[i]) - 1] = '\0';

        double val;
        while (fscanf(f1, "%lf", &val) == 1)
        {
            push(&vector_stive[i], val);
        }
    }

    return;
}
void rezolvare_cerinta(nod_stiva **vector_stive, char nume_oras[3][20], Queue *coada)
{
    if (vector_stive == NULL)
        return;
    int i = 0;
    while (!isEmpty_stiva(vector_stive[0]) && !isEmpty_stiva(vector_stive[1]) && !isEmpty_stiva(vector_stive[2]))
    {

        i++;
        double val_st1, val_st2, val_st3;
        val_st1 = pop(&vector_stive[0]);
        val_st2 = pop(&vector_stive[1]);
        val_st3 = pop(&vector_stive[2]);

        if (val_st1 == val_st2 && val_st1 != val_st3)
        {
            double diferenta = val_st3 - val_st1;
            if (diferenta < 0)
                diferenta *= -1;
            enQueue(coada, i, diferenta, nume_oras[2]);
        }
        else if (val_st1 == val_st3 && val_st1 != val_st2)
        {
            double diferenta = val_st2 - val_st1;
            if (diferenta < 0)
                diferenta *= -1;
            enQueue(coada, i, diferenta, nume_oras[1]);
        }
        else if (val_st2 == val_st3 && val_st2 != val_st1)
        {
            double diferenta = val_st1 - val_st2;
            if (diferenta < 0)
                diferenta *= -1;
            enQueue(coada, i, diferenta, nume_oras[0]);
        }
    }

    return;
}
void afisare_coada(Queue *coada, FILE *f2)
{
    while (!isEmpty_coada(coada))
    {
        deQueue(coada, f2);
    }
    return;
}
// sfarsit functii task2