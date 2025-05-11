#include "lib_gameoflife.h"

int main(int argc, const char *argv[])
{
    int nr_coloane, nr_linii, nr_task, nr_generatii;
    FILE *f_in, *f_out;
    char *grila;
    Node *top = NULL;


    T_Node *root;
    root = (T_Node*)malloc(sizeof(T_Node));
    root->generatie=0;
    root->stack = NULL;

    root->left=root->right=NULL;
    f_in = fopen(argv[1], "r");
    f_out = fopen(argv[2], "w");
    citire_f_in( f_in, &nr_task, &nr_coloane, &nr_linii, &nr_generatii, &grila );
    //root->grila = grila;
    if(nr_task==1)
        scriere_f_out(f_out, grila, nr_linii, nr_coloane); 
    if(nr_task!=TASK3)
    {
        for(int contor_generatie = 1; contor_generatie <= nr_generatii ; contor_generatie++ )
        {
            deleteStack(&top);
            rez_generatie(grila, nr_linii, nr_coloane, &top);
            
            switch (nr_task)
            {
            case TASK1:
                scriere_f_out(f_out, grila, nr_linii, nr_coloane);
                break;
            case TASK2:
                invertStack(&top);
                fprintf(f_out, "%d ", contor_generatie);
                fprintStack(top, f_out);
                fprintf(f_out, "\n");
                break;
            case TASK4:

                break;
            default:
                break;
            }
     
         }
    }
    if(nr_task==TASK3)
    {
        char *grila1 = NULL;
        copy_matr(grila, &grila1, nr_linii, nr_coloane);
        create_succ(root, nr_generatii);
        preord_rez_gen(root, nr_linii, nr_coloane, grila);
        //preord_afis(root, f_out, nr_linii, nr_coloane);
        changeNprint(f_out, grila1, nr_linii, nr_coloane, root);
        free(grila1);
    }
    fclose(f_in);
    fclose(f_out);
    free(grila);
    deleteStack(&top);
    deleteTree(&root);
    //free(top);

    return 0;
}