// Instituto de Computacao
// Banco de Dados 1
// Aluno: Edwin Juan Lopes Barboza Monteiro
// Matricula: 21453380
// Aluno: Thiago Moraes Rocha
// Matricula:21452625

#include "LinkedLista.h"
#include <unistd.h>

//Constroi um objeto vazio do tipo LinkedList 
//Cria o nó que referencia a lista de blocos, seta a variável total_blocos para 0.
LinkedLista::LinkedLista(){
    prim = new noBloco;
    prim -> prox = NULL;
    total_Bloco = 0;
    cauda = NULL;
}

//Procedimento para inserir um novo bloco  
void LinkedLista::insereBloco(noBloco * noAtual){
    if(prim -> prox == NULL){
        noAtual -> prox = prim -> prox;
        prim -> prox = noAtual;
        cauda = prim -> prox;
        total_Bloco++;        
    }
    else{
        noBloco * tmp = cauda;
        noAtual -> prox = tmp -> prox;
        tmp -> prox = noAtual;
        cauda = tmp -> prox;
        total_Bloco++;
        delete tmp;
    }
}

//Exibe o estado atual dos blocos
void LinkedLista::imprimeLista(){
    if(prim -> prox != NULL){
        if(prim -> prox->regTopo != NULL){
            noBloco * noAtual = prim -> prox;
                noAtual->regTopo->printListv2();            
        }        
    }    
}


void LinkedLista::geraBinarioBloco(){
    if(prim -> prox != NULL){
        if(prim -> prox->regTopo != NULL){
            noBloco * noAtual = prim -> prox;
                noAtual->regTopo->geraBinarioRegistro();            
        }        
    }    
}

//Desaloca toda a memoria usada pela lista de blocos
LinkedLista::~LinkedLista(){
    noBloco * p = prim;
    noBloco * q = prim;
    while (q){
        p = q;
        q = p -> prox;
        if (q) delete p;
    }
}