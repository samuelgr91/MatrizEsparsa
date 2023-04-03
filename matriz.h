# ifndef matriz_h
# define matriz_h

typedef struct matriz Matriz;

Matriz *CriaMatriz(int n,int m);

int MatrizInsereNoFinal(Matriz *matriz,int n,int m, int valor);

void MatrizLe(Matriz *, int);

void MatrizImprimeResposta(Matriz *);

void MatrizDestroi(Matriz **);

Matriz *MatrizSoma(Matriz *,Matriz *);

int MatrizBuscar(Matriz *, int, int);

Matriz *MatrizMultiplica(Matriz *,Matriz *);

Matriz *MatrizTransposta(Matriz *);

# endif // matriz_h