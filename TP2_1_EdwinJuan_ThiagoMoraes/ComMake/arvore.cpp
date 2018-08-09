#include<iostream>
using namespace std;


class NOarvore{
  int *chaves; //vetor com as chaves
  int ordem; //ordem da arvore
  NOarvore **filhos; // um vetor de ponteiros para os filhos
  int n_chaves; //numero de chaves
  bool folha; //é verdadeiro se o nó for folha e false caso contrário
public:
  NOarvore(int ordem, bool folha);
  void inserir_n_cheio(int chave);
  void splitfilho(int i, NOarvore *no);
  void imprimir();
  NOarvore *busca(int chave);
friend class ArvoreB;
};

class ArvoreB{
  NOarvore *raiz;
  int ordem;
public:
  ArvoreB(int ordem){//construtor da arvore
    raiz = NULL;
    ordem = ordem;
  }
  void imprimir(){ //declaracao da funcao imprimir
    if(raiz!=NULL){
      raiz -> imprimir();
    }
  }
  NOarvore* busca(int chave){return (raiz == NULL)? NULL : raiz->busca(chave); } //declaracao da funcao busca
  void inserir(int chave);
};

NOarvore::NOarvore(int grau, bool folha){ //criando o construtor do no da arvore
  ordem = grau;
  folha = folha;
  chaves= new int [2*ordem-1];
  filhos = new NOarvore *[2*ordem];
  n_chaves=0;
}
void NOarvore::imprimir(){ // funcao para imprimir os nós
  int i;
  for(i=0;i<n_chaves;i++){
    if(folha == false){
      filhos[i]->imprimir();
    }
    cout<<" "<< chaves[i];
  }
  if(folha == false){
    filhos[i]->imprimir();
  }
}
NOarvore *NOarvore::busca(int chave){ //funcao que busca uma chave no nó
  int i;
  i=0;
  while(i < n_chaves && chave > chaves[i]){
    i++;
  }
  if(chaves[i]==chave){
    return this;
  }
  if(folha == true){
    return NULL;
  }
  return filhos[i]->busca(chave);
}
void ArvoreB::inserir(int chave){ //funcao para inserir uma chave
  if(raiz == NULL){
    raiz = new NOarvore(ordem, true);
    raiz -> chaves[0] = chave;
    raiz -> n_chaves = 1;
  }
  else{
    if(raiz ->n_chaves == 2*ordem-1){
      NOarvore *novoNO= new NOarvore(ordem, false);
      novoNO->filhos[0] = raiz;
      novoNO->splitfilho(0,raiz);

      int i=0;
      if(novoNO->chaves[0]<chave){
        i++;
      }
      novoNO->filhos[i]->inserir_n_cheio(chave);
      raiz = novoNO;
    }
    else{
      raiz -> inserir_n_cheio(chave);
    }
  }
}
void NOarvore::inserir_n_cheio(int chave){ //inserir casa os nós não estejam cheios
  int i = n_chaves-1;
  if(folha == true){
    while(i>=0 && chaves[i] > chave){
      chaves[i+1] = chaves[i];
      i--;
    }
    chaves[i+1]=chave;
    n_chaves = n_chaves+1;
  }
  else{
    while(i>=0 && chaves[i] > chave){
      i--;
    }
    if(filhos[i+1]->n_chaves == 2*ordem-1){
      splitfilho(i+1, filhos[i+1]);
      if(chaves[i+1]<chave){
        i++;
      }
    }
  filhos[i+1]->inserir_n_cheio(chave);
  }
}
void NOarvore::splitfilho(int i, NOarvore *no){// funcao para subdividir o nó quando ele estiver cheio
  NOarvore *aux = new NOarvore(no->ordem, no->folha);
  aux->n_chaves = ordem - 1;

  for(int j=0; j<ordem-1;j++){
    aux ->chaves[j] = no->chaves[j+ordem];
  }
  if(no->folha == false){
    for(int j=0;j<ordem;j++){
      aux->filhos[j] = no->filhos[j+ordem];
    }
  }
  no->n_chaves = ordem-1;

  for(int j=n_chaves;j >=i+1;j--){
    filhos[j+1]= filhos[j];
  }

  filhos[i+1]= aux;

  for(int j=n_chaves-1;j>=i;j--){
    chaves[j+1]= chaves[j];
  }

  chaves[i]=no->chaves[ordem-1];
  n_chaves=n_chaves+1;
}

int main(){
  ArvoreB arvore(3);
  t.inserir(1);

FILE *ptr_leitura = NULL; // aponteiro para o  arquivo
ptr_leitura = fopen("data.bin", "rb"); //abrindo o arquivo binario para leitura
if(ptr_leitura){
  cout << "Arquivo aberto com sucesso!" << endl;

  //-----------------
  //Filtra os campos
  int id=0;
  char titulo[300]={0};
  int ano=0;
  char autores[100]={0};
  int citacoes=0;
  char data[19]={0};
  char _snippet[100]={0};
  int  inicial=0;
  int  fim;


  inicial = ftell(ptr_leitura); //posicao inicial do arquivo

  fread(&id,sizeof(int),1, ptr_leitura);
  fread(titulo,sizeof(char),300, ptr_leitura);
  fread(&ano,sizeof(int),1, ptr_leitura);
  fread(autores,sizeof(char),100, ptr_leitura);
  fread(&citacoes,sizeof(int),1, ptr_leitura);
  fread(data,sizeof(char),19, ptr_leitura);
  fread(_snippet,sizeof(char),100, ptr_leitura);
  fim = ftell(ptr_leitura); //posicao final

  arvore.Insert(id) //indexar os ids

return 0;
}
