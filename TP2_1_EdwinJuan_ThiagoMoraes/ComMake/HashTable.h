// Instituto de Computacao
// Banco de Dados 1
// Aluno: Edwin Juan Lopes Barboza Monteiro
// Matricula: 21453380
// Aluno: Thiago Moraes Rocha
// Matricula:21452625

#ifndef HashTable_h
#define HashTable_h

#include "LinkedLista.h"

#include "LinkedList.h"

class HashTable{
public:
    //Ponteiro para o vetor de Bucket, inicializado no arquivo HashTable.cpp
    LinkedLista * array;
    //Tamanho do vetor de Buckets.
    int length;
    //Retorna uma posição vetor para uma chave informada
    int hash( int itemKey );
    //Constroi um objeto vazio do tipo HashTable.
    //O tamanho do vetor é definido por padrão como 13 se ñão for informado.
    HashTable( int tableLength = 100000 );
    //Insere um No relacionado ao bloco, tendo de informar também o id do registro para o mapeamento via função hash
    void insertItem(noBloco * newItem, int id );
    
    //Exibe o conteúdo do hash.
    void printTable();

    //Gera Binário
    void geraBinarioBucket();

    //Printa um histrograma do Hash.
    // void printHistogram();    

    // Desaloca toda a memoria utilizada pelo Hash.
    ~HashTable();
};

#endif
