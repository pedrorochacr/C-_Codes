#include<stdio.h>
#include<stdlib.h>


int main(){

	char usuario[30];//interacao com o usuario
	int tamanho=21;
	int *valores=(int *) malloc(sizeof(int)*(tamanho));//aloca um vetor de 21 posicoes



	FILE *fp; // Declaração da estrutura
	printf("Digite o nome do arquivo de entrada: ");
	scanf("%s",usuario);
	fp = fopen(usuario,"rt");


	if (!fp){
	 	printf ("Erro na abertura do arquivo."); //no caso de um erro fopen() retorna um 			ponteiro (NULL)

	}

	int i = 0;
	int altura;//numero de fileiras
	int numCaixas=0;//utilizado para  a posicao das caixas


  	fscanf (fp, "%d", &altura);//primeira linha do arquivo é a quantidade de fileiras

	while(!feof(fp)){ // Enquanto não chegar ao final do arquivo


        fscanf (fp, "%d", &i);//armazena os valores das caixas em i


        int linhaAtual=altura+1;

        if(numCaixas>tamanho){//se numCaixas>tamanho. A memoria alocada anteriormente nao e suficiente
            tamanho=tamanho+linhaAtual;
            valores=(int *) realloc (valores, (tamanho)*sizeof(int));//realoca memoria
        }
        if(numCaixas<=tamanho){
            valores[numCaixas]=i;//guarda o valor de i em um vetor
        }

        numCaixas++;



	}
	 int somaLinha[altura], soma;//somalinha=vetor que guarda a soma de cada fileira do arquivo

        int posicao=0;

	int caixas[altura][altura];//matriz que guarda as caixas
        for(int i=0;i<altura;i++){
        soma=0;//zera a soma a cada linha
        for(int j=0;j<altura;j++){
            if(i>=j){//se a linha for maior que a altura. Assim os valores das caixas nao serao salvos em posicoes inexistentes.
                caixas[i][j]=valores[posicao];
                soma+=caixas[i][j];
                posicao++;
            }
            somaLinha[i]=soma;

        }
    }

    int fileira=2, co=1;
    int maiorSoma=somaLinha[0];//maior soma como a soma da primeira linha
    int auxSoma;//aux soma que armazena a soma das linhas.
    for(int i=0;i<altura;i++){
        for(int j=0;j<altura;j++){
            if(i>=j){
                int l=i;
                if(caixas[i][j]==0){//se a posicao for igual a 0.
                    auxSoma=0;
                    for(int k=0;k<=l-1;k++){//itera ate a linha atual, para realizar a soma das linhas acima.
                        auxSoma+=somaLinha[k];
                    }
                    if(auxSoma>maiorSoma){
                        maiorSoma=auxSoma;
                        fileira=i+1;
                        co=j+1;

                    }

                    }
                }
            }
    }

   printf("Resposta: fileira %i, caixa %i.\n",fileira, co);

	fclose(fp);//fecha o arquivo.
	free(valores);//libera a memoria alocada dinamicamente.














}
