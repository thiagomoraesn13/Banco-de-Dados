// Instituto de Computacao
// Banco de Dados 1
// Aluno: Edwin Juan Lopes Barboza Monteiro
// Matricula: 21453380
// Aluno: Thiago Moraes Rocha
// Matricula:21452625

#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>
#include "HashTable.h"
#include "LinkedList.h"
#include <unistd.h>
using namespace std;


int main (){
  string nomeArquivoLeitura;
  cout << "Informe o nome do aquivo csv, exemplo artigo.csv" << endl;
  cin >> nomeArquivoLeitura;
  ifstream ptr_artigo (nomeArquivoLeitura);  

  int idx_campo=0;
  int id = 0;
  char titulo [300] = {0};
  int ano = 0;
  char autores[100] = {0};
  int citacoes = 0;
  char data[19] = {0};
  char snip[100] = {0};
  string line;
  string tmp_line = "";

  size_t blockCount = 0;
  HashTable table;        
  while(getline(ptr_artigo, line)){
    idx_campo = 0;
    if(line.at(0)!='"'){
      getline(ptr_artigo, line);
    }
    Item *A = new Item;
    A -> id = 0;
    A -> titulo[300] = {0};
    A -> ano = 0;
    A -> autores[100]= {0};
    A -> citacoes = 0;
    A -> data[19] = {0};
    A -> _snippet[100] = {0};
    A -> next = NULL;
    for(int i = 0; i < line.length(); i++){
      if(line.at(i)=='"'){
        ++i;
        for(;i<line.length()&&line.at(i)!='"'; i++){
          tmp_line = tmp_line + line.at(i);
        }
        if(idx_campo == 0){
          id = stoi(tmp_line);
          A -> id = id;
          //fwrite(&id, sizeof(int), 1, ptr_escrita);
          ++idx_campo;
        }
        else if (idx_campo == 1){
          for(int x = 0; x < 300 && x < tmp_line.length(); x++){
            titulo[x] = tmp_line.at(x);
            A -> titulo[x] = tmp_line.at(x);
          }
          //fwrite(titulo, sizeof(char), sizeof(titulo), ptr_escrita);
          ++idx_campo;
        }
        else if(idx_campo == 2){
          ano = stoi(tmp_line);
          A -> ano = ano;
          //fwrite(&ano, sizeof(int), 1, ptr_escrita);
          ++idx_campo;
        }
        else if(idx_campo == 3){
          for(int x = 0; x < 100 && x < tmp_line.length(); x++){
            autores[x] = tmp_line.at(x);
            A -> autores[x] = tmp_line.at(x);
          }
          //fwrite(autores, sizeof(char), sizeof(autores), ptr_escrita);
          ++idx_campo;
        }
        else if(idx_campo == 4){
          citacoes = stoi(tmp_line);
          A -> citacoes = citacoes;
          //fwrite(&citacoes, sizeof(int), 1, ptr_escrita);
          ++idx_campo;
        }
        else if(idx_campo == 5){
          for(int x = 0; x < 19 && x < tmp_line.length(); x++){
            data[x] = tmp_line.at(x);
            A -> data[x] = tmp_line.at(x);
          }
          //fwrite(data, sizeof(char), sizeof(data), ptr_escrita);
          ++idx_campo;
        }
        else if (idx_campo == 6){
          for(int x = 0; x < 100 && x < tmp_line.length(); x++){
            snip[x] = tmp_line.at(x);
            A -> _snippet[x] = tmp_line.at(x);
          }
         //fwrite(snip, sizeof(char), sizeof(snip), ptr_escrita);            
          noBloco * registro2 = new noBloco;
          registro2 -> prox = NULL;
          registro2 -> regTopo = new LinkedList();
          registro2 -> regTopo->insertItemv2(A);  
          table.insertItem(registro2,A->id);
          cout << endl;
          ++idx_campo;
        }
      }
      ++i;
      tmp_line = "";
    }
  }
  //table.printTable();  
  table.geraBinarioBucket();
  cout << "Hash povoado" << endl;
  cout << "Binario gerado a partir do Hash, nome do arquivo: data.bin" << endl;
  // cout << "Exibir o arquivo binario?" << endl;
  // cout << "s/n ?" << endl;
  // string resposta;
  // cin >> resposta;
  // if(resposta == "s"){
  //   system("xxd -b data.bin");
  // }
  ptr_artigo.close();  
  return 0;
}
