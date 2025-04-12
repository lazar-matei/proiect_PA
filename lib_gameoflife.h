#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define TASK1 1
#define TASK2 2
#define TASK3 3
#define TASK4 4

struct vecin{
    int morti;
    int vii;
};
typedef struct vecin VECIN;

struct poz{
    int linie;
    int coloana;
};
typedef struct poz Poz;

struct nod{
    Poz v;
    struct nod *next;
};
typedef struct nod Node;

struct stack_node{
    Node *top;
    struct stack_node *next;
};
typedef struct stack_node stackNode;


void citire_f_in(FILE *f_in, int *task, int *col, int *lin, int *gen, char **matr);
void scriere_f_out( FILE *f_out, char *matr, int lin, int col);
VECIN stare_vecini(char *matr, int poz_coloana, int poz_linie, int col, int lin);
void copy_matr(char *matr, char **cpy_matr, int lin, int col);
void rez_generatie(char *matr, int lin, int col, Node **top);

int isEmpty(const Node* top);
void push(Node** top, Poz v);
Poz pop(Node **top);
void deleteStack(Node** top);
void fprintStack(Node* top, FILE* f_out);
void printStack(Node* top);
void invertStack(Node**top);


