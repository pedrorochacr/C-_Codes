#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void eliminaCarac(char mensagem[],char mensagemDecod[],int posicaoCarac,int  tam){
//funcao usada para eliminar o caracter extra na devida posição
 	int k=0;

    printf("\n");
    for(int i=0;i<tam;i++){
       if(i==posicaoCarac-1){//pula a posicao do caracter extra
          continue;
       }
       else{
            mensagemDecod[k]=mensagem[i];//grava normalmente em mensagemDecod
            k++;
       }
    }


}

int converteBinario(int bin[]){
    //função para converter binário em inteiro
    int num=0,aux1,aux2;

    int  posicao=4;
    for(int i=0;i<5;i++){
        aux1=(int)pow(2,posicao);
        aux2=bin[i]*aux1;
        num+=aux2;
        posicao--;
    }


    return num;
}

int main(){

	char usuario[30];//interacao com o usuario
	char c;
	char mensagem[5000],mensagemCod[5000];
	int bin[5];
	int i=0,contador=0,deslocamento;
	int controle;

	FILE *fp; // Declaração da estrutura
	printf("Digite o nome do arquivo: \n");
	scanf("%s",usuario);
	printf("--------------------");
	fp = fopen(usuario,"rt");


	if (!fp){
	 	printf ("Erro na abertura do arquivo."); //no caso de um erro fopen() retorna um 			ponteiro (NULL)

	}

	while(!feof(fp)){ // Enquanto não chegar ao final do arquivo
        c=fgetc(fp);
        controle=c;
 		if(contador<=4){//ainda não terminou de ler os binários
            bin[contador]=c-'0';//converte char para int
            contador++;
 		}

 		else{
            if((controle-5<65)){//antes do A
                deslocamento=5-(controle-65);
                mensagem[i]=91-deslocamento;//volta para o Z e subtrai a partir dele
            }
            if((controle-5<97)&&(controle-5>90)){//depois do Z e antes do a
                deslocamento=5-(controle-97);
                mensagem[i]=123-deslocamento;//volta para o z e subtrai a partir dele
            }
            if(c=='#'){
                mensagem[i]=' ';// # nos espaços
            }
            if(((controle-5)>=65&&(controle-5)<=90)||((controle-5>=97)&&(controle-5)<=122)){//nao tem problema com o deslocamento
                mensagem[i]=c-5;
            }
            mensagemCod[i]=c;//salva os caracteres do arquivo texto
            i++;
 		}

 	}

 	int posicaoCarac=converteBinario(bin);//posicao caracter extra

    int tam=strlen(mensagem)-2;//subtrai os caracteres que não pertencem a mensagem
    int indice=tam-2;//subtrai o caracter extra

 	char mensagemDecod[tam];
 	char var1, var2;//variaveis utilizadas para desfazer a permutação e desfazer a reflexão

 	eliminaCarac(mensagem,mensagemDecod,posicaoCarac, tam);

    mensagemCod[tam]='\0';//define final da mensagem
    for(int i=0;i<tam/2; i+=4){
        //desfaz a permutação
        var1 = mensagemDecod[i];
  		var2 = mensagemDecod[i+1];
  		mensagemDecod[i]=mensagemDecod[indice-1];
  		mensagemDecod[i+1] = mensagemDecod[indice];
  		mensagemDecod[indice-1] = var1;//realiza a troca das letras
  		mensagemDecod[indice] = var2;
  		indice-=4;

 	}

 	for(int i=0;i<tam;i=i+2){
        //tira a reflexão dos blocos
        var1=mensagemDecod[i];
        mensagemDecod[i]=mensagemDecod[i+1];
        mensagemDecod[i+1]=var1;
 	}

    mensagemDecod[tam-1]='\0';//define final da mensagem


	printf("Mensagem codificada:\n");
	printf("--------------------\n");

    for(int i=0;i<5;i++){
        printf("%i",bin[i]);
    }
 	printf("%s\n",mensagemCod);
 	printf("\n");
    printf("----------------------\n");
 	printf("Mensagem decodificada:\n");
 	printf("----------------------\n");
 	printf("%s\n",mensagemDecod);

    fclose(fp);


}
