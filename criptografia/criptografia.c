#include "criptografia.h"

void menu () {
    printf("CRIPTOGRAFIA\n");
    printf("1 -> Descobrir chave publica (RSA)\n");
    printf("2 -> Descobrir chave privada (RSA)\n");
    printf("3 -> Encriptar mensagem (RSA)\n");
    printf("4 -> Desencriptar mensagem (RSA)\n");
    printf("0 -> SAIR\n");
}

lli t_euclides_estendido(lli Zn, lli num) {
    lli *a, *b, *r, *q; // utilizando vetores para armazenar e calcular s e t futuramente
    lli t_final;
    a = (lli *) malloc(sizeof(lli)); // alocação padrão para armazenar UM lli por enquanto
    b = (lli *) malloc(sizeof(lli));
    q = (lli *) malloc(sizeof(lli));
    r = (lli *) malloc(sizeof(lli));
    lli cont = 0; // contador para ver quantas iterações há
    a[0] = Zn;
    b[0] = num;
    q[0] = Zn/num;
    r[0] = Zn%num;
    while (1) { // executando euclides para saber quantas iterações há para armazenarmos s e t em um vetor e printar depois
        cont++;
        if (r[cont-1] == 0) break; // importante: ver se o ultimo resto já é o mdc
        a = (lli *) realloc(a,sizeof(lli)*(cont+1)); // realocando memória para caber mais um elemento
        a[cont] = b[cont-1]; // o novo a é o antigo b 
        b = (lli *) realloc(b,sizeof(lli)*(cont+1));
        b[cont] = r[cont-1]; // o novo b é o antigo resto
        q = (lli *) realloc(q,sizeof(lli)*(cont+1));
        q[cont] = a[cont]/b[cont]; // o novo quociente
        r = (lli *) realloc(r,sizeof(lli)*(cont+1));
        r[cont] = a[cont] % b[cont]; // o novo resto
    }
    lli *s = (lli *) malloc(cont*sizeof(lli)); // alocação padrão para um lli
    lli *t = (lli *) malloc(cont*sizeof(lli));
    s[0] = 0; // início predefinido de s e t
    t[0] = 1;
    lli i = 1;
    while (i < cont) { // calcular s e t agora
        s[i] = t[i-1]; // fórmula do novo s
        t[i] = s[i-1] - (t[i-1]*q[cont-1-i]); // fórmula do novo t
        i++;
    }
    t_final = t[i-1];
    i = 0; // deve começar valendo 0 para o print
    printf("\t|iter.|    n    |    a    |  q  |   r   |   s   |   t   |\n"); // print formatado
    while (cont--) {
        printf("\t|%5lld|%9lld|%9lld|%5lld|%7lld|%7lld|%7lld|\n", i,a[i],b[i],q[i],r[i],s[cont],t[cont]);
        i++;
    }
    free(a);
    free(b);
    free(q);
    free(r);
    free(s);
    free(t); // liberando memória utilizada
    return t_final;
}

lli num_primo(lli n) {
    lli i; // divisor para saber se é primo
    lli cont = 0; // conta divisores
    for (i = 1; i <= n/2; i++) if (n % i == 0) cont++; // verificação até n/2 porque não há fatores maiores que n/2 
    if (cont == 1) return TRUE;
    else return FALSE;
}

lli num_inverso(lli n, lli t) {
    if (t < 0) t += n; // inverso = t mod n
    lli inv = t % n;
    return inv;
}

lli inverter(lli phi, lli num) {
    printf("\n\tPrecisamos calcular o t de %lld em Zphi(n)=%lld\n\n", num, phi);
    lli t = t_euclides_estendido(phi,num);
    printf("\n\tO t é %lld\n", t);
    printf("\tInverso = t mod phi(n)\n");
    lli inv = num_inverso(phi,t);
    return inv;
}

public_key chave_publica(private_key Apvt) {
    public_key T; // chave pública Temporária
    printf("\tTendo p e q, podemos calcular o phi(n): ");
    lli phi = (Apvt.p-1)*(Apvt.q-1);
    printf("%lld\n", phi);
    printf("\tCom o phi(n), descobrimos o 'e', já que 'e' é o inverso de 'd' em Zphi(n)\n");
    T.e = inverter(phi,Apvt.d); // encontrar o inverso de d em phi(n)
    T.n = Apvt.p*Apvt.q;
    printf("\tE(M) = M^%lld mod %lld\n", T.e, T.n); // fórmula de encriptar a mensagem
    return T;
}

private_key chave_privada(public_key B) {
    private_key T; // chave privada Temporária
    T.p = 2; // o p deve ser um divisor >= 2 pois '1' divide todos
    printf("\n\tPrecisamos achar os numeros p e q que resultam em %lld\n", B.n);
    while ((double)B.n/T.p != B.n/T.p) T.p++; // verificando se o número p é inteiro, se for, vai parar
    T.q = B.n/T.p; // se o primeiro valor foi divisível. então é só multiplicar p pelo valor q que encontraremos n 
    printf("\t(p,q) de 'B': (%lld,%lld)\n", T.p, T.q);
    printf("\tTendo p e q, podemos calcular o phi(n): ");
    lli phi = (T.p-1)*(T.q-1);
    printf("%lld\n", phi);
    printf("\tCom o phi(n), descobrimos o 'd', já que 'd' é o inverso de 'e' em Zphi(n)\n");
    T.d = inverter(phi,B.e);
    return T;
}

lli maior_potencia(lli expoente, lli maior_pot) {
    if(pow(2,maior_pot+1) > expoente) return maior_pot; // retorna a maior potencia de 2 que é menor que o expoente
    else return maior_potencia(expoente,maior_pot+1); // o expoente é o 'e' de M^e mod n
}

lli encriptar_RSA(public_key A, lli m) {
    lli *resultados; // vetor de resultados
    lli expo = A.e; // expoente temporário para atualizar e calcular a encriptação da mensagem
    lli maior_pot = 1; // potência de dois mais próxima do expoente temporário
    lli i; // variável auxiliar
    lli ant; // armazena o valor de um valor anterior

    printf("\tPrecisamos calcular E(M) = M^e mod n\n"); // fórmula de encriptação
    printf("\tIsto eh %lld^%lld mod %lld\n", m, A.e, A.n);
    printf("\t%lld^%lld mod %lld eh o mesmo que: ", m, A.e, A.n);
    while(expo>1){
        i = 1;
        i = maior_potencia(expo, i); // encontra a próxima maior potência de 2 antes do expoente atual
        if (expo == A.e) printf("%lld^%.0lf", m, pow(2,i)); // se for o primeiro, printamos sem o ⊗
        else printf("⊗ %lld^%.0lf", m, pow(2,i));
        expo = expo - pow(2, i); // ajusta o expoente ao próximo na lista de fatoração
    }
    if(A.e % 2 != 0) printf("⊗ %lld^1", m);
    printf("\n");

    expo = A.e; // redefinindo expo
    maior_pot = maior_potencia(expo, maior_pot); // recebe a maior potência de 2 mais próxima do expoente

    resultados = (lli *) calloc(sizeof(lli),maior_pot);

    ant = m; // valor m
    // o i vai percorrer o vetor de resultados e preenchê-lo com valores válidos
    for(i = 0; i < maior_pot; i++){
        resultados[i] = (ant*ant) % A.n; // dando valor para cada posição do vetor de resultados
        ant = resultados[i]; // atualizando para calcular o próximo com base no novo anterior
    }
    
    printf("\n\tVetor de resultados:\n"); // print apenas para verificar os valores
    for (i = 0; i < maior_pot; i++) printf("\t[%lld^%.0lf]: %lld\n", m, pow(2,i+1), resultados[i]);
    printf("\n");

    printf("\t%lld^%lld = ", m, A.e); // printando o valor que quero encontrar

    i = maior_pot-1; // i recebe a maior potencia-1 porque uma posição no vetor começa com 0
    ant = 1; // A variável começa com 1 para ser multiplicado pelo resultado na posição i do vetor

    while(expo>1){
        // printf("\t%lld^%.0lf = %lld\n", m, pow(2,i+1), resultados[i]); // Começo a lista dos valores que deverão ser multiplicados para se ter m^e
        // printf("ant * resultado[i] mod n = %lld * %lld mod %lld\n", ant, resultados[i], n);
        if (ant == 1) printf("%lld", resultados[i]); // se for o primeiro, printamos sem o ⊗
        else printf("⊗ %lld", resultados[i]);
        ant = (ant * resultados[i]) % A.n; // ant recebe os valores acumulados dos resultados válidos
        // printf("ant = %lld\n", ant);
        expo = expo - pow(2, i+1); // ajusta o expoente ao próximo na lista de fatoração, que está na posição i+1
        i = 1;
        i = maior_potencia(expo, i); // encontra a próxima maior potência de 2 antes do expoente atual
        i--; // i deve ser diminuído porque representa uma posição do vetor
    }

    if(A.e % 2 != 0) {
        printf("⊗ %lld", m);
        ant = (ant*m) % A.n;
    }
    printf("\n\t%lld^%lld = %lld\n\n", m, A.e, ant);

    return ant;
}
