#include <stdio.h>
#include <stdlib.h>


int main(){
    char usuario[30];//interacao com o usuario
    int numMochila, pesoMax[3];
    FILE *fp; // Declaração da estrutura
	printf("Digite o nome do arquivo: ");
	scanf("%s",usuario);
	fp = fopen(usuario,"rt");
	int i,numItens, pesoItem;
	int auxTeste[3];
	int pesoItens[20];

    int controle=0;
    int posicao=0;//posicao dos itens na mochila



    int pesoArq[3];//peso das solucoes propostas pelo arquivo.
	if (!fp){
	 	printf ("Erro na abertura do arquivo."); //no caso de um erro fopen() retorna um 			ponteiro (NULL)

	}
    int auxPosicao=0;

    fscanf (fp, "%d", &i);//le o num de mochila
    numMochila=i;
    for(int j=0; j<numMochila; j++){
        fscanf (fp, "%d", &i);//le o pesoMax de cada mochila
        pesoArq[j]=0;//zero o peso do arquivo para ser somado.
        pesoMax[j]=i;//salva o peso maximo suportado por cada mochila.
    }
    fscanf (fp, "%d", &i);//le o num de Itens
    numItens=i;


    int mochila[numMochila][numItens];
    int solucao[numMochila][numItens];//cria um vetor de solucao, o qual será dado pela solucao de cada linha
    int solucaoArq[numMochila];
    while(!feof(fp)){//le os pesos com os respectivos valores até o final do arquivo
        if(controle<numItens){

            fscanf (fp, "%d", &i);
            pesoItem=i;// peso do item
            fscanf (fp, "%d", &i); //le o valor do item
            pesoItens[posicao]=pesoItem;

            for(int j=0;j<numMochila; j++){
                mochila[j][posicao]=i;
                solucaoArq[j]=0;//zera a solucao proposta pelo arquivo para ser lida.
            }

            posicao++;
        }

        else{//le a solucao do arquivo.
            for(int j=0; j<numMochila; j++){
                fscanf (fp, "%d", &i);
                auxTeste[j]=i;
                if(auxTeste[j]==1){
                    solucaoArq[j]+=mochila[j][auxPosicao];
                    pesoArq[j]+=pesoItens[auxPosicao];
                }
                if(pesoArq[j]>pesoMax[j]){//se o peso da solucao proposta pelo arquivo for maior que o peso de alguma mochila.
                    printf("Solucao inviavel.");
                    fclose(fp);
                    return 0;//encerra o programa
                }
            }

            auxPosicao++;
       }

         controle++;
    }

    int pesoTotal;

    for(int l=0;l<numMochila;l++){
        pesoTotal = 0;
        for(int j=0;j<numItens;j++){
                solucao[l][j]=mochila[l][j];


                pesoTotal=pesoItens[j];
                for(int k=0;k<numItens;k++){
                    if(mochila[l][j]==mochila[l][k]){
                        continue;//nao soma itens iguais
                    }
                    if((pesoItens[j]+pesoItens[k]<=pesoMax[l])&&((pesoTotal+pesoItens[k])<=pesoMax[l])){//verifica se a soma com o proximo item respeita os limites da mochila
                        solucao[l][j]+=mochila[l][k];//soma a solucao de cada linha
                        pesoTotal+=pesoItens[k];
                    }


                }

        }

    }

    int melhorSolucao[3];
    int resposta=0;//determina se a solucao é otima ou nao


    for(int i=0; i<numMochila; i++){
        melhorSolucao[i]=solucao[i][0];
        for(int j=0; j<numItens; j++){
            if(solucao[i][j]>melhorSolucao[i]){
                melhorSolucao[i]=solucao[i][j];//escolhe a melhor solucao entre a solucao de todas as linhas.
            }
        }
    }
    for(int i=0;i<numMochila; i++){
        if(solucaoArq[i]==melhorSolucao[i]){//se alguma solucao do arquivo for ótima para alguma mochila, a solução final é otima
            resposta=1;//solucao otima
            break;
        }
    }

    if(resposta==1){
        printf("Solucao otima.\n");
    }
    else{
        printf("Solucao viavel mas nao otima.\n");
    }

    fclose(fp);



}
