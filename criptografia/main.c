#include "criptografia.h"

/*
gcc criptografia.c main.c -o criptografia.exe -lm
./criptografia.exe
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
                while (num_primo(Apvt.p)==FALSE || num_primo(Apvt.q)==FALSE){ //Verifica se os numeros p e q inseridos são primos
                    printf("Os numeros da chave privada precisam ser primos!\n");
                    scanf("%lld %lld %lld", &Apvt.p, &Apvt.q, &Apvt.d);
                }
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
                printf("\nRSA - Encriptar mensagem\n");
                printf("Chave publica do destinatario para encriptarmos: (n,e)\n");
                scanf("%lld %lld", &B.n, &B.e);
                printf("Informe a mensagem que sera encriptada: (M)\n");
                scanf("%lld", &M);
                printf("A mensagem sera assinada?\n");
                while (1) {
                    printf("1 - Sim\n2 - Nao\n");
                    scanf("%d", &opc);
                    if (opc == 1 || opc == 2) break;
                    printf("Opcao invalida!\n");
                }
                if (opc == 1) {
                    printf("Para assinar M, precisamos desencriptar M antes de encriptar para o destinatario\n");
                    printf("Chave privada do remetente: (p,q,d)\n");
                    scanf("%lld %lld %lld", &Apvt.p, &Apvt.q, &Apvt.d);
                    M = desencriptar_RSA(Apvt, M);
                    printf("\tN = D(E(M))\n");
                    printf("\tA mensagem assinada eh: %lld\n", M);
                }
                printf("\n\tUsando (n,e) = (%lld,%lld) para encriptar %lld:\n", B.n, B.e, M);
                M = encriptar_RSA(B, M);
                printf("\tA mensagem encriptada eh: %lld\n\n", M);
                break;
            case 4:
                printf("\nRSA - Desencriptar mensagem\n");
                printf("Chave privada do destinatario: (p,q,d)\n");
                scanf("%lld %lld %lld", &Apvt.p, &Apvt.q, &Apvt.d);
                printf("Mensagem que sera desencriptada:\n");
                scanf("%lld", &M);
                printf("A mensagem foi assinada?\n");
                while (1) {
                    printf("1 - Sim\n2 - Nao\n");
                    scanf("%d", &opc);
                    if (opc == 1 || opc == 2) break;
                    printf("Opcao invalida!\n");
                }
                M = desencriptar_RSA(Apvt, M);
                if (opc == 1) {
                    printf("Ja que a mensagem foi assinada, ela foi desencriptada com a chave privada do remetente\n");
                    printf("Encriptaremos ela com a chave publica do remetente para voltar a mensagem original encriptada\n");
                    printf("Chave publica do remetente (n,e):\n");
                    scanf("%lld %lld", &B.n, &B.e);
                    printf("\tN = D(E(M))\n");
                    M = encriptar_RSA(B, M);
                    printf("\tA mensagem que precisamos desencriptar eh: %lld\n", M);
                }
                printf("\tLogo, a mensagem desencriptada eh: %lld\n\n", M);
                break;
            default:
                if (op != 0) printf("Operacao invalida!\n");
        }
    } while (op != 0);

    return 0;
}
