#include "criptografia.h"

/*
gcc criptografia.c main.c -o criptografia.exe -lm
./criptografia.exe


37 43 445
2491 255
1492
*/

int main() {

    int op; // variável operador
    private_key Apvt, Bpvt; // chaves privadas de Ana e Beto
    public_key A, B; // chaves públicas de Ana e Beto
    lli phi; // phi(n) = (p-1)*(q-1)

    lli M; // mensagem que será encriptada
 
    do {
        menu();
        scanf("%d", &op);
        
        // fazer as variáveis receberem números inválidos para entrar no loop de scanf
        
        switch (op) {
            case 1:
                printf("\nRSA - Descobrir chave publica\n");
                printf("Chave privada de Ana: (p,q,d)\n"); // ler 3 números seguidos
                scanf("%lld %lld %lld", &Apvt.p, &Apvt.q, &Apvt.d);
                A = chave_publica(Apvt);
                printf("\tO inverso de 'd' eh '%lld' que eh o 'e' que queriamos.\n", A.e);
                printf("\tChave publica de Ana = (n,e) = (%lld,%lld)\n\n", A.n, A.e);
                break;
            case 2: 
                printf("\nRSA - Descobrir chave privada\n");
                printf("Chave publica de Beto: (n,e)\n"); // ler 2 números seguidos
                scanf("%lld %lld", &B.n, &B.e);
                Bpvt = chave_privada(B); // passar o n de Beto, será fatorado e vamos descobrir o p e o q
                printf("\tO inverso de 'e' eh '%lld' que eh o 'd' que queriamos.\n", Bpvt.d);
                printf("\tChave privada de Beto: (p,q,d) = (%lld,%lld,%lld)\n\n", Bpvt.p, Bpvt.q, Bpvt.d);
                break;
            case 3:
                printf("\nRSA - Encriptar\n");
                printf("Chave privada de Ana: (p,q,d)\n");
                scanf("%lld %lld %lld", &Apvt.p, &Apvt.q, &Apvt.d);
                printf("Informe a mensagem que sera encriptada: (M)\n");
                scanf("%lld", &M);
                printf("\tPara encontrar o e da chave pública de Ana: ");
                phi = (Apvt.p-1)*(Apvt.q-1);
                A.e = inverter(phi,Apvt.d); // Temos que encontrar o e da Ana pra poder encriptar
                printf("\n\tUsando p=%lld, q=%lld, e=%lld para encriptar %lld:\n", Apvt.p, Apvt.q, A.e, M);
                encriptar_RSA(Apvt.p, Apvt.q, A.e, M);
                break;
            case 4:
                printf("\nRSA - Desencriptar\n");
                break;
            default:
                if (op != 0) printf("Operacao invalida!\n");
        }
    } while (op != 0);

    return 0;
}