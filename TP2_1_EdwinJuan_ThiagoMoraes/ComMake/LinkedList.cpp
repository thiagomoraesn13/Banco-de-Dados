// Instituto de Computacao
// Banco de Dados 1
// Aluno: Edwin Juan Lopes Barboza Monteiro
// Matricula: 21453380
// Aluno: Thiago Moraes Rocha
// Matricula:21452625

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

//Constroi um objeto vazio do tipo LinkedList 
LinkedList::LinkedList(){
  head = new Item;
  head -> next = NULL;
  length = 0;
  cauda = NULL;
}

//Insere um item no final da lista
void LinkedList::insertItemv2( Item * newItem){  
  if(head -> next == NULL){
    head -> next = newItem;
    length++;    
  }else{    
    newItem -> next = head->next;
    head->next = newItem;
    length++;
  }
}

//Remove um item da lista pela chave
//Retorna True se for bem sucedida
bool LinkedList::removeItem(int itemKey){
  if (!head -> next) return false;
  Item * p = head;
  Item * q = head;
  while (q)
  {
    if (q -> id == itemKey)
    {
      p -> next = q -> next;
      delete q;
      length--;
      return true;
    }
    p = q;
    q = p -> next;
  }
  return false;
}

//Procura por um item atraves da chave
//Retorna a referencia para o primeiro encontrado
//Retora NULL caso não encontre
Item * LinkedList::getItem( int itemKey ){
  Item * p = head;
  Item * q = head;
  while (q)
  {
    p = q;
    if ((p != head) && (p -> id == itemKey))
      return p;
    q = p -> next;
  }
  return NULL;
}

//Imprime a lista de registros
void LinkedList::printListv2(){
  Item *lista = head -> next;
  while(lista != NULL){
    cout << "Id: " << lista -> id << endl;
    cout << "Title: ";
    for(int x = 0; x < 300; x++){
      cout << lista -> titulo[x];
    }
    cout << endl;
    cout << "Ano: " << lista -> ano << endl;
    for(int x = 0; x < 100; x++){
      cout << lista -> autores[x];
    }
    cout << endl;
    cout << "Citações: " << lista -> citacoes << endl;
    for(int x = 0; x < 19; x++){
      cout << lista -> data[x];
    }
    cout << endl;
    for(int x = 0; x < 100; x++){
      cout << lista -> _snippet[x];
    }
    cout << endl;
    lista = lista -> next;
  }
}

//Ponteiro para o arquivo de saida em binario de acordo com o caminhamento no Hash 
FILE *ptr_escrita = fopen("data.bin", "wb");

void LinkedList::geraBinarioRegistro(){
  if(ptr_escrita){
    Item *lista = head -> next;
    while(lista != NULL){
      fwrite(&lista -> id, sizeof(int), 1, ptr_escrita);
      fwrite(lista -> titulo, sizeof(char), 300, ptr_escrita);
      fwrite(&lista -> ano, sizeof(int), 1, ptr_escrita);
      fwrite(lista -> autores, sizeof(char), 100, ptr_escrita);
      fwrite(&lista -> citacoes, sizeof(int), 1, ptr_escrita);
      fwrite(lista -> data, sizeof(char), 19, ptr_escrita);
      fwrite(lista -> _snippet, sizeof(char), 100, ptr_escrita);
      lista = lista -> next;    
    }    
  }else{
    cout << "Ocorreu um erro ao abrir o arquivo" << endl;
    return;
  }
}

//Retorna o tamanho da lista
int LinkedList::getLength(){
  return length;
}

//Desaloca a lista da memoria quando o programa termina.
LinkedList::~LinkedList(){
  Item * p = head;
  Item * q = head;
  while (q)
  {
    p = q;
    q = p -> next;
    if (q) delete p;
  }
}
