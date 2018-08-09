// Instituto de Computacao
// Banco de Dados 1
// Aluno: Edwin Juan Lopes Barboza Monteiro
// Matricula: 21453380
// Aluno: Thiago Moraes Rocha
// Matricula:21452625

#ifndef LinkedLista_h
#define LinkedLista_h

#include <iostream>
#include <string>
#include "LinkedList.h"
using namespace std;


//Struct para representar o bloco, contem uma referencia para a lista de registros,
//o tamanho do bloco e o numero de registros 
struct noBloco{    
  LinkedList *regTopo;
  int tamanhoBloco;
  int numRegistros;    
  noBloco * prox;
};

class LinkedLista{
public:
  //Ponteiro para o primeiro bloco  
 noBloco * prim;
 //Ponteiro para o ultimo bloco
 noBloco * cauda;
 int total_Bloco;
//Constroi um objeto vazio do tipo LinkedList 
//Cria o nó que referencia a lista de blocos, seta a variável length para 0. 
 LinkedLista();
 //Procedimento para inserir um novo bloco  
 void insereBloco(noBloco * noAtual);
 //Exibe o estado atual dos blocos
 void imprimeLista();
//Gera Binario
 void geraBinarioBloco();    
//Desaloca a memoria utilizada pela lista
 ~LinkedLista();
};

#endif