// Instituto de Computacao
// Banco de Dados 1
// Aluno: Edwin Juan Lopes Barboza Monteiro
// Matricula: 21453380
// Aluno: Thiago Moraes Rocha
// Matricula:21452625

#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <string>
using namespace std;

//Nó que representa um registro com todos os seus campos
struct Item{
  int id;
  char titulo[300];
  int ano;
  char autores[100];
  int citacoes;
  char data[100];
  char _snippet[100];
  Item * next;
};

class LinkedList{
public:
  //Ponteiro para o topo da lista
  Item * head;
  //Ponteiro para o último elemento da lista
  Item * cauda;
  // Length é o numero de nos da lista.
  int length;

  //Constroi um objeto vazio do tipo LinkedList 
  //Cria o nó que referencia a lista, seta a variável length para 0.  
  LinkedList();
  
  //Insere um item no final da lista
  void insertItemv2( Item * item );

  //Remove um elemento da lista pela chave id
  //Retorna True se a operação for realizada com sucesso
  bool removeItem( int itemKey );

//Procura por um item atraves da chave
//Retorna a referencia para o primeiro encontrado
//Retora NULL caso não encontre
  Item * getItem( int itemKey );

  //Exibe a lista de registros
  void printListv2();

  //Retorna o tamanho da lista
  int getLength();

  //Gera Binario
  void geraBinarioRegistro();


  // De-allocates list memory when the program terminates.
  ~LinkedList();
};

#endif

