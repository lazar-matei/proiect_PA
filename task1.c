#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct vecin{
    int morti;
    int vii;
};
typedef struct vecin VECIN;



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
            if((i>=0)&&(j>=0)&&(i<lin)&&(j<col))

                if( *( matr + i * col + j ) == 'X' )
                    nr.vii++;
                else if( *( matr + i * col + j ) == '+' )
                    nr.morti++; 


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



void rez_generatie(char *matr, int lin, int col)
{
    int i, j;
    VECIN nr_vecini;
    char *matr_ctrl;
    matr_ctrl = NULL;
    copy_matr(matr, &matr_ctrl, lin, col);
    for(i=0; i<lin; i++)
        for(j=0; j<col; j++)
        {
            nr_vecini = stare_vecini( matr_ctrl, j, i, col, lin);
            if( *( matr + i * col + j ) == 'X' )
                {
                    if ( (nr_vecini.vii < 2) || ( nr_vecini.vii > 3 ) )
                        *( matr + i * col + j ) = '+';
                    else if( (nr_vecini.vii == 2) || ( nr_vecini.vii == 3 ) ) 
                        *( matr + i * col + j ) = 'X';
                }
            else if( (*( matr + i * col + j ) == '+') && (nr_vecini.vii == 3) )
                *( matr + i * col + j ) = 'X';
        }
        free(matr_ctrl);
}

int main(int argc, const char *argv[])
{
    int nr_coloane, nr_linii, nr_task, nr_generatii, contor_generatie;
    FILE *f_in, *f_out;
    char *grila;
    

    f_in = fopen(argv[1], "r");
    f_out = fopen(argv[2], "w");
    citire_f_in( f_in, &nr_task, &nr_coloane, &nr_linii, &nr_generatii, &grila );
    scriere_f_out(f_out, grila, nr_linii, nr_coloane);

    for( contor_generatie = 0; contor_generatie < nr_generatii ; contor_generatie++ )
    {
        rez_generatie(grila, nr_linii, nr_coloane);
        scriere_f_out(f_out, grila, nr_linii, nr_coloane);
    }

    fclose(f_in);
    fclose(f_out);
    free(grila);

    return 0;
}