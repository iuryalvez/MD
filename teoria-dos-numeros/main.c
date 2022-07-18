#include "teoria-dos-numeros.h"

int main () {
    setlocale(LC_ALL, "Portuguese");
    int i; // variável auxiliar
    long int op; // variável que armazena o valor da operação do menu
    long int n; // variável utilizada para armazenar um número n
    long int nums[2]; // variável que armazena dois números long int
    long int md, mdc; // md: maior divisor | mdc: maior divisor comum
    clear_screen();

    do {
        menu();
        scanf("%ld", &op);
        n = 0;
        nums[0] = 0; // inicialização para entrar em whiles de scanf
        nums[1] = 1; // inicialização para entrar em whiles de scanf
        switch (op) {
            case 1:
                new_line();
                printf("----- CRIVO DE ERATÓSTENES -----\n");
                printf("O crivo de eratóstenes calcula todos os números primos até o limitante escolhido\n");
                printf("Insira o número limite do crivo: ");
                while(n <= 1) { // ler enquanto nao inserir numero valido
                    scanf("%ld", &n);
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
                    scanf("%ld", &n);
                    if (n < 1) {
                        printf("Insira um número válido (>= 1)\n");
                        continue;
                    }
                    md = MD(n);
                    if (num_primo(n)) printf("O número é primo. Insira um número válido\n");
                    printf("O maior divisor de %ld é: %ld\n", n, md);
                }
                new_line();
                break;
            case 3:
                new_line();
                printf("----- MAIOR DIVISOR COMUM ENTRE DOIS NÚMEROS -----\n");
                for (i = 0; i < 2; i++) {
                    while (nums[i] < 2 || num_primo(nums[i])) {
                        printf("Insira o %iº número para ser calculado o mdc: ", i);
                        scanf("%ld", &nums[i]);
                        if (nums[i] < 1) {
                            printf("Insira um número válido (> 0)\n");
                            continue;
                        }
                        if (num_primo(nums[i]) == TRUE) printf("O número é primo, insira outro número:\n");
                    }
                }
                mdc = mdc_dois_numeros(nums[0], nums[1]);
                printf("O maior divisor comum de %ld e %ld é: %ld\n", nums[0], nums[1], mdc);
                new_line();
                break;
            case 4:
                new_line();
                printf("----- ÁRVORE DE FATORES -----\n");
                printf("A árvore de fatores vai encontrar os mínimos múltiplos comuns para o número escolhido.\n");
                printf("Insira o valor a ser calculado: ");

                while (n <= 1 || num_primo(n)) {
                    scanf("%ld", &n);
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
                for (i = 0; i < 2; i++) {
                    while (nums[i] <= 2) {
                        if (i < 1) printf("Insira o número 'n' (Z): "); 
                        else printf("Insira o número 'a': ");
                        scanf("%ld", &nums[i]);
                        if (nums[0] <= 2) printf("O número 'n' deve ser maior do que 2.\n");
                        if (i == 1) {
                            if (nums[1] <= 1) printf("O número 'a' deve ser maior que 1\n");
                            else if (nums[1] >= nums[0]) printf("O número 'a' deve ser menor que o número 'n'\n");
                            else if (nums[1] == 2) break;
                        }
                    }
                }       
                euclides(nums[0],nums[1]);
                new_line();
                break;
            case 6:
                new_line();
                printf("----- ALGORITMO DE EUCLIDES ESTENDIDO -----\n");
                for (i = 0; i < 2; i++) {
                    while (nums[i] <= 2) {
                        if (i < 1) printf("Insira o número 'n' (Z): "); 
                        else printf("Insira o número 'a': ");
                        scanf("%ld", &nums[i]);
                        if (nums[0] <= 2) printf("O número 'n' deve ser maior do que 2.\n");
                        if (i == 1) {
                            if (nums[1] <= 1) printf("O número 'a' deve ser maior que 1\n");
                            else if (nums[1] >= nums[0]) printf("O número 'a' deve ser menor que o número 'n'\n");
                            else if (nums[1] == 2) break;
                        }
                    }
                }
                euclides_estendido(nums[0],nums[1]);
                new_line();
                break;
            case 7:
                new_line();
                printf("----- EQUAÇÕES LINEARES MODULARES (\"a⊗ x = b em Zn\") -----\n");
                equacoes_lineares();
                new_line();
                break;
            case 8:
                new_line();
                printf("----- RESOLUÇÃO DE SISTEMAS (TEOREMA CHINÊS DO RESTO) -----\n");
                tcr();
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
