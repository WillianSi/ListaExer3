#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct nasc{
	int mes;
	int ano;
}tnasc;

typedef struct gado{
	char codigo[50];
	float leite;
	float alim;
	struct nasc tnasc;
	char abate[1];	
}tgado;

int anoAtual=2021;
int qtd=0;

//-------------ADICIONAR ANIMAL--------------

int addgado(tgado g[]){
	if(qtd==MAX)
	   return 0;
	printf("***** Dados para o animal %d *****\n",qtd+1);
	printf("Codigo da cabeca:");
	fflush(stdin);
	gets(g[qtd].codigo);
	printf("Numero de litros de leite produzido por semana:");
	scanf("%f",&g[qtd].leite);
	printf("Quantidade de alimento ingerida por semana Kg:");
	scanf("%f",&g[qtd].alim);
	printf("Data de nascimento - mes e ano:");
	scanf("%d",&g[qtd].tnasc.mes);scanf("%d",&g[qtd].tnasc.ano);

	int idade = anoAtual - g[qtd].tnasc.ano;
	if(g[qtd].leite < 40 || idade > 5)
		g[qtd].abate[0] = 'S';
	else
		g[qtd].abate[0] = 'N';
	printf("Abate N (nao) ou S (sim):%s",g[qtd].abate);
	qtd++;
	return 1;
} 

//-------------MOSTRAR GADO--------------
void mostraGado(tgado g[]){
	int i;
	for(i=0;i<qtd;i++){
		printf("\n----------- Animal %d ---------\n",i+1);	
			printf("Codigo da cabeca:%s\nNumero de litros de leite produzido por semana:%.2f\n",g[i].codigo,g[i].leite);
			printf("Quantidade de alimento ingerida por semana Kg:%.2f\nData de nascimento - mes e ano:%d | %d\nAbate N (nao) ou S (sim):%s\n",
			g[i].alim,g[i].tnasc.mes,g[i].tnasc.ano,g[i].abate);
		printf("-------------------------------\n");
	}
}

//--------------PRODUCAO TOTAL DE LEITE------------
void pruducaoTotal(tgado g[]){
	int i;
	float total=0;
	for(i=0;i<qtd;i++){
		total += g[i].leite;
	   }
	   printf("Producao total de leite: %.2fL",total);
}

//--------------COMSUMO DE ALIMENTO------------
void pruducaoTotalAli(tgado g[]){
	int i;
	float total=0;
	for(i=0;i<qtd;i++){
		total += g[i].alim;
	   }
	   printf("Producao total de alimento: %.2fKg",total);
}

//--------------BUSCAR GADO PARA O ABATE------------
void buscaAbate(tgado g[]){
	int i, encontrou=0;
	for(i=0;i<qtd;i++){		
		if(strcasecmp(g[i].abate,"S") == 0){
			printf("\n----------- Animal %d ---------\n",i+1);
			printf("Codigo da cabeca:%s\n",g[i].codigo);
		encontrou=1;
		}
	}	   
	if(!encontrou)
	   printf("Nao existe gado para o abate :)");
}

//---------------SALVAR DADOS EM UM ARQUIVO BINARIO-----------
void salvaArquivoBinario(tgado gados[]){
	FILE *arq;
	arq=fopen("dadosDeGados.txt","wb");
	fwrite(&gados[0],sizeof(tgado),qtd,arq);
	printf("Dados salvos com sucesso - binario\n");
	fclose(arq);
}

//--------------CARREGAR DADOS DO ARQUIVO EM BINARIO------------
void carregaBinario(tgado gados[]){
	FILE *arq;
	arq=fopen("dadosDeGados.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado :(\n");
	  return;
	  }
	 while(fread(&gados[qtd],sizeof(tgado),1,arq) >0  )
	      qtd++;  
	 printf("Dados carregados com sucesso - binario !\n");
	fclose(arq);
}

//--------------MENU DE OPCOES------------
int menu(){
	int op;
	printf("*** SISTEMA DE CADASTRO DE GADO ****\n");
	printf("1-Inserir novo animal\n");
	printf("2-Mostrar todos os animais\n");
	printf("3-Total de leite produzido por semana\n");
	printf("4-Total de alimento consumido por semana\n");
	printf("5-Animais que devem ir para o abate.\n");	
	printf("0-Sair\n");
	scanf("%d",&op);
	return op;
}
//---------------------------
int main(){
	tgado gados[MAX];
	char nomeBusca[40];
	int op;
	float valor=0, comsumo=0;
	carregaBinario(gados);
    do{
      op = menu();	
      switch(op){
      	case 1: addgado(gados);
      	break;
    	case 2: mostraGado(gados);
     	break;
    	case 3: pruducaoTotal(gados);
      	break;		
      	case 4: pruducaoTotalAli(gados);	
      	break;
		case 5: buscaAbate(gados);
      	break;
	   	case 0: salvaArquivoBinario(gados);
		  		printf("Saindo... \n");
     	break;
	  }
      	getch(); // pausa na tela - espera digitar uma tecla
      	system("cls");
	}while(op!=0);
	return 0;
}
