#include "teoria-dos-numeros.h"

int main () {
    setlocale(LC_ALL, "Portuguese");

    int op;
    int n, n1, n2;
    int md, mdc;
    clear_screen();

    do {
        menu();
        scanf("%d", &op);
        n = 0;
        n1 = 0;
        n2 = 0;
        switch (op) {
            case 1:
                new_line();
                printf("----- CRIVO DE ERATÓSTENES -----\n");
                printf("O crivo de eratóstenes calcula todos os números primos até o limitante escolhido\n");
                printf("Insira o número limite do crivo: ");
                while(n <= 1) { // ler enquanto nao inserir numero valido
                    scanf("%d", &n);
                    if (n <= 1) printf("Por favor, insira um número válido (> 1)\n");
                }                
                crivo_de_eratostenes(n);
                new_line();
                break;
            case 2:
                new_line();
                printf("----- MAIOR DIVISOR DE UM NÚMERO -----\n");
                printf("Insira o número para calcular seu MD: ");
                while(n < 1) {
                    scanf("%d", &n);
                    if (n < 1) {
                        printf("Insira um número válido (>= 1)\n");
                        continue;
                    }
                    md = MDC(n);
                    if (num_primo(n)) printf("O número é primo. Insira um número válido\n");
                    printf("O maior divisor de %d é: %d\n", n, md);
                }
                new_line();
                break;
            case 3:
                new_line();
                printf("----- MAIOR DIVISOR COMUM ENTRE DOIS NÚMEROS -----\n");
                printf("Insira o 1º número para ser calculado o mdc: ");
                while (n1 < 1 || num_primo(n1)) {
                    scanf("%d", &n1);
                    if (n1 < 1) {
                        printf("Insira um número válido (> 0)\n");
                        continue;
                    }
                    if (num_primo(n1) == TRUE) printf("O número é primo, insira outro número:\n");
                }
                printf("Insira o 2º número para ser calculado o mdc: ");
                while (n2 < 1 || num_primo(n2)) {
                    scanf("%d", &n2);
                    if (n2 < 1) {
                        printf("Insira um número válido (> 0)\n");
                        continue;
                    }
                    if (num_primo(n2) == TRUE) printf("O número é primo, insira outro número\n");
                }
                mdc = mdc_dois_numeros(n1, n2);
                printf("O maior divisor comum de %d e %d é: %d\n", n1, n2, mdc);
                new_line();
                break;
            case 4:
                new_line();
                printf("----- ÁRVORE DE FATORES -----\n");
                printf("A árvore de fatores vai encontrar os mínimos múltiplos comuns para o número escolhido.\n");
                printf("Insira o valor a ser calculado: ");

                while (n <= 1 || num_primo(n)) {
                    scanf("%d", &n);
                    if (n <= 1) {
                        printf("Insira um número válido (> 1)\n");
                        continue;
                    }
                    if (num_primo(n)) printf("O número inserido é primo, insira outro número.\n");
                }
                arvore_de_fatores(n);
                new_line();
                break;
            case 5:
                new_line();
                printf("----- ALGORITMO DE EUCLIDES -----\n");
                while (n1 < 2) {
                    printf("Insira o número 'n' (Z): ");
                    scanf("%d", &n1);
                    if (n1 < 2) printf("O número deve ser maior do que 1.\n");
                }
                while (n2 < 1 || n2 > n1) {
                    printf("Insira o número 'a': ");
                    scanf("%d", &n2);
                    if (n2 < 1 || n2 > n1) printf("O número deve ser maior do que 1 e menor do que 'a'.\n");
                }
                euclides(n1,n2);
                new_line();
                break;
            case 6:
                new_line();
                printf("----- ALGORITMO DE EUCLIDES ESTENDIDO -----\n");
                while (n1 < 2) {
                    printf("Insira o número 'n': ");
                    scanf("%d", &n1);
                    if (n1 < 2) printf("O número deve ser maior do que 1.\n");
                }
                while (n2 < 1 || n2 > n1) {
                    printf("Insira o número 'a': ");
                    scanf("%d", &n2);
                    if (n2 < 1 || n2 > n1) printf("O número deve ser maior do que 1 e menor do que 'n'.\n");
                }
                euclides_estendido(n1,n2);
                new_line();
                break;
            case 7:
                new_line();
                printf("----- EQUAÇÕES (\"a ⊗ x = b em Zn\") -----\n");
                resolve_equacoes();
                new_line();
                break;
            case 99:
                clear_screen();
                break;
            default:  
                if (op != 0) printf("Operação inválida.\n");
        }

    } while (op != 0);
    clear_screen();
    end_msg();
    return 0;
}
