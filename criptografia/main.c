#include "criptografia.h"

/*
gcc criptografia.c main.c -o criptografia.exe -lm
./criptografia.exe


37 43 445
2491 255
1492
*/

int main() {

    int op, opc; // variável operador
    private_key Apvt, Bpvt; // chaves privadas de Ana e Beto
    public_key A, B; // chaves públicas de Ana e Beto
    lli M; // mensagem que será encriptada
 
    do {
        menu();
        scanf("%d", &op);
        
        // fazer as variáveis receberem números inválidos para entrar no loop de scanf
        opc = 0;
        switch (op) {
            case 1:
                printf("\nRSA - Descobrir chave publica\n");
                printf("Chave privada de 'A': (p,q,d)\n"); // ler 3 números seguidos
                scanf("%lld %lld %lld", &Apvt.p, &Apvt.q, &Apvt.d);
                A = chave_publica(Apvt);
                printf("\tO inverso de 'd' eh '%lld' que eh o 'e' que queriamos.\n", A.e);
                printf("\tA chave publica de 'A' eh = (n,e) = (%lld,%lld)\n\n", A.n, A.e);
                break;
            case 2: 
                printf("\nRSA - Descobrir chave privada\n");
                printf("Chave publica de 'B': (n,e)\n"); // ler 2 números seguidos
                scanf("%lld %lld", &B.n, &B.e);
                Bpvt = chave_privada(B); // passar o n de Beto, será fatorado e vamos descobrir o p e o q
                printf("\tO inverso de 'e' eh '%lld' que eh o 'd' que queriamos.\n", Bpvt.d);
                printf("\tA chave privada de 'B' eh = (p,q,d) = (%lld,%lld,%lld)\n\n", Bpvt.p, Bpvt.q, Bpvt.d);
                break;
            case 3:
                printf("\nRSA - Encriptar mensagem de 'A' para 'B'\n");
                printf("Chave publica de 'B': (n,e)\n");
                scanf("%lld %lld", &B.n, &B.e);
                printf("Informe a mensagem que sera encriptada: (M)\n");
                scanf("%lld", &M);
                printf("\n\tUsando (n,e) = (%lld,%lld) para encriptar %lld:\n", B.n, B.e, M);
                M = encriptar_RSA(B, M);
                printf("\tA mensagem encriptada de 'A' para 'B' eh: %lld\n\n", M);
                break;
            case 4:
                printf("\nRSA - Desencriptar mensagem de 'B' para 'A'\n");
                printf("Chave privada de 'A': (p,q,d)\n");
                scanf("%lld %lld %lld", &Apvt.p, &Apvt.q, &Apvt.d);
                printf("Mensagem que sera desencriptada:\n");
                scanf("%lld", &M);
                M = desencriptar_RSA(Apvt, M);
                printf("\tA mensagem desencriptada eh: %lld\n", M);
                break;
            default:
                if (op != 0) printf("Operacao invalida!\n");
        }
    } while (op != 0);

    return 0;
}