#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int n, m, t;
    int qtd=3; 
    char op[2];
    scanf("%d ", &qtd);
    fgets(op,2,stdin);
    if(op[0] == 'S'){
        Matriz *A,*B,*C;
        scanf("%d%d%d",&n,&m,&t);
        A=CriaMatriz(n,m);
        MatrizLe(A,t);
        scanf("%d%d%d",&n,&m,&t);
        B=CriaMatriz(n,m);
        MatrizLe(B,t);
        C=MatrizSoma(A,B);
        for(int i=0; i < qtd-2 ;i++){
            scanf("%d%d%d",&n,&m,&t);
            A=CriaMatriz(n,m);
            MatrizLe(A,t);
            C=MatrizSoma(A,C);
        }
        MatrizImprimeResposta(C); 
        MatrizDestroi(&A);
        MatrizDestroi(&B);
        MatrizDestroi(&C);
    }
    else if(op[0] == 'T'){
        for(int i=0; i < qtd ;i++){
            Matriz *A,*B;
            scanf("%d%d%d",&n,&m,&t);
            A=CriaMatriz(n,m);
            MatrizLe(A,t);
            B=MatrizTransposta(A);
            MatrizImprimeResposta(B); 
            MatrizDestroi(&A);
            MatrizDestroi(&B);
        }
    }
    else if(op[0] == 'M'){
        Matriz *A,*B;
        scanf("%d%d%d",&n,&m,&t);
        A=CriaMatriz(n,m);
        MatrizLe(A,t);
        scanf("%d%d%d",&n,&m,&t);
        B=CriaMatriz(n,m);
        MatrizLe(B,t);
        A=MatrizMultiplica(A,B);
        for(int i=0; i < qtd-2 ;i++){
            scanf("%d%d%d",&n,&m,&t);
            B=CriaMatriz(n,m);
            MatrizLe(B,t);
            A=MatrizMultiplica(A,B);
        }
        MatrizImprimeResposta(A); 
        MatrizDestroi(&A);
        MatrizDestroi(&B);
    }

    
    return 0; 
}
