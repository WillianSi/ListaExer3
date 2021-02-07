#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 40


typedef struct{
	char titulo[30], autor[10];
	int ano,prateleira;
}tLivro;
int qtd=0;

//-------------ADICIONAR LIVRO--------------

int inserir(tLivro l[]){
	if(qtd==MAX)
		return 0;
	printf("***** Cadastro de Livros %d*****\n",qtd+1);
	printf("Digite o titulo: ");
	fflush(stdin);
	gets(l[qtd].titulo);
	printf("Digite o autor: ");
	fflush(stdin);
	gets(l[qtd].autor);
	printf("Digite o Ano: ");
	scanf("%d",&l[qtd].ano);
	printf("Digite a prateleira: ");
	scanf("%d",&l[qtd].prateleira);
	qtd++;
	return 1;
}

//-------------LISTAR--------------
void listar(tLivro l[]){
	int i;
	for(i=0; i<qtd; i++){
		printf("----------- Livro %d ---------\n",i+1);
		printf("Titulo: %s\n",l[i].titulo);
		printf("Autor: %s\n",l[i].autor);
		printf("Ano: %d\n",l[i].ano);
		printf("Prateleira: %d\n",l[i].prateleira);
		printf("-------------------------------\n");
	}
}

//-------------PROCURAR POR NOME--------------
void procurarPorNome(tLivro l[], char nomeBusca[]){
	int i, encontrou=0;
	for(i=0; i<qtd; i++){
		if(strcmp(l[i].titulo,nomeBusca) == 0){
			printf("***** Livro %d *****\n",i+1);
			printf("Titulo: %s\n",l[i].titulo);
			printf("Autor: %s\n",l[i].autor);
			printf("Ano: %d\n",l[i].ano);
			printf("Prateleira: %d\n",l[i].prateleira);	
			encontrou=1;
		}
	}
	if(!encontrou)
		printf("Titulo nao emcontrado :(\n");
}

//-------------PROCURAR POR ANO--------------
void buscaAno(tLivro l[],int ano){
	int i, encontrou=0;
	for(i=0; i<qtd; i++){
		if(ano < l[i].ano){
			printf("---------- Livro %d ----------\n",i+1);
			printf("Titulo: %s\n",l[i].titulo);
			printf("Autor: %s\n",l[i].autor);
			printf("Ano: %d\n",l[i].ano);
			printf("Prateleira: %d\n",l[i].prateleira);
			printf("-------------------------------\n");
			encontrou=1;
		}
	}	
	if(!encontrou)
		printf("Nao existe livros mais novos!\n");
}

//---------------SALDADOS EM UM ARQUIVO BINARIO-----------
void salvaArquivoBinario(tLivro livros[]){
	FILE *arq;
	arq=fopen("dadosLivro.txt","wb");
	fwrite(&livros[0],sizeof(tLivro),qtd,arq);
	printf("Dados salvos com sucesso - binario\n");
	fclose(arq);
}
//--------------CARREGAR DADOS DO ARQUIVO EM BINARIO------------
void carregaBinario(tLivro livros[]){
	FILE *arq;
	arq=fopen("dadosLivro.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado :(\n");
	  return;
	  }
	 while(fread(&livros[qtd],sizeof(tLivro),1,arq) >0  )
	      qtd++;  
	 printf("Dados carregados com sucesso - binario !\n");
	fclose(arq);
}

//--------------MENU DE OPCOES------------
int menu(){
	int op;
	printf("*** Sistema de Cadastro de Livros ***\n");
	printf("1-Inserir\n");
	printf("2-Listar\n");
	printf("3-Procurar por nome\n");
	printf("4-Livro por ano mais novo\n");
	printf("0-Sair\n");
	scanf("%d",&op);
	return op;
}

int main(){
	tLivro livros[MAX];
	char nomeBus[30];
	int op,ano;
	carregaBinario(livros);
	do{
		op = menu();
		switch(op){
			case 1: inserir(livros);
			break;
			case 2: listar(livros);
			break;
			case 3: printf("Digite o nome para buscar:\n");
					fflush(stdin);
					gets(nomeBus);
					procurarPorNome(livros,nomeBus);
			break;
			case 4: printf("Digite o ano: ");
					scanf("%d",&ano);
					buscaAno(livros, ano);
			break;	
			case 0: salvaArquivoBinario(livros);
		  			printf("Saindo... \n");
      		break;
			default: printf("Opcao invalida");
		}
		printf("Pressione qualquer tecla para sair...\n");
		getch();
		system("cls");
	}while(op != 0);
	return 0;
}
