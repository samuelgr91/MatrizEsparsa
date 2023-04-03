#include "matriz.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    int linha;
    int coluna;
    int valor;
}Item;

typedef struct cell {
    Item item;
    struct cell *prox;
    struct cell *embaixo;
} Celula;

typedef struct matriz{
    Celula *calda;
    Celula *cabeca;
    int n,m;
}Matriz;



Matriz *CriaMatriz(int n,int m) {
    Matriz* matriz = malloc(sizeof(Matriz));
    matriz->n=n;
    matriz->m=m;

    matriz->cabeca =malloc(sizeof(Celula));
    matriz->calda=matriz->cabeca;
    matriz->cabeca->prox=matriz->cabeca;
    matriz->cabeca->embaixo=matriz->cabeca;
    
    for(int i = 0;i <= m; i++){
        matriz->calda->prox =malloc(sizeof(Celula));
        matriz->calda->item.coluna=-1;
        matriz->calda = matriz->calda->prox;
        matriz->calda->prox=matriz->cabeca; 
        matriz->calda->embaixo=matriz->calda;
        
    }
    matriz->calda=matriz->cabeca;

    for(int i=0;i <= n;i++){
        matriz->calda->embaixo =malloc(sizeof(Celula));
        matriz->calda->item.linha=-1;
        matriz->calda = matriz->calda->embaixo;
        matriz->calda->embaixo=matriz->cabeca; 
        matriz->calda->prox=matriz->calda;
    }
    return matriz;
}




int MatrizInsereNoFinal(Matriz *matriz,int n,int m, int valor) {

    Celula * newCell = (Celula*) malloc(sizeof(Celula));
    if (newCell == NULL) {
        return 0;
    }
    newCell->item.valor = valor;
    newCell->item.linha = n;
    newCell->item.coluna = m;
    
    Celula * auxlinha = matriz->cabeca->embaixo;
    Celula * auxcoluna = matriz->cabeca->prox;
    
    int i;
    for(i = 0;i < n-1 ;i++){
        auxlinha=auxlinha->embaixo;
    } 
    i=0;
    while(auxlinha->prox->item.linha != -1 && i < m){
        auxlinha = auxlinha->prox;
        i++;
    }
    newCell->prox = auxlinha->prox;
    auxlinha->prox = newCell;
    

    for(i = 0;i < m-1 ;i++){
        auxcoluna=auxcoluna->prox;
    } 
    i=0;
    while(auxcoluna->embaixo->item.coluna != -1 && i < n){
        auxcoluna = auxcoluna->embaixo;
        i++;
    }
    newCell->embaixo = auxcoluna->embaixo;
    auxcoluna->embaixo = newCell;
    return 1;
}

void MatrizLe(Matriz *matriz, int n) {
    Item item;
    for (int i=0;i<n;i++) {
        scanf("%d %d %d", &item.linha, &item.coluna, &item.valor);
        if(item.valor != 0)
            MatrizInsereNoFinal(matriz,item.linha,item.coluna, item.valor);
    }
}


Matriz *MatrizSoma(Matriz *A,Matriz *B) {
    //if(A->m != B->m || A->n != B->n)
    //    return -1;
    Celula *aux1,*aux2;
    aux1 = A->cabeca->embaixo;
    aux2 = B->cabeca->embaixo;
    Matriz *C=malloc(sizeof(Matriz));
    C=CriaMatriz(A->n,A->m);
    for (int i = 1; i <= A->n; i++){
        for (int j = 1; j <= A->m; j++){
            if (aux1->prox->item.coluna == j && aux2->prox->item.linha == i && aux2->prox->item.linha == i && aux2->prox->item.coluna == j){
                MatrizInsereNoFinal(C,aux1->prox->item.linha,aux1->prox->item.coluna,(aux1->prox->item.valor+aux2->prox->item.valor));
                aux1=aux1->prox;
                aux2=aux2->prox;
            }
            else if(aux1->prox->item.coluna == j  && aux1->prox->item.linha == i ){
                MatrizInsereNoFinal(C,aux1->prox->item.linha,aux1->prox->item.coluna,aux1->prox->item.valor);
                aux1=aux1->prox;   
            }
            else if(aux2->prox->item.coluna == j  && aux2->prox->item.linha == i){
                MatrizInsereNoFinal(C,aux2->prox->item.linha,aux2->prox->item.coluna,aux2->prox->item.valor);
                aux2=aux2->prox;   
            }
        }
        
        aux1=aux1->prox->embaixo;
        aux2=aux2->prox->embaixo;

        
    }
    return C;
}


Matriz *MatrizTransposta(Matriz *A) {
    //if(A->m != B->m || A->n != B->n)
    //    return -1;
    Celula *aux1;
    aux1 = A->cabeca->prox;
    Matriz *C=malloc(sizeof(Matriz));
    C=CriaMatriz(A->m,A->n);
    for (int i = 1; i <= A->m; i++){
        for (int j = 1; j <= A->n; j++){
            if (aux1->embaixo->item.coluna == i && aux1->embaixo->item.linha == j){
                MatrizInsereNoFinal(C,aux1->embaixo->item.coluna,aux1->embaixo->item.linha,aux1->embaixo->item.valor);
                aux1=aux1->embaixo;
            }
        }
        aux1=aux1->embaixo->prox;
    }
    return C;
}

Matriz *MatrizMultiplica(Matriz *A,Matriz *B) {
    Matriz *C=CriaMatriz(A->n,B->m);
    for (int i = 1; i <= A->n; i++){
        for (int j = 1; j <= B->m; j++){
            int soma=0;
            for (int k = 1; k <= A->m; k++)
                soma+=MatrizBuscar(A,i,k)*MatrizBuscar(B,k,j);
            if(soma != 0)
                MatrizInsereNoFinal(C,i,j,soma);
        }
    }
    return C;
}


int MatrizBuscar(Matriz *matriz,int n,int m) {
    Celula * auxlinha = matriz->cabeca->embaixo;
    int valor=0;
    int i;
    for(i = 0;i < n-1 ;i++){
        auxlinha=auxlinha->embaixo;
    } 
    i=0;
    while(auxlinha->prox->item.linha != -1 && i < m){
        if(auxlinha->prox->item.coluna == m)
            valor=auxlinha->prox->item.valor;
        auxlinha = auxlinha->prox;
        i++;
    }
    return valor;
}


void MatrizImprimeResposta(Matriz *matriz) {
    Celula *pCelula;
    pCelula = matriz->cabeca->embaixo;

    

    for (int i = 1; i <= matriz->n; i++){
        for (int j = 1; j <= matriz->m; j++){
            if (pCelula->prox->item.linha == i && pCelula->prox->item.coluna == j){
                pCelula = pCelula->prox;
                printf("%d ", pCelula->item.valor);
            }
            else{
                printf("%d ", 0);
            }
        }
        printf("\n");
        pCelula = pCelula->prox->embaixo;
    }

}

void MatrizDestroi(Matriz **matriz) {
    Celula *pCelula;
    pCelula = (*matriz)->cabeca->embaixo->prox;
    Celula *aux;
    aux = (*matriz)->cabeca->embaixo->prox->prox;

    

    for (int i = 1; i <= (*matriz)->n; i++){
        for (int j = 1; j <= (*matriz)->m; j++){
            if (pCelula->item.linha == i && pCelula->item.coluna == j){
                free(pCelula);
                pCelula=aux;
                aux=aux->prox;
            }
        }
        pCelula = pCelula->prox->embaixo->prox;
        aux = pCelula->prox->embaixo->prox->prox;
    }

    pCelula = (*matriz)->cabeca->embaixo;
    aux = (*matriz)->cabeca->embaixo->embaixo;
    for (int i = 1; i <= (*matriz)->n; i++){
        free(pCelula);
        pCelula=aux;
        aux=aux->embaixo;
    }

    pCelula = (*matriz)->cabeca->prox;
    aux = (*matriz)->cabeca->prox->prox;
    for (int i = 1; i <= (*matriz)->m; i++){
        free(pCelula);
        pCelula=aux;
        aux=aux->prox;
    }
    free((*matriz)->cabeca);
}
