//livrarias
#include <stdio.h> // printf, scanf
#include <stdlib.h> //funcao padrao
#include <string.h> //estruturas
#include <locale.h>  // acentos
#include <Windows.h> //Windows
#include <conio.h>
#include <time.h> //cronologia das publica��es

//settings
#define tamNome 30 //tamanho do Nome
#define tamNick 20 //tamanho do Nickname
#define tamEmail 79 //tamanho do Email
#define tamPass 30 //tamanho da Password
#define tamData 20 //tamanho das Datas
#define tamConteudo 150 //Numero maximo de caracteres numa Publicacao
#define nrMAX_UTL 200 //Numero maximo de Utilizadores
#define tamUTLLista 100 //Tamanho do  arrat que contem a  Lista dos Utilizadores
#define tamPubliList 500 //Tamanho do  arrat que contem a  Lista dos Utilizadores


//structs

typedef struct dados{	//Estrutura com dados do Utilizador
	char nome [tamNome];
	char nickname[tamNick];
	char email[tamEmail];
	char password1[tamPass];
	char password2[tamPass];
	char dataNascimento [tamData]; 	
} Utilizador; 

typedef struct post {		//Estrutura com todos os parametros de uma Publica��o
	char conteudo[tamConteudo];
	char nickname[tamNick];
	char data[tamData];
	int tipo, id;
} Publicacao;

//Fun��es Utilizadas
void titulo();
void gravarDados();
void gravarPublicacao();
void buscarDaddos();
void buscarPublicacao();
void criarPublicacao();
void listarPrivadas();
void listarPublicas();
void editarDados();
void cadastrar();
void Login();
void anonimo();
int main();

void titulo(){			//interface da aplica��o
	puts(" _______  _______  _______  ______     _______  ___      _______  _     _ ");
	puts("|       ||       ||       ||      |   |       ||   |    |       || | _ | |");
	puts("|    ___||    ___||    ___||  _    |  |    ___||   |    |   _   || || || |");
	puts("|   |___ |   |___ |   |___ | | |   |  |   | __ |   |    |  | |  ||       |");
	puts("|    ___||    ___||    ___|| |_|   |  |   ||  ||   |___ |  |_|  ||       |");
	puts("|   |    |   |___ |   |___ |       |  |   |_| ||       ||       ||   _   |");
	puts("|___|    |_______||_______||______|   |_______||_______||_______||__| |__|");
	puts("");
	puts("");
	
}

//grava��o
void gravarDados(Utilizador lista[], int nrUTL) {
	FILE *fich;												//declara��o do ficheiro
	fich = fopen("Utilizadores.data","wb");					//abertura do ficheiro
	fwrite(&nrUTL, sizeof(int), 1, fich);					//escrver no ficheiro o numero de utilizador
	fwrite(lista, sizeof(Utilizador), nrUTL, fich);			//escrever no ficheiro todos os dados do utilizador
	fclose(fich);											//fechar ficheiro
}

void gravarPublicacao(Publicacao list[], int nrPubli){		
	FILE *file;												//declara��o do ficheiro
	file = fopen("Publicacoes.data","wb");   				//abertura do ficheiro
	fwrite(&nrPubli, sizeof(int), 1, file);					//escrever no ficheiro o numero da Publica��o
	fwrite(list, sizeof(Publicacao), nrPubli, file);		//escrever no ficheiro todos os parametros da Publica��o
	fclose(file);											//fechar ficheiro
}

//buscar

void buscarDados(Utilizador lista[], int *nrUTL){
	FILE *fich; 											//declara��o do ficheiro
	int t; 													//guarda o tamanho em bytes do arquivo
	int n; 													//guarda o numero de elementos lidos com sucesso
	fich= fopen("Utilizadores.data","rb");					//abertura do ficheiro
	if(fich == NULL) {										//certifica��o que o ficheiro abriu corretamente
		printf("Nao foi possivel abrir arquivo\n");
		*nrUTL = 0;
	}
	else {
		n = fread(&t, sizeof(int), 1, fich);				//leitura do numero de Utilizador
		fread(lista, sizeof(Utilizador), t, fich);			//leirura de todos os dados do Utilizador
		*nrUTL = t;
	}
	fclose(fich);
} 

void buscarPublicacoes(Publicacao list[], int *nrPubli){
	FILE *file;
	int t; 
	int n;
	file = fopen("Publicacoes.data","rb");
	if(file == NULL) {
		printf("Nao foi possivel abrir arquivo!\n");
		*nrPubli = 0;
	}
	else {
		n = fread(&t, sizeof(int), 1, file);				//leitura do numero de Publica��o		
		fread(list, sizeof(Publicacao), t, file);			//leitura de todos os parametros da Publica��o
		*nrPubli = t;
	}
	fclose(file);
}

//Cria��o e visualiza��o de Publica��es

void criarPublicacao(Publicacao list[], int *nrPubli, Utilizador *paux){
	getchar();												//scanf para caracteres
	strcpy(list[*nrPubli].nickname, (*paux).nickname);		//copiar a string nickname da struct para a lista de Utilizadores
	
	printf("Insira a data de hoje:\n");
	fgets (list[*nrPubli].data, tamData, stdin);            //stdin para ler caracteres introduzidos pelo teclado
	printf("Em que esta a pensar %s : ", list[*nrPubli].nickname);
	fgets(list[*nrPubli].conteudo, tamConteudo, stdin);
	printf("Que tipo de publica��o pretende:\n"); 
	printf("1- Publico\n");
	printf("2- Privado\n");
	scanf("%d",&list[*nrPubli].tipo);
	getchar();
	list[*nrPubli].id = *nrPubli; 							//definir o iD como o numero de Publica��es
	(*nrPubli)++;  											//Adicionar 1 ao numero de Publica��es
}

void listarPrivadas(Publicacao list[], int *nrPubli){
int i;
	if(*nrPubli == 0) {						
		printf("Nao existem publicacoes, tente novamente mais tarde...\n");		//verificar se j� existem publica��es privadas
	}
	else{
		for(i = 0; i<*nrPubli; i++) {					//loop para listar todas as publica��es privadas
			if(list[i].tipo==1 || list[i].tipo==2 ){		//Mostrar publica��es privadas e publicas
				printf("Nickname: %s\n", list[i].nickname); 
				printf("Data: %s",list[i].data);
				printf ("%s:",list[i].conteudo);
				printf ("iD:%d\n", list[i].id);
				printf("-------------------\n");
			}
		}
	}
}

void listarPublicas(Publicacao list[], int *nrPubli){
int i;
int nPublicas=0;												//numero de publica��es p�blicas
	if(*nrPubli == 0) {
		printf("Ainda n�o foram criadas publica��es!\n");		//verifica��o de se ja existem publica��es p�blicas
	}
	else{
		for(i = 0; i<*nrPubli; i++) {							//loop para listar todas as publica��es publicas
			if(list[i].tipo==1){								//condi��o para apenas listar publica��es p�blicas
				printf ("\nNickname:%s", list[i].nickname);
				printf ("Data: %s", list[i].data);
				printf ("%s", list[i].conteudo);
				printf ("iD:%d \n", list[i].id);
				printf ("--------------------\n");
				nPublicas++;									
			}
		}
	}
	if(nPublicas==0){
		printf("Nao existem publicacoes p�blicas, crie uma conta e divirta-se na feed glow!\n");
	}
}


//Edi��o de Dados
void editarDados(Utilizador lista[], int *ploc, Utilizador *paux) { 
	int opcao;
	do {
		system("cls");
		titulo();
		printf("\n");
		printf("Edi��o de Dados Pessoais\n");
		printf("Nickname*: %s\n", paux->nickname);
		printf("1 -Nome\n");
		printf("2 -Email\n");
		printf("3 -Password\n");
		printf("4 -Data de Nascimento\n");
		printf("0 -Voltar\n");
		
		scanf("%d", &opcao);
		
		switch(opcao) {				//switch case para escolher o dado que deseja editar
			case 1:
				getchar();
				printf("Indique o nome: ");
				fgets(lista[*ploc].nome, tamNome, stdin);		//usamos a variavel loc para determinar a posi��o do dado
				break;
				
			case 2:
				getchar();
				printf("Indique o email novo: ");
				fgets(lista[*ploc].email, tamEmail, stdin);
				break;
			
			case 3:
				getchar();
				printf("Indique a password nova: ");
				fgets(lista[*ploc].password1, tamPass, stdin);
				break;
		
			case 4:
				getchar();
				printf("Indique a data nova: ");
				fgets(lista[*ploc].dataNascimento, tamData, stdin);
				break;
			
			case 0:
				break;
			
			default:
				printf("Opcao invalida!\n");
		}
	} while(opcao != 0);
}

//LOGIN E CADASTRO

void cadastrar(Utilizador lista[], int *nrUTL){
	Utilizador aux;										//struct Utilizador
	int i;
	
	if(*nrUTL > nrMAX_UTL)								//limite de utilizadores na Aplica��o
		printf("Limite de Utilizadores Atingido!\n");
	else{
	
	getchar();
	printf("Escolha um nickname: ");
	fgets(aux.nickname, tamNick, stdin);
	printf("Insira o seu nome: ");
	fgets (aux.nome, tamNome, stdin);
	printf ("Insira o seu email: ");
	fgets (aux.email, tamEmail, stdin);
		do{												//loop para a obrigatoriadade de confirmar a password
		printf("Escolha a sua password: ");
		fgets (aux.password1, tamPass, stdin);
		printf("Confirme a password: ");
		fgets(aux.password2, tamPass, stdin);
		}while(strcmp(aux.password1, aux.password2)!=0);
	}
	printf ("Insira a sua data de Nascimento: ");
	fgets (aux.dataNascimento, tamData, stdin);
	
	lista[*nrUTL] = aux;							//adicionar dados da struct para lista de Utilizadores 
	(*nrUTL)++;		
}

void Login (Utilizador lista[], Publicacao list[], int nrUTL, int *nrPubli, int *loc){
	Utilizador aux;
	Utilizador *paux = &aux;					//mostrar o valor apontado pelo paux
	int i;
	int option;
	
	titulo();
	getchar();
	printf ("Nickname: ");
	fgets (aux.nickname, tamNick, stdin);
	printf ("Password: ");
	fgets (aux.password1, tamPass, stdin);
	
	for (i=0; i<nrUTL; i++){
		if(strcmp(aux.nickname,lista[i].nickname) == 0 && strcmp(aux.password1,lista[i].password1) == 0 ){		//verificar se o Utilizador esta presente nos ficheiros
			printf("Login Efetudo com sucesso\n");
			system("pause");
			(*loc)=i;					//o contador vai ser igual � posicao de cada dado
				do{
					system ("cls");
					titulo ();
					printf ("\n");
					printf ("-------------------------MENU--------------------------\n");
					printf ("\n");
					printf ("Selecione a op��o pretendida:\n");
					printf ("\n");
					printf ("1-FEED\n");
					printf ("2-Criar Publicacao\n");
					printf ("3-Editar dados pessoais\n");
					printf ("0-Logout\n");
					
					scanf("%d",&option);
					
					switch (option){
						case 1:
							system ("cls");
							titulo();
							listarPrivadas(list, nrPubli);
							system("pause");
						break;
						
						case 2:
							system ("cls");
							titulo();
							criarPublicacao(list, nrPubli, paux);
						break;
						
						case 3:
							editarDados(lista, loc, paux);
						break;
						
						case 0:
						break;
						
						default:
							printf ("Opc�o inv�lida, por favor tente novamente...\n");
							system ("pause");
						break;
					}
			}while(option!=0);
			
		}
		
	}
}

void anonimo(Publicacao list[], int nrPubli){
	printf("Bem-vindo ao modo An�nimo, aqui apenas poder� visualizar publica��es p�blicas\n");
	listarPublicas(list, &nrPubli);
	system ("pause");
}

int main(){
	Utilizador lista[tamUTLLista];
	Publicacao list[tamPubliList];
	int loc=0;		
	int opcao=0;
	int nrUTL=0; 
	int nrPubli=0;
	
	setlocale(LC_ALL, ("Portuguese")); //Introduzir Acentos
	
	buscarDados(lista, &nrUTL);
	buscarPublicacoes(list, &nrPubli);
	
	do{
		system ("cls");
		titulo ();
		printf("\n");
		printf ("---------------------BEM-VINDO-----------------------");
		printf("\n");
		printf("\n");
		
		printf("Digite a op��o pretendida:\n");
		printf("\n");
		
		printf("1-Iniciar Sess�o\n");
		printf("2-Criar Conta\n");
		printf("3-Modo An�nimo\n");
		printf("4-Informa��es Estat�sticas\n");
		printf("0-Sair\n");
		
		scanf("%d",&opcao);
		
		switch(opcao){
			case 1:
				system ("cls");
				Login(lista, list, nrUTL, &nrPubli, &loc);
			break;
			
			case 2:
				system ("cls");
				titulo();
				cadastrar(lista, &nrUTL);
			break;
			
			case 3:
				system ("cls");
				titulo();
				anonimo(list, nrPubli);
			break;
			
			case 4:
				system ("cls");
				titulo();
				printf("Informa��o estat�stica:\n");
				printf("Numero de contas criadas na aplica��o: %d\n",nrUTL);
				printf("Numero de publica��es ja criadas: %d\n",nrPubli);
				system ("pause");
			break;
			
			case 0:
			gravarDados(lista, nrUTL);
			gravarPublicacao(list, nrPubli);
			printf("AT� � PROXIMA\n");
			exit(0);
			break;
			
			default:
				printf ("Opc�o inv�lida, tente novamente...\n");
				system ("pause");
			break;
		}		
	}while(opcao!=0);
}
