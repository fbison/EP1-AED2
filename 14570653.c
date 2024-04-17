/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2024                          **/
/**   Turma 04 - Prof. Luciano Digiampietri                         **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   Filipe Bison de Souza                   14570653              **/
/**                                                                 **/
/*********************************************************************/

// gcc completeERenomeie.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define true 1
#define false 0

typedef int bool;

/* Estrutura para representar nosso grafo usando matriz binaria de adjacencias */
typedef struct {
  int numVertices;
  int numArestas;
  bool** matriz;
} Grafo;


/* Funcao auxiliar para o sistema de correcao automatica (nao mexer) */
void printf123(){
    // Funcao usada pelo sistema de correcao automatica (nao mexer)
}


/* Funcao que inicializa o grafo cujo endereco foi passado como parametro.
   Isto e, cria a matriz de adjacencias (preenchida com false),
   e atribui valor para numVertices (recebendo o valor passado por parametro)
   e numArestas igual a zero.
*/
bool inicializaGrafo(Grafo* g, int vertices){
  if (g==NULL || vertices<1) return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->matriz = (bool**) malloc(sizeof(bool*)*vertices);
  for (x=0; x<vertices; x++){
    g->matriz[x] = (bool*) malloc(sizeof(bool)*vertices);
    for (y=0; y<vertices; y++){
      g->matriz[x][y] = false;
    }
  }
  return true;
}


/* Funcao que libera a memoria da matriz de adjacencia do grafo cujo endereco
   foi passado como parametro.
*/
bool liberaGrafo(Grafo* g){
  if (g==NULL) return false;
  int x;
  for (x=0; x<g->numVertices; x++)
    free(g->matriz[x]);
  free(g->matriz);
  g->numVertices = 0;
  g->numArestas = 0;
  g->matriz = NULL;
  return true;
}

/* Funcao que retorna o numero de vertices do grafo apontado por g, caso o 
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeVertices(Grafo* g){
  if (g != NULL) return g->numVertices;
  else return -1;
}


/* Funcao que retorna o numero de arestas do grafo apontado por g, caso o 
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeArestas(Grafo* g){
  if (g != NULL) return g->numArestas;
  else return -1;
}


/* Funcao que retorna o grau do vertice v, caso ele exista.
   Caso contrario, retorna -1.
*/
int retornaGrauDoVertice(Grafo* g, int v){
  if (!g || v < 0 || v >= g->numVertices) return -1;
  int x, grau = 0;
  for (x=0;x<g->numVertices;x++){
    if (g->matriz[v][x]) grau++;
  }
  return grau;
}


/* Funcao que retorna true se o vertice v possui um ou mais
   vertices adjacentes (vizinhos).
*/
bool possuiVizinhos(Grafo* g, int v){
  if (!g || v < 0 || v >= g->numVertices) return false;
  int x;
  for (x=0;x<g->numVertices;x++)
    if (g->matriz[v][x]) return true;
  return false;
}


/* Funcao que insere uma nova aresta no grafo.
   Se os vertices passados como parametro forem validos, ha duas possibilidades:
   - a aresta nao existia;
   - a aresta existia. 
*/
bool insereAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || v1 == v2) return false;
  if (g->matriz[v1][v2] == false){
      g->matriz[v1][v2] = true;
      g->matriz[v2][v1] = true;
      g->numArestas++;
  }
  return true;
}


/* Funcao que exclui a aresta entre v1 e v2 (caso exista uma aresta valida
   entre v1 e v2) e retorna true; ou retorna false, caso contrario.
*/
bool removeAresta(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  g->matriz[v1][v2] = false;
  g->matriz[v2][v1] = false;
  g->numArestas--;
  return true;
}


/* Funcao que retorna true se existe uma aresta valida entre v1 e v2 
   e false caso contrario.
*/
bool arestaExiste(Grafo* g, int v1, int v2){
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  return true;
}


/* Funcao que cria um grafo com o numero de vertices e
   numero de arestas passados como parametro e retorna seu endereco.
*/
Grafo* criaGrafoAleatorio(int numVertices, int numArestas){
  printf("################# Criando grafo com %i vertice(s) e com %i aresta(s). #################\n",numVertices, numArestas);
  int x, y, a = 0;
  if (numVertices < 1 || numArestas >= numVertices*(numVertices-1)/2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;  
  }
  Grafo* g = (Grafo*)malloc(sizeof(Grafo));
  inicializaGrafo(g,numVertices);
  while(a<numArestas){
    x = rand()%numVertices;
    y = rand()%numVertices;
    if (x!=y && g->matriz[x][y] == false){
      g->matriz[x][y] = true;
      g->matriz[y][x] = true;
      a++;
    }
  }
  g->numArestas = numArestas;
  return g;
}


/* Funcao desenvolvida para exibir um grafo, no formato de uma matriz
   de adjacencia.
*/
void exibeGrafo(Grafo* g){
  if(!g) return;
  int x, y;
  printf("\nImprimindo grafo (vertices: %i; arestas: %i).\n   ", g->numVertices, g->numArestas);
  for (x=0;x<g->numVertices;x++) printf(" %3i",x);
  printf("\n");
  for (x=0;x<g->numVertices;x++){
    printf("%3i",x);
    for (y=0;y<g->numVertices;y++)
      printf(" %3i",g->matriz[x][y]);  
    printf("\n");
  }
  printf("\n");
}


/* Funcao que exibe os valores de um arranjo de numeros reais */
void exibeArranjoReais(float* arranjo, int n){
  int x;
  for (x=0; x<n; x++) printf("  v%i\t", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%3.2f\t",arranjo[x]);
  }
  printf("\n\n");
}


/* Funcao que exibe os valores de um arranjo de numeros inteiros */
void exibeArranjoInteiros(int* arranjo, int n){
  int x;
  for (x=0; x<n; x++) printf(" v%i\t", x);
  printf("\n");
  for (x=0; x<n; x++){
    printf("%3i\t",arranjo[x]);
  }
  printf("\n\n");
}


/*Adiciona ao array vizinhos quantos vizinhos em comum
 o índice i tem com o indice v*/
void vizinhosEmComum(Grafo* g, int v, int* vizinhos){
  for (int x=0; x< g->numVertices; x++){
    vizinhos[x]=0;
    for(int possivelVizinho=0; possivelVizinho< g->numVertices;possivelVizinho++){
      if (g->matriz[v][possivelVizinho] &&
          g->matriz[x][possivelVizinho]) {
            vizinhos[x]++;
          }
    }
  }
}


/* Coeficiente de Jaccard 
Calcula a intercessão e a união de vizinhos de v para cada outro vértice
Realiza os cálculos do coeficiente no final
*/
void coeficienteDeJaccard(Grafo* g, int v, float* coeficientes){
  for (int x=0; x< g->numVertices; x++){
    int intercessaoDeVizinhos= 0;
    int uniaoDeVizinhos =0;
    for(int possivelVizinho=0; possivelVizinho< g->numVertices;possivelVizinho++){
      bool eVizinhoDeX=g->matriz[x][possivelVizinho];
      bool eVizinhoDeV=g->matriz[v][possivelVizinho];
      if(eVizinhoDeX && eVizinhoDeV) intercessaoDeVizinhos++;
      if(eVizinhoDeX || eVizinhoDeV) uniaoDeVizinhos++;
    }
    if(uniaoDeVizinhos==0){
      coeficientes[x]=-1;
      continue;
    }
    coeficientes[x]= intercessaoDeVizinhos/(float)uniaoDeVizinhos;
  }
}

int quantidadeDeVizinhos(Grafo* g, int v){
  int vizinhos=0;
  for(int possivelVizinho=0; possivelVizinho< g->numVertices;possivelVizinho++){
    if (g->matriz[v][possivelVizinho]) {
      vizinhos++;    
    }
  }
  return vizinhos;
}
/* Medida Adamic Adar 
Encontra os vizinhos em comum de v com outros vértices
Para cada vértice analisa quantos vizinhos ele tem, e adiciona log(valor)^-1
Para otimização esse cálculo só é realizado para o vértice x uma vez, mesmo que ele apareça como comum para outros vértices
Ao invés de zerar o array que guarda esses valores, por calloc, ou num array separado. 
  Ele são setados dentro do for, para diminuir o número de iterações.
*/
void AdamicAdar(Grafo* g, int v, float* coeficientes){
  float* valores= (float*) malloc(sizeof(float)* g->numVertices); 
  for (int x=0; x< g->numVertices; x++){
    float somatorio=0;
    for(int possivelVizinho=0; possivelVizinho< g->numVertices;possivelVizinho++){
      
      if(x==0){
        valores[possivelVizinho]= -1;
      }

      if (g->matriz[v][possivelVizinho] &&
          g->matriz[x][possivelVizinho]) {
            if(valores[possivelVizinho]== -1){
              float quant=(float)quantidadeDeVizinhos(g, possivelVizinho); 
              float denominador= log(quant);
              if(denominador==0){
                somatorio=-1;
                break;
              }else{
                valores[possivelVizinho]= 1/denominador;
              }
            }
            somatorio= somatorio+ valores[possivelVizinho];
      }

    }
    coeficientes[x]= somatorio;
  }
}


/* Alocacao de Recursos 
Encontra os vizinhos em comum de v com outros vértices
Para cada vértice analisa quantos vizinhos ele tem, e adiciona (valor)^-1
Para otimização esse cálculo só é realizado para o vértice x uma vez, mesmo que ele apareça como comum para outros vértices
Ao invés de zerar o array que guarda esses valores, por calloc, ou num array separado. 
  Ele são setados dentro do for, para diminuir o número de iterações.
*/
void alocacaoDeRecursos(Grafo* g, int v, float* coeficientes){
  float* valor= (float*) malloc(sizeof(float)* g->numVertices); 
  for (int x=0; x< g->numVertices; x++){
    float somatorio=0;
    for(int possivelVizinho=0; possivelVizinho< g->numVertices;possivelVizinho++){
      
      if(x==0)valor[possivelVizinho]= -1;
      
      if (g->matriz[v][possivelVizinho] &&
          g->matriz[x][possivelVizinho]) {
            if(valor[possivelVizinho]== -1){
              float quant=(float)quantidadeDeVizinhos(g, possivelVizinho);   
              valor[possivelVizinho]= 1/(quant);
            }
            somatorio= somatorio+ valor[possivelVizinho];  
      }

    }
    coeficientes[x]= somatorio;
  }
}


/* Similaridade Cosseno 
Calcula a intercessão de vizinhos de v para cada outro vértice, através de cálculos booleanos
Soma a quantidade de vizinhos de v e cada vértice
Realiza os cálculos da similaridade no final
*/
void similaridadeCosseno(Grafo* g, int v, float* coeficientes){
  for (int x=0; x< g->numVertices; x++){
    int intercessaoDeVizinhos= 0;
    int vizinhosDeX=0;
    int vizinhosDeV=0;
    for(int possivelVizinho=0; possivelVizinho< g->numVertices;possivelVizinho++){
      bool eVizinhoDeX=g->matriz[x][possivelVizinho];
      bool eVizinhoDeV=g->matriz[v][possivelVizinho];
      intercessaoDeVizinhos += (eVizinhoDeV && eVizinhoDeX);
      vizinhosDeX += eVizinhoDeX;
      vizinhosDeV += eVizinhoDeV;
    }
    float denominador= sqrt(vizinhosDeV * (float)vizinhosDeX);
    if(denominador==0){
      coeficientes[x]=-1;
      continue;
    }
    coeficientes[x]= intercessaoDeVizinhos/denominador;
  }
}


/* Coeficiente de Dice 
Calcula a intercessão de vizinhos de v para cada outro vértice, através de cálculos booleanos
Soma a quantidade de vizinhos de v e cada vértice
Realiza os cálculos do coeficiente de dice no final
*/
void coeficienteDeDice(Grafo* g, int v, float* coeficientes){

  for (int x=0; x< g->numVertices; x++){
    int intercessaoDeVizinhos= 0;
    int vizinhosDeX=0;
    int vizinhosDeV=0;
    for(int possivelVizinho=0; possivelVizinho< g->numVertices;possivelVizinho++){
      bool eVizinhoDeX=g->matriz[x][possivelVizinho];
      bool eVizinhoDeV=g->matriz[v][possivelVizinho]; 
      intercessaoDeVizinhos += eVizinhoDeV && eVizinhoDeX;
      vizinhosDeX += eVizinhoDeX;
      vizinhosDeV += eVizinhoDeV;
    }
    float denominador= vizinhosDeV + vizinhosDeX;
    if(denominador==0){
      coeficientes[x]=-1;
      continue;
    }
    coeficientes[x]= 2*intercessaoDeVizinhos/denominador;
  }

}

int min(int a, int b){
  if(a>b) return b;
  return a;
}
int max(int a, int b){
  if(a<b) return b;
  return a;
}

/* Hub Promoted Index 
Calcula a intercessão de vizinhos de v para cada outro vértice, através de cálculos booleanos
Soma a quantidade de vizinhos de v e cada vértice
Realiza os cálculos da HPI no final, ultizando a função min
*/
void HPI(Grafo* g, int v, float* coeficientes){

  for (int x=0; x< g->numVertices; x++){
    int intercessaoDeVizinhos= 0;
    int vizinhosDeX=0;
    int vizinhosDeV=0;
    for(int possivelVizinho=0; possivelVizinho< g->numVertices;possivelVizinho++){
      bool eVizinhoDeX=g->matriz[x][possivelVizinho];
      bool eVizinhoDeV=g->matriz[v][possivelVizinho];
      intercessaoDeVizinhos += eVizinhoDeV && eVizinhoDeX;
      vizinhosDeX += eVizinhoDeX;
      vizinhosDeV += eVizinhoDeV;
    }
    float denominador= (float)min(vizinhosDeV, vizinhosDeX);
    if(denominador==0){
      coeficientes[x]=-1;
      continue;
    }
    coeficientes[x]= intercessaoDeVizinhos/denominador;
  }

}


/* Hub Depressed Index  
Calcula a intercessão de vizinhos de v para cada outro vértice, através de cálculos booleanos
Soma a quantidade de vizinhos de v e cada vértice
Realiza os cálculos da HDI no final, ultizando a função max
*/
void HDI(Grafo* g, int v, float* coeficientes){
  for (int x=0; x< g->numVertices; x++){
    int intercessaoDeVizinhos= 0;
    int vizinhosDeX=0;
    int vizinhosDeV=0;
    for(int possivelVizinho=0; possivelVizinho< g->numVertices;possivelVizinho++){
      bool eVizinhoDeX=g->matriz[x][possivelVizinho];
      bool eVizinhoDeV=g->matriz[v][possivelVizinho];
      intercessaoDeVizinhos += eVizinhoDeV && eVizinhoDeX;
      vizinhosDeX += eVizinhoDeX;
      vizinhosDeV += eVizinhoDeV;
    }
    float denominador= (float)max(vizinhosDeV, vizinhosDeX);
    if(denominador==0){
      coeficientes[x]=-1;
      continue;
    }
    coeficientes[x]= intercessaoDeVizinhos/denominador;
  }
}


/* Funcao main para testar as funcoes implementadas neste EP.
   Esta parte do codigo nao sera usada na correcao do EP e nao contempla
   todos os testes possiveis.
   Fique a vontade para realizar testes adicionais.
*/
int main() {

  int n = 5;
  int* vComum = (int*)malloc(sizeof(int)*n);
  float* coeficientes = (float*)malloc(sizeof(float)*n);
  
  Grafo g1;

  printf("PRIMEIRO EXEMPLO\n");

  inicializaGrafo(&g1, n);
  insereAresta(&g1,0,1);
  insereAresta(&g1,0,2);
  insereAresta(&g1,1,4);
  insereAresta(&g1,1,3);
  insereAresta(&g1,2,3);

  exibeGrafo(&g1);

  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(&g1, 0, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  coeficienteDeDice(&g1, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HPI(&g1, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HDI(&g1, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("\n\nSEGUNDO EXEMPLO\n");

  // Excluindo duas arestas do grafo
  removeAresta(&g1,0,2);
  removeAresta(&g1,2,3);


  exibeGrafo(&g1);

  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(&g1, 0, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(&g1, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  coeficienteDeDice(&g1, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HPI(&g1, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  HDI(&g1, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);


  /* Grafo gerado aleatoriamente - pode ficar diferente
     de acordo com o compilador usado.                 */
  printf("\nTERCEIRO EXEMPLO\n");
  n = 6;
  int arestas = 8;
  
  free(vComum);
  free(coeficientes);
  vComum = (int*)malloc(sizeof(int)*n);
  coeficientes = (float*)malloc(sizeof(float)*n);
  
  Grafo* g2 = criaGrafoAleatorio(n,arestas);
  exibeGrafo(g2);
  
  printf("Vizinhos em Comum de v0:\n");
  vizinhosEmComum(g2, 0, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Vizinhos em Comum de v1:\n");
  vizinhosEmComum(g2, 1, vComum);
  exibeArranjoInteiros(vComum, n);

  printf("Vizinhos em Comum de v5:\n");
  vizinhosEmComum(g2, 5, vComum);
  exibeArranjoInteiros(vComum, n);


  printf("Coeficientes de Jaccard de v0:\n");
  coeficienteDeJaccard(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficientes de Jaccard de v1:\n");
  coeficienteDeJaccard(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficientes de Jaccard de v5:\n");
  coeficienteDeJaccard(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  printf("Medida de Adamic-Adar de v0:\n");
  AdamicAdar(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v1:\n");
  AdamicAdar(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Adamic-Adar de v5:\n");
  AdamicAdar(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  printf("Medida de Alocacao de Recursos de v0:\n");
  alocacaoDeRecursos(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v1:\n");
  alocacaoDeRecursos(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Medida de Alocacao de Recursos de v5:\n");
  alocacaoDeRecursos(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  printf("Similaridade Cosseno de v0:\n");
  similaridadeCosseno(g2, 0, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v1:\n");
  similaridadeCosseno(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Similaridade Cosseno de v5:\n");
  similaridadeCosseno(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  coeficienteDeDice(g2, 0, coeficientes);
  printf("Coeficiente de Dice de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Coeficiente de Dice de v1:\n");
  coeficienteDeDice(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Coeficiente de Dice de v5:\n");
  coeficienteDeDice(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);


  HPI(g2, 0, coeficientes);
  printf("Indice HPI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Indice HPI de v1:\n");
  HPI(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Indice HPI de v5:\n");
  HPI(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);
  
  
  HDI(g2, 0, coeficientes);
  printf("Indice HDI de v0:\n");
  exibeArranjoReais(coeficientes, n);

  printf("Indice HDI de v1:\n");
  HDI(g2, 1, coeficientes);
  exibeArranjoReais(coeficientes, n);

  printf("Indice HDI de v5:\n");
  HDI(g2, 5, coeficientes);
  exibeArranjoReais(coeficientes, n);
  scanf("%s\n");
  return 0;  
}