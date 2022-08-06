/***************************************************************/
/**                                                           **/
/**   João Pedro Lima Affonso de Carvalho          11260846   **/
/**   Exercício-Programa 03 - Caça-Minas                      **/
/**   Professor: Alair Pereira do Lago                        **/
/**   Turma: (03)                                             **/
/**                                                           **/
/***************************************************************/
#include <stdio.h>;
#include <stdlib.h>

#define MMAX 90
#define NMAX 90
#define true  1
#define false 0

/*Declarador de metodos*/
void verificador_Inicial();
void emoldura_Tab(int m, int n, char tabuleiro[m][n]);
void sorteia_Minas(int s, int m, int n, int z, int T[m][n]);
void torna_Maiusculo(char *x);
void abrir_Mina(int linha_c, int coluna_c, int *resultado, int m, int n, int z, char tabuleiro[m][n], int T[m][n], int status[m][n]);
void marcar_Mina(int linha_c, int coluna_c, int m, int n, int z, int marcadas, char tabuleiro[m][n], int T[m][n], int status[m][n]);
void desmarcar_Mina(int linha_c, int coluna_c, int m, int n, int z, char tabuleiro[m][n], int T[m][n], int status[m][n]);


/*Declara e inicializa os parametros iniciais do jogo*/
int m,n,z,s = 0;
int mina_plantada = false;
int resultado = 0;
char comando;
int linha_c, coluna_c;
int marcadas, livres = 0;

int main()
{
    verificador_Inicial(); /*A funcao 'chamada' garante valores validos para m,n,z e s*/

    printf("\n Numero de linhas (3 <= m <= %d) :  %d", MMAX, m);
    printf("\n Numero de colunas (3 <= n <= %d):  %d", NMAX, n);
    printf("\n Numero de minas (1 <= z <= %d)  :  %d", m*n-1, z);
    printf("\n Semente (1 <= s <= 12345)       :  %d", s);
    printf("\n Bem vindo ao Caca-Minas! \n");

    char tabuleiro[m][n]; /*Cria o tabuleiro, que sera emoldurado por metodo externo*/
    int T[m][n], status[m][n]; /*Cria um mapa auxiliar que guarda a posicao das minas e uma matriz para guardar o status da casa(i, j): '1' para fechada e desmarcada, '2' para fechada e marcada e '3' para aberta*/
    printf("\n");

    sorteia_Minas(s, m, n, z, T);

    for(int i = 0; i <= m - 1; i++)
    {
        for(int j = 0; j <= n - 1; j++)
        {
            tabuleiro[i][j] = '.';
            status[i][j] = 1;
        }
    }
    printf("\n");

    while(resultado == 0)  /*Enquanto o jogo esta ocorrendo...*/
    {
        emoldura_Tab(m, n, tabuleiro);

        livres = m*n;
        marcadas = 0;

         for(int i = 0; i <= m - 1; i++){
            for(int j = 0; j <= n - 1; j++) {
            if(status[i][j] == 2) marcadas++;
            if(status[i][j] != 1) livres--;
        }
         }

        printf("\n Por enquanto: %d/%d marcadas, %d livres. \n.", marcadas, z, livres);

        int verificador = false;

        while(verificador == false)
        {
            printf("\n Proximo chute (comando, casa(i,j)) : ");
            scanf(" %c  %d  %d", &comando, &linha_c, &coluna_c);
            torna_Maiusculo(&comando); /*Coloca o caractere do comando em maiusculo*/

            if((comando == 'A' || comando == 'D' || comando == 'M') && (1 <= linha_c && linha_c <= m) && (1 <= coluna_c && coluna_c <= n))
            {
                /*Verifica todas as condicoes pelas quais as entradas dos usuarios sao validas: comando ser 'A', 'D' ou 'M' e linha e coluna da casa a ser aplicada ao comando estar dentro do tabuleiro emoldurado*/
                verificador = true;
            }
            else
                printf("\n Foi digitado um comando errado ou uma casa invalida. Tente novamente, por favor. \n");
        }
        if(comando == 'A') abrir_Mina(linha_c, coluna_c, &resultado, m, n, z, tabuleiro, T, status);
        else if(comando == 'M') marcar_Mina(linha_c, coluna_c, m, n, z, marcadas, tabuleiro, T, status);
         else if(comando == 'D') desmarcar_Mina(linha_c, coluna_c, m, n, z, tabuleiro, T, status);
    }
    return 0;
}

void verificador_Inicial()  /*Funcao que verifica a entrada de dados pelo usuario no inicio da execucao do jogo*/
{

    while(m < 3 || m > 90) /*Verificacao do numero de linhas*/
    {
        printf("\nDe o numero de linhas do tabuleiro do jogo, entre 3 e %d : \n", MMAX);
        scanf("%d", &m);

        if(m < 3 || m > 90)
        {
            printf("\nFoi digitado um valor invalido. Tente novamente, por favor. \n");
        }
    } /*Verifica se o numero de linhas m esta dentro do intervalo aceitado*/

    while(n < 3 || n > 90) /*Verificacao do numero de colunas*/
    {
        printf("\nDe o numero de colunas do tabuleiro do jogo, entre 3 e %d : \n", NMAX);
        scanf("%d", &n);

        if(n < 3 || n > 90)
        {
            printf("\nFoi digitado um valor invalido. Tente novamente, por favor. \n");
        }
    } /*Verifica se o numero de colunas m esta dentro do intervalo aceitado*/

    while(z < 1 || z > m*n - 1)  /*Verificacao do numero de minas*/
    {
        printf("\nDe o numero de minas plantadas no tabuleiro, entre 1 e %d: \n", m*n - 1);
        scanf("%d", &z);

        if(z < 1 || z > m*n - 1)
        {
            printf("\nFoi digitado um valor invalido. Tente novamente, por favor. \n");
        }
    } /*Verifica se o numero de minas z esta dentro do intervalo aceitado*/

    while(s < 1 || s > 12345)
    {
        printf("\nDe a semente, entre 1 e 12345: \n");
        scanf("%d", &s);

        if(s < 1 || s > 12345)
        {
            printf("\nFoi digitado um valor invalido. Tente novamente, por favor. \n");
        }
    }
}

void sorteia_Minas(int s, int m, int n, int z, int T[m][n])  /*Funcao que sorteia as minas pelo tabuleiro T, que guarda essa informacao*/
{
    int i_mina, j_mina; /*Coordenadas da mina no tabuleiro*/

    for(int i = 0; i <= m - 1; i++)
    {
        for(int j = 0; j <= n - 1; j++)
        {
            T[i][j] = 0;
        }
    }
    srand(s);

    int numero; /*Parametro de sorteio*/

    for(int i = 1; i <= z; i++)
    {
        while(mina_plantada == false)
        {
            numero = rand(); /*O parametro de sorteio recebe o proximo valor randomico*/
            i_mina = numero % m;
            j_mina = (numero / m) % n;

            if(T[i_mina][j_mina] != -1)
            {
                T[i_mina][j_mina] = -1;
                mina_plantada = true;
            }
        }

        mina_plantada = false;

    }
    int vizinhos = 0;

    for(int i = 0; i <= m - 1; i++)
    {
        for(int j = 0; j <= n - 1; j++)
        {
            if(T[i][j] != -1)
            {
                if(0 <= i - 1 && 0 <= j - 1)
                {
                    if(T[i - 1][j - 1] == -1)
                    {
                        vizinhos++;
                    }
                }
                if(0  <= i - 1)
                {
                    if(T[i - 1][j] == -1)
                    {
                        vizinhos++;
                    }
                }
                if(0  <= i - 1 && j + 1 <= n - 1)
                {
                    if(T[i - 1][j + 1] == -1)
                    {
                        vizinhos++;
                    }
                }
                if(0 <= j - 1)
                {
                    if(T[i][j - 1] == -1)
                    {
                        vizinhos++;
                    }
                }
                if(j + 1 <= n - 1)
                {
                    if(T[i][j + 1] == -1)
                    {
                        vizinhos++;
                    }
                }
                if(i + 1 <= m - 1 && 0 <= j - 1)
                {
                    if(T[i + 1][j - 1] == -1)
                    {
                        vizinhos++;
                    }
                }
                if(i + 1 <= m - 1)
                {
                    if(T[i + 1][j] == -1)
                    {
                        vizinhos++;
                    }
                }
                if(i + 1 <= m - 1 && j + 1 <= n - 1)
                {
                    if(T[i + 1][j + 1] == -1)
                    {
                        vizinhos++;
                    }
                }
                T[i][j] = vizinhos;
            }
            vizinhos = 0;
        }
    }
}

void emoldura_Tab(int m, int n, char tabuleiro[m][n])  /*Funcao que cria uma moldura para o tabuleiro, com as coordenadas das casas*/
{
    int indice_v = -1;
    int indice_h = 1;

    for(int i = -2; i <= m + 1; i++)
    {
        for(int j = -2; j <= n + 1; j++)
        {
            if(i == -2 || i == m + 1)
            {
                if(j >= 0 && j <= n - 1)
                {
                    printf(" %2d ", indice_h); /*Digita o indice na coluna*/
                    indice_h++; /*Incrementa para o proximo indice da coluna*/
                }
                else
                    printf("  "); /*Imprime um espaço para que se coloque as colunas a mais abaixo*/
            }
            else if(i == -1 || i == m)
            {
                if(j == -2 || j == n + 1)
                    printf("   ");
                else if(j == -1 || j == n)
                    printf(" + ");
                else
                    printf("----");
            }
            else if(i >= 0 && i <= m - 1)
            {
                if(j == -2 || j == n + 1)
                {
                    printf(" %2d ", indice_v);
                }
                else if(j == -1 || j == n)
                {
                    printf("|");
                }
                else
                    printf("%2c  ", tabuleiro[i][j]);  /*imprime o conteudo de cada posicao da matriz*/
            }
        }
        indice_h = 1; /*Reinicia a contagem de colunas*/
        indice_v++; /*Incrementa a contagem de linhas*/

        printf("\n");
    }
}

void torna_Maiusculo(char *x)  /*Funcao que coloca letras em maiusculo, seguindo a tabela ASCII*/
{
    if(*x >= 97 && *x <= 122)
    {
        *x = *x - 32;
    }
}

void abrir_Mina(int linha_c, int coluna_c, int *resultado, int m, int n, int z, char tabuleiro[m][n], int T[m][n], int status[m][n]) /*Funcao que abre uma mina, se ela nao estiver aberta*/
{
    if(status[linha_c - 1][coluna_c - 1] != 3)  /*Se a casa(linha_c, coluna_c) nao estiver aberta (-1 e o fator de correcao entre a moldura e a matriz)*/
    {
        if(T[linha_c - 1][coluna_c - 1] == -1) /*Se houver uma mina plantada na posicao escolhida...*/
        {
            for(int i = 0; i <= m - 1; i++)
            {
                for(int j = 0; j <= n - 1; j++)
                {
                    if(T[i][j] == -1)
                        tabuleiro[i][j] = '@'; /*Demarca no tabuleiro a posicao de todas as minas*/
                    else
                        tabuleiro[i][j] = (char) T[i][j] + '0'; /*Demarca no tabuleiro as casas que nao possuem minas, com seus valores (de minas adjacentes) no T[m][n]*/
                }
            }
            *resultado = -1; /*Retorna para o metodo principal a derrota*/
            printf("\n BOOM! Voce acaba de pisar numa mina!\n");
            emoldura_Tab(m,n, tabuleiro);
        }
        else
        {
            int conta_abertas = 0; /*Variavel de controle que conta quantas casas ja estao abertas*/

            for(int i = 0; i <= m - 1; i++)
            {
                for(int j = 0; j <= n - 1; j++)
                {
                    if(status[i][j] == 3)
                        conta_abertas++;
                }
            }

            if(conta_abertas == m*n - z - 1) /*Se ja tiverem sido abertas todas as casas sem minas antes dessa, o jogo acaba em vitoria*/
            {
                for(int i = 0; i <= m - 1; i++)
                {
                    for(int j = 0; j <= n - 1; j++)
                        if(T[i][j] == -1)
                            tabuleiro[i][j] = '@'; /*Demarca no tabuleiro a posicao de todas as minas*/
                }
                tabuleiro[linha_c - 1][coluna_c - 1] = (char) T[linha_c - 1][coluna_c - 1] + '0'; /*Preenche a ultima casa aberta com seu valor em T[m][n]*/
                *resultado = 1; /*Retorna para o metodo principal a vitoria*/
                printf("\n Parabens! Voce venceu. \n");
                emoldura_Tab(m,n, tabuleiro);
            }
            else /*Se a mina sendo aberta nao for a ultima sobrando*/
            {
                status[linha_c - 1][coluna_c - 1] = 3; /*Atualiza o status da casa(linha_c)(coluna_c) para aberta*/
                if(T[linha_c - 1][coluna_c - 1] == 0)  /*Se a casa escolhida nao tem vizinhos adjacentes*/
                {
                    for(int i = linha_c -2; i <= linha_c + 2; i++)
                    {
                        for(int j = coluna_c - 2; j <= coluna_c + 2; j++)
                        {
                            if(i >= 0 && i <= m-1 && j >= 0 && j <= n - 1)
                            {
                                if(T[i][j] != -1)
                                {
                                    tabuleiro[i][j] = (char) T[i][j] + '0';
                                    status[i][j] = 3;
                                }
                            }
                        }
                    }

                    int contador = 0;

                    for(int i = 0; i <= m - 1; i++)
                {
                    for(int j = 0; j <= n - 1; j++)
                    {
                        if(status[i][j] == 3)
                            contador++;
                    }
                }

                if(contador == m*n - z){

            for(int i = 0; i <= m - 1; i++)
            {
                for(int j = 0; j <= n - 1; j++)
                {
                    if(T[i][j] == -1)
                        tabuleiro[i][j] = '@'; /*Demarca no tabuleiro a posicao de todas as minas*/
                }
            }
                *resultado = 1; /*Retorna para o metodo principal a vitoria*/
                printf("\n Parabens! Voce venceu. \n");
                emoldura_Tab(m,n, tabuleiro);
                }
                }
                else
                    tabuleiro[linha_c - 1][coluna_c - 1] = (char) T[linha_c - 1][coluna_c - 1] + '0'; /*Coloca na casa o valor correspondente a quantidade != 0 de minas adjacentes a casa*/
            }
        }
    }
    else
        printf("\n Sem efeito. \n");
}

void marcar_Mina(int linha_c, int coluna_c, int m, int n, int z, int marcadas, char tabuleiro[m][n], int T[m][n], int status[m][n]) /*Funcao que marca  uma mina, se ela nao estiver marcada*/
{
if(status[linha_c - 1][coluna_c - 1] == 1 && marcadas != z){ /*Se a posicao estiver fechada e desmarcada e ainda tiver minas para marcar*/

status[linha_c - 1][coluna_c - 1] = 2; /*Atualiza para fechada e marcada*/
tabuleiro[linha_c - 1][coluna_c - 1] = '*';

} else printf("\n Sem efeito. \n");
}

void desmarcar_Mina(int linha_c, int coluna_c, int m, int n, int z, char tabuleiro[m][n], int T[m][n], int status[m][n]) /*Funcao que desmarca  uma mina, se ela estiver marcada*/
{
if(status[linha_c - 1][coluna_c - 1] == 2){ /*Se a posicao estiver fechada e marcada*/

status[linha_c - 1][coluna_c - 1] = 1; /*Atualiza para fechada e desmarcada*/
tabuleiro[linha_c - 1][coluna_c - 1] = '.';

} else printf("\n Sem efeito. \n");
}
