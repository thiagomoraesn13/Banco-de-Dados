// Instituto de Computacao
// Banco de Dados 1
// Aluno: Edwin Juan Lopes Barboza Monteiro
// Matricula: 21453380
// Aluno: Thiago Moraes Rocha
// Matricula:21452625

#include "HashTable.h"

//Constroi um objeto vazio do tipo HashTable.
//O tamanho do vetor é definido por padrão como 13 se ñão for informado.
HashTable::HashTable( int tableLength ){
  if (tableLength <= 0) tableLength = 1000000;
  array = new LinkedLista[ tableLength ];
  length = tableLength;
}

//Funcao Hash que calcula o indice do Bucket por meio da chave - utilizando o ID
int HashTable::hash( int itemKey ){
  int value = 0;  
  return itemKey % length;
}

//Insere um No relacionado ao bloco, tendo de informar também o id do registro para o mapeamento via função hash
void HashTable::insertItem( noBloco * newItem, int id ){
  int index = hash(id);
  array[ index ].insereBloco(newItem);  
}

//Exibe o conteúdo do hash.
void HashTable::printTable(){
  cout << "\n\nHash Table:\n";
  for ( int i = 0; i < length; i++ )
  {
    cout << "Bucket " << i << ": " << endl;
    array[i].imprimeLista();
  }
}

//Gera Binario
void HashTable::geraBinarioBucket(){
  for ( int i = 0; i < length; i++ )
  {
    // cout << "Bucket " << i << ": " << endl;
    array[i].geraBinarioBloco();
  }
}

    //Printa um histrograma do Hash.
// void HashTable::printHistogram()
// {
//   cout << "\n\nHash Table Contains ";
//   cout << getNumberOfItems() << " Items total\n";
//   for ( int i = 0; i < length; i++ )
//   {
//     cout << i + 1 << ":\t";
//     for ( int j = 0; j < array[i].getLength(); j++ )
//     cout << " X";
//     cout << "\n";
//   }
// }

// Desaloca toda a memoria utilizada pelo Hash.
HashTable::~HashTable()
{
  delete [] array;
}
