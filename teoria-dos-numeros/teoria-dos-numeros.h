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

void clear_screen();

void menu();

void crivo_de_eratostenes(int n);

int num_primo(int n);

int mdc_dois_numeros(int n1, int n2);

int MDC(int n);

void arvore_de_fatores(int n);

void euclides(int a, int b);

void euclides_estendido(int a, int b);

int maior_numero(int n1, int n2);

void end_msg();
