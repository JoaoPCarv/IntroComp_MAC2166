/************************************* **************************/
/**                                                           **/
/**   Jo�o Pedro Lima Affonso de Carvalho          11260846   **/
/**   Exerc�cio-Programa 01 - Senha                           **/
/**   Professor: Alair Pereira do Lago                        **/
/**   Turma: (03)                                             **/
/**                                                           **/
/***************************************************************/


#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int main(){

/*Defini��o de vari�veis iniciais*/
int c = 0; /*Quantidade m�xima de cores para o jogo. Inicialmente � 0 para entrar na primeira verifica��o do while, mas � formalmente um valor entre 1 e 9*/
int k = 0; /*Quantidade de pinos no tabuleiro, n�mero >= 1*/
int p = 0; /*N�mero m�ximo de palpites*/
int senha; /*Senha a ser fornecida pelo jogador*/
int senhadiv; /*Divisor auxiliar para o "descascamento" da senha, guarda os v�rios est�gios de "descascamento" at� o final, deixando a senha armazenada "constanetmente" em seu campo (int senha)*/
int palpite; /*Palpite a ser fornecido pelo jogador*/
int pinos = 0; /*Quantidade de pinos pretos*/
int algfinal = FALSE; /*Ponteiro que sinaliza o final do "descascamento" da senha (senhadiv) e do palpite*/

/*Apresenta��o*/
printf("Bem-vindo ao Jogo da Senha do aluno Joao Pedro L.A. de Carvalho. \n");


/*Consist�ncia na quantidade de cores*/
while (c < 1 || c > 9){

    printf("\nDigite a quantidade de cores que voce deseja para o seu jogo. Sao permitidas de 1 a 9 cores. \n");
    scanf("%d", &c);

    if (c < 0 || c > 9){ /*Mensagem de aviso*/

    printf("\nVoce digitou uma quantidade invalida. Tente de novo.\n");
    }
}

/*Consist�ncia na quantidade de pinos*/
while(k < 1){

    printf("\nDigite a quantidade de pinos que voce deseja para o tabuleiro. O minimo e 1. \n");
    scanf("%d", &k);

    if(k < 0){ /*Mensagem de Aviso*/

        printf("\nVoce digitou uma quantidade invalida. Tente de novo.\n");
}
}

/*Consist�ncia no n�mero m�ximo de palpites*/
while(p < 1){

    printf("\nDigite o numero maximo de palpites para o jogo. O minimo e 1. \n");
    scanf("%d", &p);

    if(p < 0){ /*Mensagem de Aviso*/

        printf("\nVoce digitou uma quantidade invalida. Tente de novo.\n");
}
}

/*Bloco fornecido nas instru��es deste EP. N�o ser� feita a consist�ncia sobre esse c�digo.*/
    printf("\nEntre com a senha de %d digitos (0 para valor aleatorio): \n", k);
    scanf("%d",&senha);

   if (senha == 0) {

     srand(time(NULL));

   for (int i = 0; i < k; i++) {

     senha = senha*10 + (rand() % c + 1);

     }
}
/*Fim do bloco fornecido*/

printf("\nAperte uma tecla para comecar o jogo! \n");
getch(); /*Espera o usu�rio apertar uma tecla*/


   for(int j = 1; j <= p; j++){ /*Aqui ser� utilizado o divisor auxiliar da senha, "senhadiv"*/

        pinos = 0; /*Sempre reinicializa a contagem de pinos pretos*/
        printf("\nDigite o seu palpite numero %d : \n", j);
        scanf("%d", &palpite); /*Para simplificar, aqui n�o � feita a verifica��o de consist�ncia do valor digitado*/
        printf("\nPALPITE: %d \n", palpite);
        senhadiv = senha; /*Recebe a senha sem descascar a cada palpite. Vai alterando seu valor com o "descascamento", por�m deixa a senha invari�vel para poss�veis novos "descascamentos"*/

     while(algfinal != TRUE) { /*"Descasca" a senha (senhadiv) at� o �ltimo d�gito, em que a parte inteira da divis�o por 10 resulta em 0*/

             if(senhadiv%10 == 0) algfinal = TRUE; /*Para o �ltimo d�gito (o mais significativo), sua divis�o por 10 resulta na parte inteira 0, sinalizando o final da senha e do palpite*/

           else if(senhadiv%10 == palpite%10) /*Compara os digitos menos significativos da senha (senhadiv) e do palpite (mesma posicao: resto da divisao por 10)*/ {

                pinos++; /*Soma a quantidade de pinos iguais (sinalizacao por pinos pretos)*/ }

                palpite = palpite/10;
                senhadiv = senhadiv/10;
                /*Atualiza a senha (senhadiv) e o palpite para diminuir seus algarismos, por ignorar a parte a fracion�ria*/ }

            if(k == pinos){ /*Vit�ria caso a quantidade de pinos pretos for igual � pr�pria quantidade de pinos (palpite � igual � senha)*/

                printf("\nParabens! Voce venceu a partida em %d palpites.\n", j);
                j = p + 1;
                /*Informa em quantos palpites a pessoa venceu a partida, e logo sai do looping for... por "for�ar" a condi��o de sa�da (j = p + 1)*/



            } else if(j == p){ /*Mensagem para o caso de e pessoa nao tenha conseguido vencer em todas as tentativas (palpites)*/

            printf("\nVoce nao conseguiu, nessas %d tentativas, acertar a senha %d ...Mas tente de novo! Obrigado por jogar.\n.", p, senha);

            } else {printf(
            "\nQuantidade de pinos pretos: %d \n",pinos); /*Mensagem para informar a quantidade de pinos iguais (pinos pretos) em uma jogada entre a primeira e a ultima*/
            algfinal = FALSE;} /*Reinicia o sinalizador para que na pr�xima jogada possa ser feito de novo o "descascamento"*/

  }



return(0);
}




