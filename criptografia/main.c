#include "criptografia.c"

int main() {

    int op; // variável operador

    do {
        menu();
        scanf("%d", &op);
        
        // fazer as variáveis receberem números inválidos para entrar no loop de scanf
        
        switch (op) {
            case 1:
                printf("RSA\n");
                printf("...\n");
                break;
            default:
                if (op != 0) printf("Operacao invalida!\n");
        }
    } while (op != 0);

    return 0;
}