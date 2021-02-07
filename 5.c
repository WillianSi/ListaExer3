#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct data{
	int dia;
	int mes;
	int ano;
}tdata;

typedef struct emprestimo{
	struct data tdata;
	char nomePessoa[30];
	char emprestado[1];
}temprestimo;

typedef struct jogo{
	char titulo[30];
	char console [15];
	int ano;
	int ranking; 
	struct emprestimo temprestimo;
}tjogo;
int qtd=0;

//-------------ADICIONAR JOGO--------------

int addjogo(tjogo j[]){
	if(qtd==MAX)
	   return 0;
	printf("***** Dados para o jogo %d *****\n",qtd+1);
	fflush(stdin);
	printf("Titulo:");
	gets(j[qtd].titulo);
	printf("Tipo de console:");
	fflush(stdin);
	gets(j[qtd].console);
	printf("Ano:");
	scanf("%d",&j[qtd].ano);
	printf("Ranking:");
	scanf("%d",&j[qtd].ranking);
	printf("Date de emprestimo:");
	scanf("%d",&j[qtd].temprestimo.tdata.dia);	
	scanf("%d",&j[qtd].temprestimo.tdata.mes);
	scanf("%d",&j[qtd].temprestimo.tdata.ano);
	printf("Nome da pessoa:");
	fflush(stdin);
	gets(j[qtd].temprestimo.nomePessoa);
	printf("Emprestado S|N:");
	fflush(stdin);
	gets(j[qtd].temprestimo.emprestado);
	qtd++;
	return 1;
} 

//-------------MOSTRAR JOGOS--------------

void mostrajogo(tjogo j[]){
	int i;
	for(i=0;i<qtd;i++){
		printf("\n----------- JOGO %d ---------\n",i+1);
			printf("Titulo:%s\nTipo de console:%s\nAno:%d\nRanking:%d\n",j[i].titulo,j[i].console,j[i].ano,j[i].ranking);
			printf("Data de emprestimo:%d/%d/%d\nNome da pessoa:%s\nEmprestado S|N:%s\n",j[i].temprestimo.tdata.dia,j[i].temprestimo.tdata.mes,
			j[i].temprestimo.tdata.ano,j[i].temprestimo.nomePessoa,j[i].temprestimo.emprestado);	   
		printf("-------------------------------\n");
	}
}

//--------------BUSCAR JOGO POR NOME------------
void buscajogo(tjogo j[], char nomeBusca[]){
	int i, encontrou=0;
	char nomeJogo[30];
	for(i=0;i<qtd;i++){
		strcpy(nomeJogo, j[i].titulo);
		if(strcmp(strupr(nomeJogo) , strupr(nomeBusca) )==0){
			printf("\n----------- JOGO %d ---------\n",i+1);
			printf("Titulo:%s\nTipo de console:%s\nAno:%d\nRanking:%d\n",j[i].titulo,j[i].console,j[i].ano,j[i].ranking);
			printf("Date de emprestimo:%d/%d/%d\nNome da pessoa:%s\nEmprestado S|N:%s\n",j[i].temprestimo.tdata.dia,j[i].temprestimo.tdata.mes,
			j[i].temprestimo.tdata.ano,j[i].temprestimo.nomePessoa,j[i].temprestimo.emprestado);	   
			printf("-------------------------------\n");
			encontrou=1;
	   }
	}
	if(!encontrou)
	   printf("Jogo nao encontrado :(");
}

//--------------BUSCAR JOGO POR CONSOLE------------
void buscaConsole(tjogo j[], char nomeBusca[]){
	int i, encontrou=0;
	char nomeConsole[30];
	for(i=0;i<qtd;i++){
		strcpy(nomeConsole, j[i].console);
		if(strcmp(strupr(nomeConsole) , strupr(nomeBusca) )==0){
			printf("\n----------- JOGO %d ---------\n",i+1);
			printf("Titulo:%s\nTipo de console:%s\nAno:%d\nRanking:%d\n",j[i].titulo,j[i].console,j[i].ano,j[i].ranking);
			printf("Date de emprestimo:%d/%d/%d\nNome da pessoa:%s\nEmprestado S|N:%s\n",j[i].temprestimo.tdata.dia,j[i].temprestimo.tdata.mes,
			j[i].temprestimo.tdata.ano,j[i].temprestimo.nomePessoa,j[i].temprestimo.emprestado);	   
			printf("-------------------------------\n");
			encontrou=1;
	   }
	}
	if(!encontrou)
	   printf("Jogo nao encontrado :(");
}

//--------------REALIZAR EMPRESTIMO------------
void emprestaJogo(tjogo j[], char nomeBusca[]){
	int i, encontrou=0;
	char nomeJogo[30];
	for(i=0;i<qtd;i++){
		strcpy(nomeJogo, j[i].titulo);
		if(strcmp(strupr(nomeJogo) , strupr(nomeBusca) )==0){
			if(strcasecmp(j[i].temprestimo.emprestado,"N") == 0){
				printf("\n----------- JOGO %d ---------\n",i+1);
				printf("Data de emprestimo:");
				scanf("%d",&j[i].temprestimo.tdata.dia);	
				scanf("%d",&j[i].temprestimo.tdata.mes);
				scanf("%d",&j[i].temprestimo.tdata.ano);
				printf("Nome da pessoa:");
				fflush(stdin);
				gets(j[i].temprestimo.nomePessoa);
				printf("Emprestado S|N:");
				fflush(stdin);
				gets(j[i].temprestimo.emprestado);	   
				printf("-------------------------------\n");
			}
			else
				printf("Jogo emprestado :(");
			encontrou=1;
			break;
	   }
	}
	if(!encontrou)
	   printf("Jogo nao encontrado :(");
}
//--------------REALIZAR DEVOLUCAO------------
void devolveJogo(tjogo j[], char nomeBusca[]){
	int i, encontrou=0;
	char nomeJogo[30];
	for(i=0;i<qtd;i++){
		strcpy(nomeJogo, j[i].titulo);
		if(strcmp(strupr(nomeJogo) , strupr(nomeBusca) )==0){
			if(strcasecmp(j[i].temprestimo.emprestado,"S") == 0){
				j[i].temprestimo.emprestado[0] = 'N';
				encontrou=1;
				break;
	  		 }
		}
	}
	if(!encontrou)
	   printf("Jogo nao encontrado :(");
	else
	   printf("Jogo devolvido com sucesso");
}

//--------------BUSCAR POR JOGO EMPRESTADO------------
void buscaEmprestimo(tjogo j[]){
	int i, encontrou=0;
	for(i=0;i<qtd;i++){
		if(strcasecmp(j[i].temprestimo.emprestado,"S") == 0){
			printf("\n----------- JOGO %d ---------\n",i+1);
			printf("Titulo:%s\nTipo de console:%s\nAno:%d\nRanking:%d\n",j[i].titulo,j[i].console,j[i].ano,j[i].ranking);
			printf("Date de emprestimo:%d/%d/%d\nNome da pessoa:%s\nEmprestado S|N:%s\n",j[i].temprestimo.tdata.dia,j[i].temprestimo.tdata.mes,
			j[i].temprestimo.tdata.ano,j[i].temprestimo.nomePessoa,j[i].temprestimo.emprestado);	   
			printf("-------------------------------\n");
			encontrou=1;
	   }
	}
	if(!encontrou)
	   printf("Jogo nao encontrado aq :(");
}
//---------------SALVAR DADOS EM UM ARQUIVO BINARIO-----------
void salvaArquivoBinario(tjogo jogos[]){
	FILE *arq;
	arq=fopen("dadosDeJogos.txt","wb");
	fwrite(&jogos[0],sizeof(tjogo),qtd,arq);
	printf("Dados salvos com sucesso - binario\n");
	fclose(arq);
}
//--------------CARREGAR DADOS DO ARQUIVO EM BINARIO------------
void carregaBinario(tjogo jogos[]){
	FILE *arq;
	arq=fopen("dadosDeJogos.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado :(\n");
	  return;
	  }
	 while(fread(&jogos[qtd],sizeof(tjogo),1,arq) >0  )
	      qtd++;  
	 printf("Dados carregados com sucesso - binario !\n");
	fclose(arq);
}

//--------------MENU DE OPCOES------------
int menu(){
	int op;
	printf("*** SISTEMA DE CADASTRO DE JOGOS ****\n");
	printf("1-Inserir novo JOGO\n");
	printf("2-Mostrar todos os JOGOS\n");
	printf("3-Buscar jogo por nome\n");
	printf("4-Buscar por console\n");
	printf("5-Realizar emprestimo\n");	
	printf("6-Devolucao de emprestimo\n");	
	printf("7-Buscar por jogos emprestados\n");
	printf("0-Sair\n");
	scanf("%d",&op);
	return op;
}
//---------------------------
int main(){
	tjogo jogos[MAX];
	char nomeBusca[40];
	int op;
	float valor=0, comsumo=0;
	carregaBinario(jogos);
    do{
      op = menu();	
      switch(op){
      	case 1: addjogo(jogos);
      	break;
    	case 2: mostrajogo(jogos);
     	break;
    	case 3: printf("Titulo do jogo para buscar:");
      			fflush(stdin); gets(nomeBusca);
      			buscajogo(jogos, nomeBusca);
      	break;		
      	case 4: printf("Nome do console para buscar:");
      			fflush(stdin); gets(nomeBusca);
      			buscaConsole(jogos, nomeBusca);		
      	break;
		case 5: printf("Nome do jogo para buscar:");
      			fflush(stdin); gets(nomeBusca);
      			emprestaJogo(jogos, nomeBusca);
      	break;
      	case 6: printf("Nome do jogo para buscar:");
      			fflush(stdin); gets(nomeBusca);
      			devolveJogo(jogos, nomeBusca);
      	break;
      	case 7:	buscaEmprestimo(jogos);
      	break;
	   	case 0: salvaArquivoBinario(jogos);
		  		printf("Saindo... \n");
     	break;
	  }
      	getch(); // pausa na tela - espera digitar uma tecla
      	system("cls");
	}while(op!=0);
	return 0;
}
