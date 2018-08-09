'''
Universidade Federal Do Amazonas
Insituto de Computacao
Banco de Dados 1
Trabalho Prático 1
Aluno: Edwin Juan Lopes Barboza Monteiro
Matricula: 21453380
Aluno: Thiago Moraes
Matricula: 21452625
   O codigo para copiar os dados do arquivo para o banco de dados foi feito na linguagem Python 3
   '''
import psycopg2
import sys
import pprint
import time

conn = None
cursor = None
cont = 0
incrementt = 0

#funcao para conectar ao banco de dados, dbname é o nome do banco
def conecta_BD():
	#Credenciais do SGBD	
	dbnametext = input('Digite o nome do banco: ')
	usertext = input('Digite o nome de usuario: ')
	passwordtext = input('Digite a senha: ')
	nomearquivo = input('Digite o nome do arquivo: ')
	
	conn_string = "host='127.0.0.1' dbname="+dbnametext+ " user="+usertext+ " password="+passwordtext
	print ("Conectando ao banco...")
	print ("Conectado!")
	print ("Povoando...")
	#Conecta ao BD existente
	try:
		global conn
		global cursor
		conn = psycopg2.connect(conn_string)
		cursor = conn.cursor()
	except:
		print ("Impossivel Conectar")

conecta_BD()

#funcao para inserir no banco
def insert_BD(str, vet, asin):
	global conn
	global cursor
	try:
		if(str=="product"):
			cursor.execute("INSERT INTO Product VALUES (%s, %s ,%s, %s, %s, %s)", (vet[0], vet[1], vet[2], vet[3], vet[4], vet[5],))
		elif(str=="reviews"):
			cursor.execute("INSERT INTO Reviews VALUES (%s,%s, %s, %s, %s, %s, %s)", (incrementt,asin,vet[0], vet[2], vet[4],vet[6],vet[8],))
			global incrementt
			incrementt = incrementt + 1
		elif(str=="similar"):
			cursor.execute("INSERT INTO Similarr VALUES (%s,%s)",(asin,vet[0],))
		elif (str=="categories"):
			cursor.execute("INSERT INTO Categories VALUES (%s,%s,%s)",(asin,vet[0],vet[1],))
	except ValueError:
		print ("Erro na insercao")
		print(ValueError)
	conn.commit()

arquivo = open('amazon-meta.txt', 'r')
linha = arquivo.readline()
vet=[] #Vetor vazio
while linha:
	if(linha != "\n"):
		valor = linha.split()
		if (valor[0]== "ASIN:"):
			#insercao no vetor
			asin=valor[1]
			vet.append(valor[1])
		elif (valor[0] == "discontinued"):
			linha = arquivo.readline()
			vet = []
		elif (valor[0]=="title:"):
			str=""
			for i in range (1, len(valor)):
				#Pega todo o titulo
				str = str + valor[i] +" "
			vet.append(str)
			#Insere no vetor o valor do sales
		elif (valor[0]=="group:"):
			vet.append(valor[1])
		elif (valor[0]=="salesrank:"):
			vet.append(valor[1])
		elif(valor[0]=="reviews:"):
			vet.append(valor[7])
			vet.append(valor[2])
			insert_BD("product",vet,asin)
			cont = cont + 1
			for m in range (int(valor[4])):
				linha=arquivo.readline()
				aux = linha.split()
				insert_BD("reviews",aux, asin)
			vet=[]
	linha = arquivo.readline()
arquivo.close()


arquivo = open('amazon-meta.txt', 'r')
linha = arquivo.readline()
while linha:
	if(linha != "\n"):
		valor = linha.split()
		if (valor[0]== "ASIN:"):
			#insercao no vetor
			asin=valor[1]
		elif (valor[0] == "discontinued"):
			linha = arquivo.readline()
			vet = []
		elif (valor[0]=="similar:"):
			for j in range (int(valor[1])):
				vet = [valor[j+2]]
				try:
					cursor.execute("INSERT INTO Similarr VALUES (%s,%s)",(asin,vet[0],))
				except ValueError:
					print ("Erro na insercao")
					print(ValueError)
				conn.commit()

		elif(valor[0]=="categories:"):
			for k in range (int(valor[1])):
				linha = arquivo.readline()
				aux = linha.split("|")
				for l in range (1, len(aux)):
					tmp = aux[l].split("[")
					if(len(tmp)==2):
						vtmp=[(tmp[1].replace("]","")), (tmp[0])]
						try:
							cursor.execute("INSERT INTO Categories VALUES (%s,%s,%s)",(asin,vtmp[0],vtmp[1],))
						except:
							print ("Tratando excecao")
						conn.commit()

	linha = arquivo.readline()
arquivo.close()
