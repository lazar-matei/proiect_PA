#include "lib_gameoflife.h"

void citire_f_in(FILE *f_in, int *task, int *col, int *lin, int *gen, char **matr)
{
    int i, j;
    fscanf(f_in, "%d%d%d%d", task, lin, col, gen);
    *matr = (char*)malloc(((*lin)) * ((*col)) * sizeof(char));
    while(*matr == NULL)
    {
        puts("eroare alocare matrice\n......\nretry\n");
        *matr = (char*)malloc((*lin) * (*col) * sizeof(char));
    }
    
    fgetc(f_in);
    
    for(i=0; i<(*lin); i++)
    {    
        for(j=0; j<(*col); j++)
        {
            fscanf(f_in, "%c", ((*matr) + i * (*col) + j));
        }
        fgetc(f_in);
    }
        
}

void scriere_f_out( FILE *f_out, char *matr, int lin, int col)
{
   
    int i, j;
    for(i=0; i<lin; i++)
    {
        for(j=0; j<col; j++)
        {
            fprintf( f_out, "%c", *(matr + i*col + j) );
        }
        fprintf(f_out, "\n");
    }
    fprintf(f_out, "\n");
}

VECIN stare_vecini(char *matr, int poz_coloana, int poz_linie, int col, int lin)
{
    int i, j;
    VECIN nr;
    nr.morti = nr.vii = 0;
    
    for( i = poz_linie - 1 ; i <= poz_linie + 1 ; i++ )
        for( j= poz_coloana - 1; j <= poz_coloana + 1; j++ )
            if((i>=0)&&(j>=0)&&(i<lin)&&(j<col)){
                if( *( matr + i * col + j ) == 'X' )
                    nr.vii++;
                else if( *( matr + i * col + j ) == '+' )
                    nr.morti++; 
            }

    if( *( matr + poz_linie * col + poz_coloana ) == 'X' )
        nr.vii--;
    else if( *( matr + poz_linie * col + poz_coloana ) == '+' )
        nr.morti--;
    

    return nr;
}


void copy_matr(char *matr, char **cpy_matr, int lin, int col)
{
    int i, j;
    *cpy_matr = (char*)malloc(lin * col * sizeof(char));
    while ((*cpy_matr) == NULL)
    {
        puts("eroare cpy_matr");
        *cpy_matr = (char*)malloc(lin * col * sizeof(char));
        
    }
    for(i=0; i<lin; i++)
        for(j=0; j<col; j++)
            *((*cpy_matr) + i*col + j) = *(matr + i*col + j) ;
    
}



void rez_generatie(char *matr, int lin, int col, Node **top)
{
    
    Poz v;
    int i, j;
    VECIN nr_vecini;
    char *matr_ctrl;
    matr_ctrl = NULL;
    copy_matr(matr, &matr_ctrl, lin, col);
    for(i=0; i<lin; i++)
        for(j=0; j<col; j++)
        {
            v.coloana = j;
            v.linie = i;
            nr_vecini = stare_vecini( matr_ctrl, j, i, col, lin);
            if( *( matr + i * col + j ) == 'X' )
                {
                    if ( (nr_vecini.vii < 2) || ( nr_vecini.vii > 3 ) ){
                        *( matr + i * col + j ) = '+';
                        push(top, v);
                    }
                    
                }
            else if( (*( matr + i * col + j ) == '+') && (nr_vecini.vii == 3) ){
                *( matr + i * col + j ) = 'X';
                push(top, v);
            }
        }
    free(matr_ctrl);
}

int isEmpty(const Node* top){
    return (top==NULL);
}


void push(Node** top, Poz v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->v.linie = v.linie;
    newNode->v.coloana = v.coloana;
    newNode->next = *top;
    *top = newNode;
}

Poz pop(Node** top) {
    Poz intMIN;
    intMIN.coloana = INT_MIN;
    intMIN.linie = INT_MIN;
    if (isEmpty(*top)) 
        return intMIN;
    Node *temp = (*top);
    Poz aux = temp->v;
    *top = (*top)->next;
    free(temp);
    return aux;
}

void deleteStack(Node** top) {
    
    while ((*top) != NULL) {  
        Node* temp;
        temp = *top;
        *top = (*top)->next;
        free(temp);
    }
}
void fprintStack(Node* top, FILE *f_out) {
    while (top->next != NULL) {
        fprintf(f_out, "%d ", top->v.linie);
        fprintf(f_out, "%d ", top->v.coloana);
        top = top->next;
    }
    fprintf(f_out, "%d ", top->v.linie);
    fprintf(f_out, "%d", top->v.coloana);
}
/*
void printStack(Node* top) {
    while (top != NULL) {
        printf("%d ", top->v.linie);
        printf("%d ", top->v.coloana);
        top = top->next;
    }
    printf("\n");
}
*/
void invertStack(Node**top)
{
    Node *aux_top =NULL;
    while(!isEmpty(*top))
    {
        
        push(&aux_top, pop(top));
        
    }
    
   deleteStack(top);
    (*top) = aux_top;
    
}
/*
void rez_generatie_bonus(char *matr, int col, Node *top)
{
    
    Poz v;
    int i, j;
    while(!isEmpty(top))
    {
        v = pop(top);
        if(*(matr + v.linie * col + v.coloana)=='X')
            *(matr + v.linie * col + v.coloana)='+';
        else *(matr + v.linie * col + v.coloana)='X';
    }
    
}
    */
/*
void preord_afis(T_Node *root, FILE *fout, int lin, int col)
{
    if(root !=NULL)
    {
        //scriere_f_out(fout, root->grila, lin, col);
        preord_afis(root->left, fout, lin, col);
        preord_afis(root->right, fout, lin, col);
    }
}
*/
char* rule1(char *matr, int lin, int col, Node **top)
{
    Poz v;
    int i, j;
    VECIN nr_vecini;
    char *matr_ctrl, *matr2use;
    matr_ctrl = NULL;
    copy_matr(matr, &matr_ctrl, lin, col);
    copy_matr(matr, &matr2use, lin, col);
    for(i=0; i<lin; i++)
        for(j=0; j<col; j++)
        {
            v.coloana = j;
            v.linie = i;
            nr_vecini = stare_vecini( matr_ctrl, j, i, col, lin);
            if( *( matr2use + i * col + j ) == 'X' )
                {
                    if ( (nr_vecini.vii < 2) || ( nr_vecini.vii > 3 ) ){
                        *( matr2use + i * col + j ) = '+';
                        push(top, v);
                        
                    }
                    
                }
            else if( (*( matr2use + i * col + j ) == '+') && (nr_vecini.vii == 3) ){
                *( matr2use + i * col + j ) = 'X';
                push(top, v);
            }
        }
    free(matr_ctrl);
    //free(matr);
    return matr2use;
}

char* rule2(char *matr, int lin, int col, Node **top)
{
    Poz v;
    int i, j;
    VECIN nr_vecini;
    char *matr_ctrl, *matr2use;
    matr_ctrl = NULL;
    copy_matr(matr, &matr_ctrl, lin, col);
    copy_matr(matr, &matr2use, lin, col);
    for(i=0; i<lin; i++)
        for(j=0; j<col; j++)
        {
            v.coloana = j;
            v.linie = i;
            nr_vecini = stare_vecini( matr_ctrl, j, i, col, lin);
            if( (*( matr2use + i * col + j ) == '+') && (nr_vecini.vii == 2) )
            {
                *( matr2use + i * col + j ) = 'X';
                push(top, v);
            }
        }
    free(matr_ctrl);
    //free(matr);
    return matr2use;
}

void create_succ(T_Node* root, int nr_gen)
{
    if(root->generatie == nr_gen)
        return;
    root->left = (T_Node*)malloc(sizeof(T_Node));
    root->right = (T_Node*)malloc(sizeof(T_Node));
    root->stack = NULL;
    root->left->left = NULL;
    root->left->right = NULL;
    root->right->left = NULL;
    root->right->right = NULL;
    root->left->generatie = root->right->generatie = root->generatie+1;
    create_succ(root->left, nr_gen);
    create_succ(root->right, nr_gen);
}
void preord_rez_gen(T_Node *root, int lin, int col, char *grila)
{
    if(root->left)
    {
        char *grila1 = NULL;
        char *grila2 = NULL;
        
        grila1 = rule2(grila, lin, col, &root->left->stack);
        grila2 = rule1(grila, lin, col, &root->right->stack);
        
       
        if (root->generatie>0) 
        {
            free(grila);
        }
        
       
        preord_rez_gen(root->left, lin, col, grila1);
        preord_rez_gen(root->right, lin, col, grila2);
    }
    else if (root->generatie > 0) 
            free(grila);
            
}
void deleteTree(T_Node** root)
{
    if(*root != NULL)
    {
        deleteTree(&(*root)->left);
        deleteTree(&(*root)->right);
        deleteStack(&(*root)->stack);
        free(*root);
        *root = NULL;
    }
}

void changeNprint(FILE *f,char *grila, int lin, int col, T_Node *root)
{
    if(root ==NULL) return;
    //invertStack(&root->stack);
    while(!isEmpty(root->stack))
    {
        Poz v = pop(&root->stack);
        if(*(grila+ v.linie *col + v.coloana) == 'X')
            *(grila+ v.linie *col + v.coloana) = '+';
        else *(grila+ v.linie *col + v.coloana) = 'X';
    }
    scriere_f_out(f, grila, lin, col);
    char *grila1 = NULL;
    char *grila2 = NULL;
    copy_matr(grila, &grila1, lin, col);
    copy_matr(grila, &grila2, lin, col);
    changeNprint(f, grila1, lin, col, root->left);
    changeNprint(f, grila2, lin, col, root->right);
    free(grila1);
    free(grila2);

}



int isEmpty_conex(const Node_Conex *top)
{
    return(top == NULL);
}

void push_conex(Node_Conex** top, Node *v)
{
    Node_Conex* newNode = (Node_Conex*)malloc(sizeof(Node_Conex));
    newNode->top = v;
    newNode->next = *top;
    *top = newNode;

}

Node* pop_conex(Node_Conex **top)
{
    if (isEmpty_conex(*top)) 
        return NULL;
    Node_Conex *temp = (*top);
    Node* aux = temp->top;
    *top = (*top)->next;
    deleteStack(&temp->top);
    free(temp);
    return aux;
}


void deleteStack_conex(Node_Conex** top)
{
    while ((*top) != NULL) {  
        Node_Conex* temp;
        temp = *top;
        *top = (*top)->next;
        deleteStack(&temp->top);
        free(temp);
    }
}


void fprintStack_conex(Node_Conex* top, FILE* f_out)
{

}


void printStack_conex(Node_Conex* top)
{

}


void invertStack_conex(Node_Conex**top)
{


}








int inViata(char *grila, int lin, int col, Poz **elemente_graph)
{
    int vii = 0;
    (*elemente_graph) = NULL;
    for(int i = 0; i< lin; i++)
    {
        for(int j = 0; j< col; j++)
        {
            if(*(grila + i*col + j) == 'X')
            {
                vii++;
                Poz v;
                v.linie = i;
                v.coloana = j;
                (*elemente_graph) = (Poz*)realloc((*elemente_graph), vii*sizeof(Poz));
                (*((*elemente_graph) + vii - 1)) = v;
            }
        }
    }
    return vii;
}

int vecini(Poz a, Poz b)
{
    if(a.linie-1 == b.linie)
    {
        if((a.coloana -1 == b.coloana)||(a.coloana == b.coloana)||(a.coloana+1 == b.coloana))
        return 1;

    }
    else if(a.linie == b.linie)
    {
        if((a.coloana -1 == b.coloana)||(a.coloana == b.coloana)||(a.coloana+1 == b.coloana))
        return 1;

    }
    else if(a.linie +1 == b.linie)
    {
        if((a.coloana -1 == b.coloana)||(a.coloana == b.coloana)||(a.coloana+1 == b.coloana))
        return 1;

    }
    return 0;
}

void createGfromVector(Poz *elemente_graph, int vii, GRAPH *g)
{
    g->V = vii;
    g->E = 0;
    g->adi = (int *)calloc(vii*vii, sizeof(int));
    for(int i=0; i<vii; i++)
    {
        for(int j=0; i<vii; j++)
        {
            *(g->adi + i*vii + j) = vecini(elemente_graph[i], elemente_graph[j]);
            if(vecini(elemente_graph[i], elemente_graph[j]))
            {
                g->E++;
            }
        }
    }
    g->E=g->E/2;
}





void DFS_scan(GRAPH *g, int visited[], int i, Node **top) {
    int j;
    visited[i] = 1;
    Poz v;
    v.coloana = i;
    push(top, v);
    printf("Nodul %d -> ", i);
    for (j = 0; j < g->V; j++) 
        if (*(g->adi + i*g->V + j) == 1 && visited[j] == 0)
            DFS_scan(g, visited, j, top);
}

int DFS(GRAPH *g, Node_Conex **top_conex) {
    int i, comp_conexe = 0;
    int *visited = (int*)calloc(g->V, sizeof(int));
    for (i = 0; i < g->V; i++) 
        if (visited[i] == 0) {
            Node *aux;
            aux=NULL;
            DFS_scan(g, visited, i, &aux);
            comp_conexe++;
            invertStack(&aux);
            push_conex(top_conex, aux);
            printf("\n");
        }
    
    return comp_conexe;
}


int convertStack2Vector(Node **top, int *v)
{
    int n=0;
    while(!isEmpty(*top))
    {
        n++;
        v = (int*)realloc(v, n*sizeof(int));
        v[n-1] = pop(top).coloana;
    }
    return n;
}

/*

int lant_Hamiltonian(int *adi, int varfuri, int nr_noduri, int *v, int **path, FILE *f_out)
{
    int *dp;
    dp = (int*)calloc(nr_noduri * (1 << nr_noduri), sizeof(int));
    (*path) = (Node*)calloc(nr_noduri*(1<<nr_noduri), sizeof(int));
    
    for(int i = 0; i<nr_noduri; i++)
    {
        *(dp + i*(1<<nr_noduri) + (1<<i)) = 1;
        *((*path)+i*(1<<nr_noduri)+i) = -1;
    }

    for(int i=0; i< ( 1<<nr_noduri ) ; i++)
    {
        for(int j=0; j<nr_noduri; j++)
        {
            if(i & (1<<j))
            {
                for(int k=0; k< nr_noduri; k++)
                {
                    if(i & (1<<k) && *(adi + v[k]*varfuri + v[j]) && j!=k && *(dp + k*(1<<nr_noduri) + (i ^ (1<<j))))
                    {              
                        *(dp + j*(1<<nr_noduri) + i) = 1;
                        
                    }
                }
            }
        }
    }

    for(int i = 0; i<nr_noduri; i++)
    {
        if(*(dp + i*(1<<nr_noduri) + (1<<nr_noduri) -1 ))
        {
            fprintStack(*top[i], f_out);
            return 1;
        }
    }
    return 0;
}

*/

int bk(int current, int *nr_vizitati, int *visited, GRAPH *g, int *de_vizitat, int nr_de_vizitat, int **path)
{

    if(*nr_vizitati == nr_de_vizitat)
    {
        return 1;
    }
    *nr_vizitati++;
    *path = realloc(*path, *nr_vizitati);
    *((*path)+(*nr_vizitati)-1) = current;
    for(int urm=0; urm<nr_de_vizitat; urm++)
    {
        int urm_fr = de_vizitat[urm];
        if(*(g->adi + current*g->V + urm_fr)&& !visited[urm_fr])
        {
            visited[urm_fr] = 1;
            if(bk(urm_fr, nr_vizitati, visited, g, de_vizitat, nr_de_vizitat, path))
            {
                return 1;
            }
            visited[urm_fr] = 0;
        }
    }
    return 0;
}

int hamilton(GRAPH *g, int *de_vizitat, int nr_de_vizitat, int **path)
{
    int *visited, nt_visited;
    visited = (int*)calloc(nr_de_vizitat, sizeof(int));
    *path = NULL;
    for(int i=0; i<nr_de_vizitat; i++)
    {
        int start = de_vizitat[i];
        for(int j=0; j<nr_de_vizitat; j++)
        {
            visited[j] = 0;
        }
        visited[start] =1;
        nt_visited = 1;
        if(bk(start, &nt_visited, visited, g, de_vizitat, nr_de_vizitat, path))
        {
            return 1;
        }
        
    }
    return -1;
}

void preord_rez_gen1(T_Node *root, int lin, int col, char *grila)
{
    if(root->left)
    {
        char *grila1 = NULL;
        char *grila2 = NULL;
        
        grila1 = rule2(grila, lin, col, &root->left->stack);
        grila2 = rule1(grila, lin, col, &root->right->stack);
        
       
        if (root->generatie>0) 
        {
            free(grila);
        }
        
       
        preord_rez_gen(root->left, lin, col, grila1);
        preord_rez_gen(root->right, lin, col, grila2);
    }
    else if (root->generatie > 0) 
            free(grila);
            
}
