#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct eletrodomestico{
	char nome[50];
	float potencia;
	float tempo; 
}teletrodomestico;
int qtd=0;

//-------------ADICIONAR ELETRODOMESTICO--------------
int addEletrodomestico(teletrodomestico e[]){
	if(qtd==MAX)
	   return 0;
	printf("***** Dados para o eletrodomestico %d *****\n",qtd+1);
	fflush(stdin);
	printf("Nome:");
	gets(e[qtd].nome);
	printf("Potencia em kW:");
	scanf("%f",&e[qtd].potencia);
	printf("Tempo ativo por dia em horas:");
	scanf("%f",&e[qtd].tempo);
	qtd++;
	return 1;
} 

//-------------MOSTRAR ELETRODOMESTICOS--------------
void mostraeletrodomestico(teletrodomestico e[]){
	int i;
	for(i=0;i<qtd;i++){
		printf("\n----------- Eletrodomestico %d ---------\n",i+1);
		    printf("Nome: %s\nPotencia em kW:%.2lf\nTempo ativo por dia em horas:%.2lf\n",
			e[i].nome, e[i].potencia, e[i].tempo);
		printf("-------------------------------\n");
	}
}

//--------------BUSCAR ELETRODOMESTICO POR NOME------------
void buscaeletrodomestico(teletrodomestico e[], char nomeBusca[]){
	int i, encontrou=0;
	char nomeEletrodomestico[40];
	for(i=0;i<qtd;i++){
		strcpy(nomeEletrodomestico, e[i].nome);
		if(strcmp(strupr(nomeEletrodomestico) , strupr(nomeBusca) )==0){
			printf("\n----------- Eletrodomestico %d ---------\n",i+1);
		    printf("Nome: %s\nPotencia em kW:%.2lf\nTempo ativo por dia em horas:%.2lf\n",
			e[i].nome, e[i].potencia, e[i].tempo);
			printf("-------------------------------\n");
			encontrou=1;
			break;
	   }
	}
	if(!encontrou)
	   printf("Eletrodomestico nao encontrado :(");
}

//--------------BUSCAR ELETRODOMESTICO POR COMSUMO------------
void buscaComsumo(teletrodomestico e[], float comsumo){
	int i, encontrou=0;
	for(i=0; i<qtd; i++){
		if(e[i].potencia >= comsumo){
			printf("\n----------- Eletrodomestico %d ---------\n",i+1);
		    printf("Nome: %s\nPotencia em kW:%.2lf\nTempo ativo por dia em horas:%.2lf\n",
			e[i].nome, e[i].potencia, e[i].tempo);
			printf("-------------------------------\n");
		encontrou=1;
	   }
	}
	if(!encontrou)
	   printf("Eletrodomestico nao encontrado :(");
}

//--------------BUSCAR ELETRODOMESTICO POR COMSUMO------------
void calculoValor(teletrodomestico e[], float valor){
	int i;
	float consumo,diarioKw,diarioRs, mesKw, mesRs;
	for(i=0;i<qtd;i++){
		consumo=e[i].potencia*e[i].tempo;
		diarioKw += consumo;
	}
	diarioRs = (diarioKw / 1000) * valor;
	mesKw = diarioKw * 30;
	mesRs = (mesKw / 1000) * valor;
	printf("Consumo diario da casa\nkW = %.2f\nRS = %.2f\n\nConsumo mensal da casa\nkW = %.2f\nRS = %.2f", diarioKw,diarioRs, mesKw, mesRs);
}

//---------------SALVAR DADOS EM UM ARQUIVO BINARIO-----------
void salvaArquivoBinario(teletrodomestico eletrodomesticos[]){
	FILE *arq;
	arq=fopen("dadosEletrodomestico.txt","wb");
	fwrite(&eletrodomesticos[0],sizeof(teletrodomestico),qtd,arq);
	printf("Dados salvos com sucesso - binario\n");
	fclose(arq);
}
//--------------CARREGAR DADOS DO ARQUIVO EM BINARIO------------
void carregaBinario(teletrodomestico eletrodomesticos[]){
	FILE *arq;
	arq=fopen("dadosEletrodomestico.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado :(\n");
	  return;
	}
	 while(fread(&eletrodomesticos[qtd],sizeof(teletrodomestico),1,arq) >0  )
	      qtd++;  
	 printf("Dados carregados com sucesso - binario !\n");
	fclose(arq);
}
//--------------MENU DE OPCOES------------
int menu(){
	int op;
	printf("*** SISTEMA DE CADASTRO DE ELETRODOMESTICO ****\n");
	printf("1-Inserir novo eletrodomestico\n");
	printf("2-Mostrar todos os eletrodomesticos\n");
	printf("3-Buscar eletrodomestico por nome\n");
	printf("4-Buscar por eletrodomesticos que gastam mais de certo valor\n");
	printf("5-Consumo diario e mensal da casa em kW e RS.\n");	
	printf("0-Sair\n");
	scanf("%d",&op);
	return op;
}
//---------------------------
int main(){
	teletrodomestico eletrodomesticos[MAX];
	char nomeBusca[40];
	int op;
	float valor=0, comsumo=0;
	carregaBinario(eletrodomesticos);
    do{
      op = menu();	
      switch(op){
      	case 1: addEletrodomestico(eletrodomesticos);
      	break;
    	case 2: mostraeletrodomestico(eletrodomesticos);
     	break;
    	case 3: printf("Nome do eletrodomestico para buscar:");
      			fflush(stdin); gets(nomeBusca);
      			buscaeletrodomestico(eletrodomesticos, nomeBusca);
      	break;		
      	case 4: printf("Determinar valor em Kw:");
      			scanf("%f",&comsumo);
      			buscaComsumo(eletrodomesticos, comsumo);		
      	break;
		case 5: printf("Dar o valor do Kw em RS:");
      			scanf("%f",&valor);
      			calculoValor(eletrodomesticos, valor);
      	break;
	   	case 0: salvaArquivoBinario(eletrodomesticos);
		  		printf("Saindo... \n");
     	break;
	  }
      	getch(); // pausa na tela - espera digitar uma tecla
      	system("cls");
	}while(op!=0);
	return 0;
}
