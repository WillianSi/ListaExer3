#include <stdio.h>
#include <string.h>
#define MAX 100

typedef struct aluno{
	char nome[50];
	int matricula;
	float prova1;
	float prova2; 
	float prova3;
}taluno;
int qtd=0;

//-------------ADICIONAR ALUNO--------------
int addAluno(taluno a[]){
	if(qtd==MAX)
	   return 0;
	printf("***** Dados para aluno %d *****\n",qtd+1);
	fflush(stdin);
	printf("Nome:");
	gets(a[qtd].nome);
	printf("N matricula:");
	scanf("%d",&a[qtd].matricula);
	printf("Nota 1 prova:");
	scanf("%f",&a[qtd].prova1);
	printf("Nota 2 prova:");
	scanf("%f",&a[qtd].prova2);
	printf("Nota 3 prova:");
	scanf("%f",&a[qtd].prova3);
	qtd++;
	return 1;
} 

//-------------MOSTRAR ALUNOS--------------
void mostraAluno(taluno a[]){
	int i;
	for(i=0;i<qtd;i++){
		printf("\n----------- Aluno %d ---------\n",i+1);
		printf("Nome: %s\nN matricula:%d\nNota 1 prova:%.2lf\nNota 2 prova:%.2lf\nNota 3 prova:%.2lf\n",
		a[i].nome, a[i].matricula, a[i].prova1, a[i].prova2, a[i].prova3);
		printf("-------------------------------\n");
	}
}

//--------------BUSCAR ALUNoS POR NOME------------
void buscaAluno(taluno a[], char nomeBusca[]){
	int i, encontrou=0;
	char nomeAluno[40];
	for(i=0;i<qtd;i++){
		strcpy(nomeAluno, a[i].nome);
		if(strcmp(strupr(nomeAluno) , strupr(nomeBusca) )==0){
		printf("\n----------- Aluno %d ---------\n",i+1);
		printf("Nome: %s\nN matricula:%d\nNota 1 prova:%.2lf\nNota 2 prova:%.2lf\nNota 3 prova:%.2lf\n",
		a[i].nome, a[i].matricula, a[i].prova1, a[i].prova2, a[i].prova3);
		printf("-------------------------------\n");
		encontrou=1;
		break;
	   }
	}
	if(!encontrou)
	   printf("Aluno nao encontrado :(");
}

//--------------BUSCAR ALUNO POR N DA MATRICULA------------
void buscaMatricula(taluno a[], int matri){
	int i, encontrou=0;
	for(i=0; i<qtd; i++){
		if(a[i].matricula == matri){
			printf("\n----------- Aluno %d ---------\n",i+1);
			printf("Nome: %s\nN matricula:%d\nNota 1 prova:%.2lf\nNota 2 prova:%.2lf\nNota 3 prova:%.2lf\n",
			a[i].nome, a[i].matricula, a[i].prova1, a[i].prova2, a[i].prova3);
			printf("-------------------------------\n");
		encontrou=1;
		break;
	   }
	}
	if(!encontrou)
	   printf("Aluno nao encontrado :(");
}

//----------------------Aluno com maior media geral--------------------------
void mediamaior(taluno a[]){
	int i;
	float maior=0,resultado,media;
	for(i=0;i<qtd;i++){
		resultado = a[i].prova1 + a[i].prova2 + a[i].prova3;
		media = resultado / 3;
		if(maior < media){
		maior = media;	
		}	
	}
	printf("\n----------- Aluno %d tem a maior media geral---------\n",i);
	printf("Nome: %s\nN matricula:%d\nNota 1 prova:%.2lf\nNota 2 prova:%.2lf\nNota 3 prova:%.2lf\nMedia:%.2lf\n",
	a[i-1].nome, a[i-1].matricula, a[i-1].prova1, a[i-1].prova2, a[i-1].prova3,maior);
	printf("-------------------------------\n");
}

//----------------------SITUACAO DO ALUNO--------------------------
void mediaAluno(taluno a[]){
	int i;
	float resultado,media;
	for(i=0;i<qtd;i++){
		resultado = a[i].prova1 + a[i].prova2 + a[i].prova3;
		media = resultado / 3;
		if(media > 6){
			printf("\n----------- Aluno %d ---------\n",i+1);
			printf("Nome: %s\nN matricula:%d\nNota 1 prova:%.2lf\nNota 2 prova:%.2lf\nNota 3 prova:%.2lf\n",
			a[i].nome, a[i].matricula, a[i].prova1, a[i].prova2, a[i].prova3);
			printf("\nAPROVADO COM NOTA %.2lf :)\n",media);
			printf("-------------------------------\n");
		}
		else{
			printf("\n----------- Aluno %d ---------\n",i+1);
			printf("Nome: %s\nN matricula:%d\nNota 1 prova:%.2lf\nNota 2 prova:%.2lf\nNota 3 prova:%.2lf\n",
			a[i].nome, a[i].matricula, a[i].prova1, a[i].prova2, a[i].prova3);
			printf("\nREPROVADO COM NOTA %.2lf :(\n",media);
			printf("-------------------------------\n");
		}
	}
}

//---------------SALVAR DADOS EM UM ARQUIVO BINARIO-----------
void salvaArquivoBinario(taluno alunos[]){
	FILE *arq;
	arq=fopen("dadosAlunos.txt","wb");
	fwrite(&alunos[0],sizeof(taluno),qtd,arq);
	printf("Dados salvos com sucesso - binario\n");
	fclose(arq);
}

//--------------CARREGAR DADOS DO ARQUIVO EM BINARIO------------
void carregaBinario(taluno alunos[]){
	FILE *arq;
	arq=fopen("dadosAlunos.txt","rb");
	if(arq==NULL){
	  printf("Arquivo nao encontrado :(\n");
	  return;
	  }
	 while(fread(&alunos[qtd],sizeof(taluno),1,arq) >0  )
	      qtd++;  
	 printf("Dados carregados com sucesso - binario !\n");
	fclose(arq);
}

//--------------MENU DE OPCOES------------
int menu(){
	int op;
	printf("*** SISTEMA DE CADASTRO DE ALUNOS ****\n");
	printf("1-Inserir novo aluno\n");
	printf("2-Mostrar todos os alunos\n");
	printf("3-Buscar aluno por nome\n");
	printf("4-Buscar aluno por N da matricula\n");
	printf("5-Aluno aprovado ou reprovado\n");	
	printf("6-Aluno com maior media geral\n");
	printf("0-Sair\n");
	scanf("%d",&op);
	return op;
}

//---------------------------
int main(){
	taluno alunos[MAX];
	char nomeBusca[40];
	int op, matri;
	carregaBinario(alunos);
    do{
      op = menu();	
      switch(op){
      	case 1: addAluno(alunos);
      	break;
     	case 2: mostraAluno(alunos);
      	break;
      	case 3: printf("Nome do aluno para buscar:");
      			fflush(stdin); gets(nomeBusca);
      			buscaAluno(alunos, nomeBusca);
      	break;		
      	case 4: printf("N da matricula para busca:");
      			scanf("%d",&matri);
      			buscaMatricula(alunos, matri);		
      	break;
		case 5: mediaAluno(alunos);
      	break;
      	case 6: mediamaior(alunos);
      	break;
      	case 0: salvaArquivoBinario(alunos);
		  		printf("Saindo... \n");
      	break;
	  }
      	getch(); // pausa na tela - espera digitar uma tecla
      	system("cls");
	}while(op!=0);
	return 0;
}
