#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define TRUE 1
#define FALSE 0

/* Esquema de printar letras coloridas (não entendi como faz no windows)
#ifdef __LINUX__
    #define RED   "\x1B[31m"
    #define GRN   "\x1B[32m"
    #define YEL   "\x1B[33m"
    #define BLU   "\x1B[34m"
    #define MAG   "\x1B[35m"
    #define CYN   "\x1B[36m"
    #define WHT   "\x1B[37m"
    #define RESET "\x1B[0m"
#endif
*/

// função que limpa a tela ("clear"/"cls")
void clear_screen();

//função que exibe as opções de um 'switch case'
void menu();

/**
 * @brief função que calcula o crivo de eratóstenes de um número "n"
 * 
 * @param n número referência para o cálculo
 */
void crivo_de_eratostenes(long int n);

/**
 * @brief função que informa se o número "n" é primo ou não
 * 
 * @param n número n
 * @return long int, TRUE or FALSE 
 */
long int num_primo(long int n);

/**
 * @brief função que retorna o maior divisor comum entre dois números
 * 
 * @param n1 número 1
 * @param n2 número 2
 * @return long int, o maior divisor 
 */
long int mdc_dois_numeros(long int n1, long int n2); 

/**
 * @brief função que retorna o maior divisor de um número "n"
 * 
 * @param n número
 * @return long int, maior divisor 
 */
long int MD(long int n);

/**
 * @brief função que exibe a árvore de fatores de um número "n"
 * 
 * @param n número "n"
 */
void arvore_de_fatores(long int n);

/**
 * @brief função que calcula e exibe o algoritmo de euclides
 * 
 * @param a número Za
 * @param b número b
 */
void euclides(long int a, long int b);

/**
 * @brief função que calcula e exibe o algoritmo de euclides estendido
 * 
 * @param a número Za
 * @param b número b
 */
void euclides_estendido(long int a, long int b);

/**
 * @brief função que retorna o "t" do algoritmo de euclides estendido
 * 
 * @param n1 número Zn
 * @param n2 número "a"
 * @return long int, o "t"  
 */
long int t_euclides_estendido(long int n1, long int n2);

/**
 * @brief função que retorna o maior número entre número 1 e 2
 * 
 * @param n1 número 1
 * @param n2 número 2
 * @return long int, maior número 
 */
long int maior_numero(long int n1, long int n2);

/**
 * @brief função que retorna o número inverso de um número "n" em um Za
 * 
 * @param n número "n"
 * @param t número "t" calculado com o algoritmo de euclides estendido
 * @return long int, número inverso 
 */
long int num_inverso(long int n, long int t);

// função que calcula e exibe a solução de uma equação linear modular
void equacoes_lineares();

// função que calcula e exibe a solução de sistema lineares modulares utilizando o teorema chinês do resto 
void tcr();

void print_TCR(long int **tabela_tcr, int s, long int x);

long int **aloca_matriz(int tam);

void libera_matriz(long int **matriz, int tam);

// long int verifica_tcr(long int **tabela, long int s, long int x);

// função que pula uma linha no printf
void new_line();

// função que exibe a mensagem de saída
void end_msg();
