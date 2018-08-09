/*
Universidade Federal Do Amazonas
Insituto de Computação
Banco de Dados 1
Trabalho Prático 1
Aluno: Edwin Juan Lopes Barboza Monteiro
Matrícula: 21453380
Aluno: Thiago Moraes
Matrícula: 21452625
*/
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <pqxx/pqxx>
#include <cstring>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[]){
	//Ler credenciais
	string dbname="";
	cout << "Digite o nome do banco: " << endl;
	cin >> dbname;

	string user="";
	cout << "Digite o nome do usuario: " << endl;
	cin >> user;

	string password="";
	cout << "Digite a senha: " <<endl;
	cin >> password;


	string hostaddr="127.0.0.1";
	//cout << "Digite o nome do host: " << endl;
	//cin >> hostaddr;

	string arquivo="";
	cout << "Digite o nome do arquivo .txt: " << endl;
	cin >> arquivo;

	string port="";
	cout << "Digite o nome da porta: " << endl;
	cin >> port;
	
	char* sql = new char[255];
	try{
		connection C("dbname="+dbname+ " user="+user+ " password="+password+ " hostaddr="+hostaddr+ " port="+port);
		if (C.is_open()) {
			cout << "Conectado a base de dados!" << endl;
		} else {
			cout << "Erro de conexão" << endl;
			return 1;
		}

		try{
			string sqlTable="";
			sqlTable = "CREATE TABLE Product (" \
			"ASIN char(10) PRIMARY KEY," \
			"TITLE varchar NOT NULL," \
			"GROUPP varchar NOT NULL," \
			"SALESRANK integer NOT NULL," \
			"AVG_RATING real NOT NULL," \
			"TOTAL_REVIEWS integer NOT NULL);";

			work W(C);
			W.exec(sqlTable);
			W.commit();
		}catch (const std::exception &e){
			cerr << e.what() << std::endl;
			return 1;
		}

		try{
			string sqlTable="";

			sqlTable = "CREATE TABLE Similarr (" \
			"ASIN char(10) NOT NULL," \
			"RELATED_ASIN char(10) NOT NULL, FOREIGN KEY (ASIN) REFERENCES Product (ASIN), PRIMARY KEY (ASIN, RELATED_ASIN));";

			work Q(C);
			Q.exec(sqlTable);
			Q.commit();
		}catch (const std::exception &e){
			cerr << e.what() << std::endl;
			return 1;
		}

		try{
			string sqlTable="";

			sqlTable = "CREATE TABLE Categories (ASIN char(10) NOT NULL, ID integer NOT NULL, NAME varchar NOT NULL, FOREIGN KEY (ASIN) REFERENCES Product (ASIN), PRIMARY KEY (ASIN, ID));";

			work R(C);
			R.exec(sqlTable);
			R.commit();
		}catch (const std::exception &e){
			cerr << e.what() << std::endl;
			return 1;
		}

		try{
			string sqlTable="";

			sqlTable = "CREATE TABLE Reviews (ID SERIAL PRIMARY KEY, ASIN char(10) NOT NULL, DATE date NOT NULL, CUSTOMER varchar NOT NULL, RATING integer NOT NULL, VOTES integer NOT NULL, HELPFUL integer NOT NULL, FOREIGN KEY (ASIN) REFERENCES Product (ASIN));";

			work Y(C);
			Y.exec(sqlTable);
			Y.commit();
		}catch (const std::exception &e){
			cerr << e.what() << std::endl;
			return 1;
		}




		system("python3 povoamento.py");


		int chave = 0;
		cout << endl;
		char* escolha = new char[1];
		std::strcpy(escolha, "s");
		while(!strcmp(escolha, "s")){
			cout << "Opções disponíveis:" << endl;

			cout << "1 - Listar 5 comentários mais úteis e com maior e menor avaliação" << endl;

			cout << "2 - mostrar a evolução diária das médias de avaliação ao longo do intervalo de tempo" << endl;

			cout << "3 - Produtos lideres de venda em cada grupo de produtos" << endl;

			cout << "4 - Listar produtos com a maior média de avaliações úteis positivas por produto" << endl;

			cout << "5 - Listar as 5 categorias de produto com a maior média de avaliações úteis positivas por produto" << endl;

			cout << "Escolha uma opção entre 1-5: ";
			cin >> chave;
			cout << endl;
			if(chave == 1){
				std::strcpy(sql, "SELECT * FROM Reviews ORDER BY helpful DESC, votes DESC LIMIT 5");
				nontransaction N(C);
				result R(N.exec(sql));
				cout << "Listar 5 comentários mais úteis e com maior avaliação" << endl;
				for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
          cout << "ID = " << c[0].as<std::string>();// << endl;
          cout << ", ASIN = " << c[1].as<std::string>();// << endl;
          cout << ", DATE = " << c[2].as<std::string>();// << endl;
          cout << ", CUSTOMER = " << c[3].as<std::string>();// << endl;
          cout << ", RATING = " << c[4].as<std::string>();///\\ << endl;
          cout << ", VOTES = " << c[5].as<std::string>();
          cout << ", HELPFUL = " << c[6].as<std::string>() << endl;
      }
      C.disconnect ();
      try{
      	connection C("dbname=consultas user=postgres password=bdtp001 \
      		hostaddr=127.0.0.1 port=5432");
      	char * sql2 = new char[255];
      	cout << "5 comentários mais úteis e com menor avaliação" << endl;
      	std::strcpy(sql2, "SELECT * FROM Reviews ORDER BY helpful DESC, votes LIMIT 5;");
      	nontransaction B(C);
      	result Re(B.exec(sql2));
      	for (result::const_iterator c = Re.begin(); c != Re.end(); ++c) {
            cout << "ID = " << c[0].as<std::string>();// << endl;
            cout << ", ASIN = " << c[1].as<std::string>();// << endl;
            cout << ", DATE = " << c[2].as<std::string>();// << endl;
            cout << ", CUSTOMER = " << c[3].as<std::string>();// << endl;
            cout << ", RATING = " << c[4].as<std::string>();///\\ << endl;
            cout << ", VOTES = " << c[5].as<std::string>();
            cout << ", HELPFUL = " << c[6].as<std::string>() << endl;
        }
    }
    catch (const std::exception &e){
    	cerr << e.what() << std::endl;
    	return 1;
    }
}
else if(chave == 2){
	cout << "Mostrar a evolução diária das médias de avaliação ao longo do intervalo de tempo" << endl;
	std::strcpy(sql, "select asin,date, avg(rating) as media from reviews group by asin, date order by date");
	nontransaction N(C);
	result R(N.exec(sql));
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
          cout << "ASIN = " << c[0].as<std::string>();// << endl;
          cout << ", DATE = " << c[1].as<std::string>();// << endl;
          cout << ", media = " << c[2].as<std::string>() << endl;
      }
  }
  else if(chave == 3){
  	cout << "Produtos lideres de venda em cada grupo de produtos" << endl;
  	cout << endl;
  	cout << "Grupp: Book" << endl;
  	std::strcpy(sql, "select asin, title, groupp, salesrank from product where groupp='Book' order by salesrank desc limit 10;");
  	nontransaction N(C);
  	result R(N.exec(sql));
  	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
          cout << "ASIN = " << c[0].as<std::string>();// << endl;
          cout << ", TITLE = " << c[1].as<std::string>();// << endl;
          cout << ", GROUPP = " << c[2].as<std::string>();// << endl;
          cout << ", SALESRANK = " << c[3].as<std::string>() << endl;
      }
      C.disconnect ();
      try{
      	connection C("dbname=consultas user=postgres password=bdtp001 \
      		hostaddr=127.0.0.1 port=5432");
      	cout << endl;
      	cout << "Groupp: DVD" << endl;
      	cout << endl;
      	std::strcpy(sql, "select asin, title, groupp, salesrank from product where groupp='DVD' order by salesrank desc limit 10");
      	nontransaction N(C);
      	result R(N.exec(sql));
      	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << "ASIN = " << c[0].as<std::string>();// << endl;
            cout << ", TITLE = " << c[1].as<std::string>();// << endl;
            cout << ", GROUPP = " << c[2].as<std::string>();// << endl;
            cout << ", SALESRANK = " << c[3].as<std::string>() << endl;
        }
    }
    catch (const std::exception &e){
    	cerr << e.what() << std::endl;
    	return 1;
    }
    C.disconnect ();
    try{
    	connection C("dbname=consultas user=postgres password=bdtp001 \
    		hostaddr=127.0.0.1 port=5432");
    	cout << "Grupp: Video" << endl;
    	cout << endl;
    	std::strcpy(sql, "select asin, title, groupp, salesrank from product where groupp='Video' order by salesrank desc limit 10");
    	nontransaction N(C);
    	result R(N.exec(sql));
    	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << "ASIN = " << c[0].as<std::string>();// << endl;
            cout << ", TITLE = " << c[1].as<std::string>();// << endl;
            cout << ", GROUPP = " << c[2].as<std::string>();// << endl;
            cout << ", SALESRANK = " << c[3].as<std::string>() << endl;
        }
    }
    catch (const std::exception &e){
    	cerr << e.what() << std::endl;
    	return 1;
    }
    C.disconnect ();
    try{
    	connection C("dbname=consultas user=postgres password=bdtp001 \
    		hostaddr=127.0.0.1 port=5432");
    	cout << "Grupo: Music" << endl;
    	cout << endl;
    	std::strcpy(sql, "select asin, title, groupp, salesrank from product where groupp='Music' order by salesrank desc limit 10");
    	nontransaction N(C);
    	result R(N.exec(sql));
    	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
            cout << "ASIN = " << c[0].as<std::string>();// << endl;
            cout << ", TITLE = " << c[1].as<std::string>();// << endl;
            cout << ", GROUPP = " << c[2].as<std::string>();// << endl;
            cout << ", SALESRANK = " << c[3].as<std::string>() << endl;
        }
    }
    catch (const std::exception &e){
    	cerr << e.what() << std::endl;
    	return 1;
    }
}
else if(chave == 4){
	cout << "Listar produtos com a maior média de avaliações úteis positivas por produto" << endl;
	cout << endl;
	std::strcpy(sql, "Select ASIN, AVG(helpful) AS media FROM Reviews group by asin ORDER BY media DESC LIMIT 10;");
	nontransaction N(C);
	result R(N.exec(sql));
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
          cout << "ASIN = " << c[0].as<std::string>();// << endl;
          cout << ", MEDIA = " << c[1].as<std::string>() << endl;
      }
  }
  else if(chave == 5){
  	cout << "Listar as 5 categorias de produto com a maior média de avaliações úteis positivas por produto" << endl;
  	cout << endl;
  	std::strcpy(sql, "select M.name,V.avghelp from (select asin, avg(helpful) as avghelp from reviews group by asin) as V join (select name, asin from categories group by asin,name) as M on M.asin = V.asin order by V.avghelp DESC limit 5");
  	nontransaction N(C);
  	result R(N.exec(sql));
  	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
          cout << "Name = " << c[0].as<std::string>();// << endl;
          cout << ", AVG_HELPFUL = " << c[1].as<std::string>() << endl;
      }
  }
  cout << "Deseja continuar? s/n? ";
  cin >> escolha;
  system("clear");
}
cout << "Operação concluída com sucesso." << endl;
C.disconnect ();
}
catch (const std::exception &e){
	cerr << e.what() << std::endl;
	return 1;
}
return 0;
}
