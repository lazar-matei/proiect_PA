#include "lib_gameoflife.h"

int main(int argc, const char *argv[])
{
    int nr_coloane, nr_linii, nr_task, nr_generatii, contor_generatie;
    FILE *f_in, *f_out;
    char *grila;
    Node *top = NULL;


    f_in = fopen(argv[1], "r");
    f_out = fopen(argv[2], "w");
    citire_f_in( f_in, &nr_task, &nr_coloane, &nr_linii, &nr_generatii, &grila );
    if(nr_task==1)
        scriere_f_out(f_out, grila, nr_linii, nr_coloane); 

    for( contor_generatie = 1; contor_generatie <= nr_generatii ; contor_generatie++ )
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
        case TASK3:

            break;
        case TASK4:

            break;
        default:
            break;
        }
            
        
        
    }

    fclose(f_in);
    fclose(f_out);
    free(grila);
    deleteStack(&top);
    //free(top);

    return 0;
}