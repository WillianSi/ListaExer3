#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct banda{
	char nome[40];
	char genero[40];
	int integrantes;
	int ranking;
}tbanda;
int qtd=0;

//-------------ADICIONAR BANDAS--------------

int addBanda(tbanda b[]){
	if(qtd==MAX)
	   return 0;
	printf("***** Dados para banda %d *****\n",qtd+1);
	fflush(stdin);
	printf("Nome:");
	gets(b[qtd].nome);
	fflush(stdin);
	printf("Genero:");
	gets(b[qtd].genero);
	printf("Integrantes:");
	scanf("%d",&b[qtd].integrantes);
	printf("Ranking:");
	scanf("%d",&b[qtd].ranking);
	qtd++;
	return 1;
} 

//-------------MOSTRAR BANDAS--------------

void mostraBandas(tbanda b[]){
	int i;
	for(i=0;i<qtd;i++){
		printf("\n----------- Banda %d ---------\n",i+1);
		printf("Nome:%s\nGenero:%s\nIntegrantes:%d\nRanking:%d\n",
		       b[i].nome, b[i].genero,b[i].integrantes, b[i].ranking);
		printf("-------------------------------\n");
	}
}

//--------------BUSCAR BANDAS POR NOME------------
void buscaBanda(tbanda b[], char nomeBusca[]){
	int i, encontrou=0;
	char nomeBanda[40];
	for(i=0;i<qtd;i++){
		strcpy(nomeBanda, b[i].nome);
		if(strcmp(strupr(nomeBanda) , strupr(nomeBusca) )==0){
		printf("\n----------- Banda %d ---------\n",i+1);
		printf("Nome:%s\nGenero:%s\nIntegrantes:%d\nRanking:%d\n",
		       b[i].nome, b[i].genero,b[i].integrantes, b[i].ranking);
		printf("-------------------------------\n");
		encontrou=1;
		break;
	   }
	}
	if(!encontrou)
	   printf("Banda nao encontrada :(");
}

//-------------BANDA FAVORITA-------------
void favoritas(tbanda b[]){
	int i, cont=0;
	for(i=0; i<qtd; i++){
		if(b[i].ranking >=1 && b[i].ranking <=3){
			printf("Nome:%s\nGenero:%s\nIntegrantes:%d\nRanking:%d\n", b[i].nome, b[i].genero,b[i].integrantes, b[i].ranking);
		printf("-------------------------------\n");
		cont++;
		}
	}
	printf("Existem %d banda(s) favoritas\n",cont);
}

//-------------REMOVER BANDA-------------
void removeBanda(tbanda b[], char nomeBusca[]){
	int i, encontrou=0, res;
	char nomeBanda[40];
	for(i=0;i<qtd;i++){
		strcpy(nomeBanda, b[i].nome);
		if(strcmp(strupr(nomeBanda) , strupr(nomeBusca) )==0){
		  printf("Tem certeza que deseja excluir da banda %s? [1- Sim 2- Nao]\n",b[i].nome);
		  scanf("%d",&res);
		  if(res==1){
		  	b[i] = b[qtd-1];
		  	qtd--;
		  }
		encontrou=1;   
		break;
	   }
	}
	if(!encontrou)
	   printf("Banda nao encontrada :(\n");
	else
	  printf("Banda removida com sucesso!\n");   
}

//--------------ALTERAR BANDA------------
void alteraBanda(tbanda b[], char nomeBusca[]){
	int i, encontrou=0;
	char nomeBanda[40];
	for(i=0;i<qtd;i++){
		strcpy(nomeBanda, b[i].nome);
		if(strcmp(strupr(nomeBanda) , strupr(nomeBusca) )==0){
		    printf("*** Novos dados para banda %s ***\n", b[i].nome);
			printf("Novo Nome[%s]:",b[i].nome);
			fflush(stdin); 
			gets(b[i].nome);
			printf("Novos Integrantes[%d]:",b[i].integrantes);
			scanf("%d",&b[i].integrantes);
			printf("Novo Genero[%s]:",b[i].genero);
			fflush(stdin);
			gets(b[i].genero);
			printf("Novo Ranking[%d]:",b[i].ranking);
			scanf("%d",&b[i].ranking);
		encontrou=1;	
		break;
	   }
	}
	if(!encontrou)
	   printf("Banda nao encontrada :(");
	else
	   printf("Dados alterados com sucesso");
}
//--------------BUSCAR BANDAS POR RANKING------------
void buscaRanking(tbanda b[], int rank){
	int i, cont=0;
	for(i=0; i<qtd; i++){
		if(b[i].ranking == rank){
			printf("Nome:%s\nGenero:%s\nIntegrantes:%d\nRanking:%d\n",
		     b[i].nome, b[i].genero,b[i].integrantes, b[i].ranking);
		printf("-------------------------------\n");
		cont++;
		}
	}
	printf("Existem %d banda(s) neste ranking\n",cont);
}

//---------------SALVAR DADOS EM UM ARQUIVO-----------
void salvarDados(tbanda b[]){
	int i;
	FILE *arq;
	arq = fopen("bandas.txt","w");
	fprintf(arq,"%d\n",qtd);
	for(i=0;i<qtd;i++){
		fprintf(arq,"%s\n",b[i].nome);
		fprintf(arq,"%s\n",b[i].genero);
		fprintf(arq,"%d\n",b[i].integrantes);
		fprintf(arq,"%d\n",b[i].ranking);
	}
	printf("Dados salvos com sucesso :)\n");
}
//--------------CARREGAR DADOS DO ARQUIVO------------
void carregaDados(tbanda b[]){
	FILE *arq;
	int i;
	arq = fopen("bandas.txt","r");
	if(arq==NULL){
		printf("Arquivo nao foi encontrado :(\n");
		return;
	}
	fscanf(arq,"%d",&qtd);
	for(i=0;i<qtd;i++){
		fscanf(arq,"%s",&b[i].nome);
		fscanf(arq,"%s",&b[i].genero);
		fscanf(arq,"%d",&b[i].integrantes);
		fscanf(arq,"%d",&b[i].ranking);
	}
	fclose(arq);
	printf("Dados carregados com sucesso :)\n");
}
//---------------SALDADOS EM UM ARQUIVO BINARIO-----------
void salvaArquivoBinario(tbanda bandas[]){
	FILE *arq;
	arq=fopen("dadosBinario.txt","wb");
	fwrite(&bandas[0],sizeof(tbanda),qtd,arq);
	printf("Dados salvos com sucesso - binario\n");
	fclose(arq);
}
//--------------CARREGAR DADOS DO ARQUIVO EM BINARIO------------
void carregaBinario(tbanda bandas[]){
	FILE *arq;
	arq=fopen("dadosBinario.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado :(\n");
	  return;
	  }
	 while(fread(&bandas[qtd],sizeof(tbanda),1,arq) >0  )
	      qtd++;  
	 printf("Dados carregados com sucesso - binario !\n");
	fclose(arq);
}
//--------------MENU DE OPCOES------------
int menu(){
	int op;
	printf("*** SISTEMA DE CADASTRO DE BANDAS MUSIC.YOU ****\n");
	printf("1-Inserir nova banda\n");
	printf("2-Mostrar todas bandas\n");
	printf("3-Buscar banda por nome\n");
	printf("4-Buscar banda ranking\n");
	printf("5-Favoritas\n");	
	printf("6-Remover banda\n");
	printf("7-Alterar banda\n");
	printf("0-Sair\n");
	scanf("%d",&op);
	return op;
}
//---------------------------
int main(){
	tbanda bandas[MAX];
	char nomeBusca[40];
	int op, rank;
	carregaBinario(bandas);
    do{
      op = menu();	
      switch(op){
      	case 1: addBanda(bandas);
      	break;
      	case 2: mostraBandas(bandas);
      	break;
      	case 3: printf("Nome da banda para buscar:");
      			fflush(stdin); gets(nomeBusca);
      			buscaBanda(bandas, nomeBusca);
      	break;		
      	case 4: printf("Ranking para busca:");
      			scanf("%d",&rank);
      			buscaRanking(bandas, rank);		
      	break;
		case 5: favoritas(bandas);
      	break;
      	case 6: printf("Nome da banda para remover:");
      			fflush(stdin); gets(nomeBusca);
      			removeBanda(bandas, nomeBusca);
      	break;
      	case 7: printf("Nome da banda para alterar:");
      			fflush(stdin); gets(nomeBusca);
      			alteraBanda(bandas, nomeBusca);
      	break;
      	case 0: salvaArquivoBinario(bandas);
		  		printf("Saindo... \n");
      	break;
	  }
      	getch(); // pausa na tela - espera digitar uma tecla
      	system("cls");
	}while(op!=0);
	return 0;
}
