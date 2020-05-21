#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//Pour le tableau de 8 aléatoires différences valeurs
#define l 9

long int u;
int a = 1, b = 9, k = 1;
int d;
int arr[l];

//Pour la matrice (l'état initial, l'état de déplacement, l'état final)
#define r 3
#define c 3

char matrix[r][c];
char new[r][c];
char final[r][c];
int count;
int i, j;
char z ;
int p, q, x, y;
int t = 0;
int result = 0;

//-----------------------------------------------------------------------------------
void createArr(int arr[]) {
    d = round(a + (b - a) * ((float) rand ()) / RAND_MAX);
    if (k < 8) {
        for (int i = 0; i < k; i++) {
            if (d == arr[i]) {
                return createArr(arr);
            }
        }
        arr[k] = d;
        k++;
        createArr(arr);
    }
}

void sortArr(int arr[]) {
    int h, k;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8 - i; j++) {
            h = arr[j];
            k = arr[j + 1];
            if (arr[j] < arr[j + 1]) {
                arr[j] = k;
                arr[j + 1] = h;
            }
        }
    }
}

//-----------------------------------------------------------------------------------
void load() {
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            if(new[i][j] == '0') {
                matrix[i][j]= ' ';
                continue;
            }
            matrix[i][j] = new[i][j];
        }
    }
}

void initial(char new[r][c], int arr[l]) {
    int x = 0;
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            if (i == 2 && j == 2) {
                new[2][2] = ' ';
                break;
            }
            
            // changer le type des données (entiers -> charactères)
            new[i][j] = '0' + arr[x];
            x++;
        }
    }
}

void move(char matrix[r][c], char final[r][c], int callBack()) {
    while(1) {
        printf("Entrez une valeur pour changer sa position en espace vide\n");
        scanf(" %c",&z);
        
        if(z == 'q') {
            // printf("\n********Quittez********\n");
            // break;
            printf("\n********Quitter ou redémarrer? (q|r) ********\n");
            scanf(" %c",&z);
            if (z == 'q') break;
            else if(z == 'r') callBack();
        }
        
        for(i = 0; i < r; i++) {
            for(j = 0; j < c; j++) {
                if((matrix[i][j]) == z) {
                    p = i;
                    q = j;
                } else if((matrix[i][j]) == ' ') {
                    x = i;
                    y = j;
                }
            }
        }
        
        t = 0;
        int m , n ;
        m = p - 1;
        n = q ;
        
        if(m >= 0) {
            if((matrix[m][n]) == ' ') t = 1;
        }
        
        m = p + 1;
        
        if(m <= 2) {
            if((matrix[m][n]) == ' ') t = 1;
        }
        
        m = p;
        n = q - 1 ;
        
        if(n >= 0) {
            if((matrix[m][n]) == ' ') t = 1;
        }
        
        n = q + 1 ;
        
        if(n <= 2) {
            if((matrix[m][n]) == ' ') t = 1;
        }
        
        if(t == 1) {
            matrix[x][y] = z;
            matrix[p][q] = ' ';
        }
        
        t = 0;
        
        for(i = 0; i<r; i++) {
            for(j = 0; j < c; j++) {
                if((matrix[i][j]) == final[i][j]) {
                    t++;
                }
            }
        }
        
        system("clear");
        
        for(i = 0; i < r; i++) {
            for(j = 0; j < c; j++) {
                printf("|%c|",matrix[i][j]);
            }
            printf("\n");
        }
        
        if(t == 9) {
            printf("\n****Vous gagnez****\n");
            break;
        }
    }
}

//-----------------------------------------------------------------------------------
int main() {
    time(&u);
    srand(u);
    
    d = round(a + (b - a) *((float) rand ()) / RAND_MAX);
    arr[0] = d;
    createArr(arr);
    
    
main:
    count = 0;
    
    //Établir l'état initial de la matrice
    initial(new, arr);
    printf("\n");
    
    load();
    printf("Démarrer le programme: \n");
    
    
    for(i = 0; i < r; i++) {
        if (i == 2 && j == 2) {
            printf("|%c| \n", matrix[i][j]);
            break;
        }
        for(j = 0; j < c; j++) {
            printf("|%c|", matrix[i][j]);
        }
        printf("\n");
    }
    
    //Changer l'ordre de ce tableau pour établir l'état final de la matrice
    sortArr(arr);
    
    //Établir l'état final
    char final[r][c] = {
        {'0' + arr[7], '0' + arr[6], '0' + arr[5]}, 
        {'0' + arr[4], '0' + arr[3], '0' + arr[2]}, 
        {'0' + arr[1], '0' + arr[0], ' '}
    };
    
    //Déplacement et mise à jour l'état de la matrice
    move(matrix, final, main);
    
    return 1;
}
