/***************************************************************/
/**                                                           **/
/**   João Pedro Lima Affonso de Carvalho          11260846   **/
/**   Exercício-Programa 02 - Seven & Half                    **/
/**   Professor: Alair Pereira do Lago                        **/
/**   Turma: (03)                                             **/
/**                                                           **/
/***************************************************************/



#include <stdio.h>

#define false 0
#define true 1

double raizCubica(double x); /*Declara o metodo raizCubica*/
int chao(double x); /*Declara o metodo chao*/
int contaDigitos(int x); /*Declara o metodo contaDigitos*/
double tornaDecimal(int x); /*Declara o metodo tornaDecimal*/
double novaCaixa(double caixa); /*Declara o metodo novaCaixa*/
double pontuaCarta(double caixa); /*Declara o metodo pontuaCarta*/


double pont_apostador = 0; /*Inicializa a pontuacao do apostador*/
double pont_banca = 0; /*Inicializa a pontuacao da banca*/
int num_apostador = 0; /*Inicializa a variavel que guardara a quantidade de cartas retiradas para o apostador*/
int num_banca = 0; /*Inicializa a variavel que guardara a quantidade de cartas retiradas para a banca*/
double teto; /*Declara o teto de pontuacao do apostador*/
int semente; /*Declara a variavel que iniciara a Simulacao*/
double caixa; /*Declara a caixa que iniciara um novo sorteio*/
int derrotas = 0; /*Inicializa a variavel que guarda quem ganhara o jogo. A derrota refere-se a derrota da banva, ou seja, seu valor e true quando o apostador vencer*/

int main()
{

    printf("\n Bem-vindo a Simulacao do jogo Seven n Half do aluno Joao Pedro L.A. de Carvalho. \n");
    printf("\n Para iniciar a Simulacao, e necessario que seja digitado um numero inteiro: \n");
    scanf("%d", &semente); /*Coleta a variavel que inicia a Simulacao*/
    printf("\n Aperte uma tecla para iniciar a Simulacao com a semente %d ! \n", semente);
    getch();

    caixa = tornaDecimal(semente); /*A variavel que inicia a Simulacao e colocada em forma decimal, pois caixa pertence ao intervalo [0,1[*/

    for(teto = 0.5; teto <= 7.5; teto = teto + 0.5) /*Faz Simulacoes para cada um dos tetos de pontuacao permitidos para o apostador*/
    {
        for(int n = 1; n <= 10000; n++) /*Para cada teto, simula n = 10000 jogos*/
        {
            while(pont_apostador < teto) /*Enquanto a pontuacao do apostador for menor do que o teto, sorteia-se mais uma carta a ele*/
            {
                pont_apostador = pont_apostador + pontuaCarta(caixa); /*Soma a pontuacao de um sorteio a pontuacao do apostador*/
                num_apostador++; /*Soma mais uma carta a quantidade de cartas retiradas para o apostador*/
                caixa = novaCaixa(caixa); /*Gera uma nova caixa para um novo sorteio*/
            }

            if(pont_apostador <= 7.5) /*Se a pontuacao do apostador nao estourou, o jogo continua*/
            {

                while(pont_apostador > pont_banca && pont_banca < 7.5)  /*Enquanto a pontuacao da banca for menor do que a do apostador, e for uma pontuacao valida...*/
                {
                    pont_banca = pont_banca + pontuaCarta(caixa);  /*Continua o sorteio de cartas para a banca*/
                    num_banca++; /*Soma mais uma carta a quantidade de cartas retiradas para a banca*/
                    caixa = novaCaixa(caixa); /*Gera uma nova caixa para um novo sorteio*/

                }

                if((pont_banca > 7.5) || (pont_apostador > pont_banca) || (pont_apostador == pont_banca && num_apostador < num_banca))
                {
                    /*Se a pontuacao da banca estoura, se as pontuacoes forem iguais e a banca tiver retirado mais cartas
                     ou a pontuacao do apostador for maior do que a da banca, uma derrota da banca e contada*/

                    derrotas++;
                } /*Os casos de empate (pont_apostador = pont_banca && num_apostador == num_banca) sao contados como vitoria da banca, por isso apenas o sinal de maior (>) valida o codigo acima*/
            }

            pont_apostador = 0; /*Reinicia a pontuacao do apostador para uma nova Simulacao dentro do mesmo teto*/
            pont_banca = 0; /*Reinicia a pontuacao da banca para uma nova Simulacao dentro do mesmo teto*/
            num_apostador = 0; /*Reinicia a quantidade de cartas do apostador para uma nova Simulacao dentro do mesmo teto*/
            num_banca = 0;  /*Reinicia a quantidade de cartas da banca para uma nova Simulacao dentro do mesmo teto*/

        }


        printf("\n %.1f %d ", teto, derrotas); /*Exibe na tela as duas primeiras informacoes, teto e numero de derrotas, pulando sempre uma linha com \n*/

        for(int cont = 1; cont <= chao(derrotas/100 + 0.5); cont++)  /*Conforme a formula do roteiro, o contador x fara com que seja digitada a quantidade certa de caracteres "*" */
        {


            printf("*");  /*Concatena um caractere "*" a linha onde estao as informacoes teto e numero de derrotas*/

        }
        printf("\n"); /*Pula uma linha*/

        derrotas = 0; /*Reinicia a quantidade de derrotas para as novas Simulacoes (de 1 a 10000) dos proximos tetos*/
    }

    return 0;


}

int chao(double x)  /*Funcao que retorna o maior inteiro menor ou igual o numero x*/
{

    int inteiro = 0; /*Valor que sera posteriormente retornado. Comeca em 0 pois o numero retornado e natural*/
    int i = 0; /*Contador que vai somando 1, desde o 0, ate passar do maior inteiro menor ou igual do que x*/

    while(i <= x)  /*O looping acaba quando i passa do valor desejado*/
    {

        inteiro = i; /*O valor a ser retornado vai recebendo o contador ate o chegar no valor desejado*/
        i = i + 1; /*O contador passa a ser o proximo inteiro*/

    }

    return inteiro;
}


int contaDigitos(int x)  /*Fimcao que retorna o numero de digitos de x*/
{

    int dig = 0; /*Numero de digitos que sera posteriormente retornado*/

    if(x/10 == 0)  /*Se o numero for menor do que 10*/
    {
        dig = 1; /*Retorna que a quantidade de digitos do numero e apenas 1*/
    }
    else
    {

        while(x/10 > 0) /*Para numeros com 2 digitos ou mais, "descasca-se" o numero...*/
        {
            x = x/10; /*Por meio da parte inteira da divisao por 10*/
            dig++; /*Conta mais um digito*/
        }

        dig++; /*Quando so tiver 1 digito sobrando, esse digito sera menor do que 10, entao o looping acima nao o somara. Para corrigir isso, soma-se aqui o ultimo digito*/

    }

    return dig;

}

double tornaDecimal(int x)  /*Funcao que retorna um numero a partir da entrada x, colocando essa entrada em forma decimal. por exemplo, para x = 123, o retorno e 0.123*/
{
    double retorno = x; /*Numero a ser retornado, que inicialmente recebe x*/

    for(int i = 1; i<= contaDigitos(x); i++)  /*Looping que, a partir de quantos digitos a entrada tem (n), divide essa entrada por 10^n*/
    {

        retorno = retorno/10; /*Divide retorno de forma iterativa por 10, ate 10^n, "empurrando" todos os digitos a uma unidade a esquerda por iteracao*/

    }

    return retorno;
}


double novaCaixa(double caixa) /*Funcao que cria uma nova caixa (parametro do sorteio da carta) em funcao da caixa corrente*/
{

    /*As formulas abaixo foram fornecidas no documento*/
    double rifa =  9821.00 * raizCubica(caixa) + 0.211327;
    caixa = rifa - chao(rifa);

    return caixa; /*Retorna a nova caixa para um novo sorteio*/


}

double pontuaCarta(double caixa)  /*Funcao que sorteia uma nova carta, a partir do parametro caixa ("caixa magica"), e retorna a pontuacao dessa carta*/
{

    int carta = chao(caixa*10 + 1) /*Retorna um inteiro entre 1 e 10, simbolizando uma carta (As = 1, Dama = 8, Valete = 9, Rei = 10)*/;
    double pontuacao; /*Valor a ser posteriormente retornado pela funcao, contendo a pontuacao da carta (de 1 a 7: pontuacao  = numero da carta, de 8 a 10: pontuacao = 0.5)*/

    if(carta > 7)
    {

        pontuacao = 0.5; /*Pontuacao padrao para Dama, Valete e Rei*/

    }
    else
    {
        pontuacao = carta; /*Pontuacao das carats numeradas e As: numero da carta (As = 1)*/
    }

    return pontuacao;

};


double raizCubica(double x)  /*Funcao que retorna a raiz cubica de x*/
{

    double novo = 1; /*Variavel que guarda r_n da sequencia de iteracao*/
    double antigo = 0; /*Variavel que guarda r_(n-1) da sequencia de iteracao*/
    int primeira_iteracao = true; /*Apontador que sinaliza o inicio da iteracao, ou seja, n = 0. Logo apos a primeira iteracao, seu valor e mudado, pois muda-se a formula para determinar r_n*/

    while(novo - antigo > 1E-8 || novo - antigo < -1E-8)  /*Enquanto o modulo da diferenca entre r_n (novo) e r_(n-1) (antigo) for maior do que 0,00000001, a iteracao continua , para melhor aproximacao*/
    {
        /*Foram escolhidos os valores inicais para r_n = 1 e r_(n-1) = 0 pois |r_n - r_(n-1)| = 1 >>>> 1E-8. Na verdade, poderiam ser escolhidos quaisquer valores tais que |r_n - r_(n-1)| > 1E-8*/

        if (primeira_iteracao == true)    /*Para a i primeira iteracao, r_n recebe x*/
        {
            novo = x; /*r_n recebe x*/
            primeira_iteracao = false; /*A partir dai, o algoritmo comecara a usar a formula abaixo nas proximas iteracoes*/
        }

        else   /*A partir da segunda iteracao*/
        {

            antigo = novo; /*Ao avancar uma iteracao, r_n torna-se r_(n-1) e calcula-se um novo r_n. Exemplo: n = 10, novo = r_(10) e antigo = r_9. Em n = 11, novo = r_(11) e antigo = r_(10)*/

            novo = (double) (2*antigo/3 + x/(3*antigo*antigo)); /*Equivale a formula r_n = 2/3*r_(n-1) + x/(3*r^2_(n-1)), com novo sempre recebendo o novo valor de r_n (o da n-esima iteracao) */
            novo = (double) (2*antigo/3 + x/(3*antigo*antigo)); /*Equivale a formula r_n = 2/3*r_(n-1) + x/(3*r^2_(n-1)), com novo sempre recebendo o novo valor de r_n (o da n-esima iteracao) */

        }
    }

    return novo; /*Quando |r_n - r_(n-1)| < 1E-8, o looping finaliza e o metodo retorna o novo (ultimo) valor de r_n*/
}


