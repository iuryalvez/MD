#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

// facilitar visualização
typedef long long int lli;

struct private_key {
    lli p; // um primo qualquer 
    lli q; // um primo qualquer
    lli d; // inverso do 'e' em Zphi(n) 
};

typedef struct private_key private_key;

struct public_key {
    lli n; // n = p*q
    lli e; // expoente da fórmula de encriptar (M^e mod n)
};

typedef struct public_key public_key;

// menu de opções
void menu();

/**
 * @brief função que retorna uma chave privada com base em uma chave pública 'B'
 * 
 * @param B chave pública
 * @return private_key, uma chave privada
 */
private_key chave_privada(public_key B);

/**
 * @brief função que retorna uma chave pública com base em uma chave privada 'A'
 * 
 * @param A chave privada
 * @return public_key, uma chave pública 
 */
public_key chave_publica(private_key A);

/**
 * @brief função que retorna o "t" do algoritmo de euclides estendido de um número qualquer em Zn
 * 
 * @param Zn número Zn
 * @param num número "num" qualquer
 * @return long long, o "t"  
 */
lli t_euclides_estendido(lli Zn, lli num);

/**
 * @brief função que retorna se o número "n" é primo ou não
 * 
 * @param n número n
 * @return long long, TRUE or FALSE 
 */
lli num_primo(lli n);

/**
 * @brief função que retorna o número inverso de um número "n" em um Z
 * 
 * @param n número "n"
 * @param t número "t" calculado com o algoritmo de euclides estendido
 * @return long long, número inverso 
 */
lli num_inverso(lli n, lli t);

/**
 * @brief função que inverte 'd' ou 'e' em Zphi(n)
 * 
 * @param phi (p-1)*(q-1)
 * @param num 'd' ou 'e'
 * @return lli, long long int, o número invertido 
 */
lli inverter(lli phi, lli num);

/**
 * @brief função que retorna a potência de 2 mais próxima do valor do expoente
 * 
 * @param expoente é a variável 'e' da chave pública
 * @param pot potência
 * @return lli, long long int, a potência mais próxima
 */
lli maior_potencia(lli expoente, lli pot);


/**
 * @brief função que encripta uma mensagem 'm' com base em uma chave pública 'A'
 * 
 * @param A chave pública
 * @param m mensagem enviada
 * @return lli, long long int, mensagem encriptada 
 */
lli encriptar_RSA(public_key A, lli m);

/**
 * @brief função que desencripta a mensagem m com chave privada Apvt
 * 
 * @param Apvt chave privada
 * @param N mensagem encriptada
 * @return lli mensagem desencriptada
 */
lli desencriptar_RSA (private_key Apvt, lli N);

/**
 * @brief função que calcula o vetor de resultados das potências em Zn (M^e mod n) para encriptar ou desencriptar
 * 
 * @param n o n que fazemos o resto da divisão "mod n"
 * @param tam tamanho do vetor de resultados, é o valor da potência de base 2 mais próxima do 'e' da chave pública
 * @param m a BASE M (M^e mod n) 
 * @return lli* retorna o vetor de resultados em N
 */
lli *resultados_N(lli n, lli tam, lli m);

/**
 * @brief função que calcula as multiplicações modulares dos resultados válidos em Zn (M^e mod n)
 * 
 * @param n o valor Zn (mod n)
 * @param e o valor do expoente que somamos até chegar nele
 * @param resultados o vetor de resultados para sabermos os resultados válidos
 * @param m a BASE M (M^e mod n)
 * @return lli o resultado das multiplicações
 */
lli multiplicacoes_modulares(lli n, lli e, lli *resultados, lli m);

/**
 * @brief printa as somas das potências necessárias para chegarmos em 'e'
 * 
 * @param A chave pública A para sabermos o 'n' e o 'e'
 * @param m mensagem (M^e)
 */
void print_potencias_validas(public_key A, lli m);

/**
 * @brief Utiliza o teorema do resto chinês para calcular o resultado de um sistema de equações modulares
 * 
 * @param a1 O valor encontrado pelas multiplicações modulares com o 'p'
 * @param a2 O valor encontrado pelas multiplicações modulares com o 'q'
 * @param p Número 'p' da chave privada
 * @param q Número 'q' da chave privada
 * @return O resultado do sistema calculado pelo TCR
 */
lli tcr(lli a1, lli a2, lli p, lli q);

/**
 * @brief Imprime a tabela do teorema chinês do resto, na forma de uma matriz 7x2
 * 
 * @param x O resultado do sistema
 */
void print_TCR(lli tabela_tcr[7][2], lli x);

/**
 * @brief Retorna o maior entre dois números
 * 
 * @param n1 Primeiro número a ser comparado
 * @param n2 Segundo número a ser comparado
 * @return O maior entre n1 e n2
 */
lli maior_numero (lli n1, lli n2);

/**
 * @brief Encontra e retorna o máximo divisor comum entre dois números
 * 
 * @param n1 Primeiro número
 * @param n2 Segundo número
 * @return O m.d.c. entre n1 e n2
 */
lli mdc_dois_numeros(lli n1, lli n2);
