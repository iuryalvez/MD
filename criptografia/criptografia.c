#include "criptografia.h"

void menu () {
    printf("CRIPTOGRAFIA\n");
    printf("1 -> Descobrir chave publica (RSA)\n");
    printf("2 -> Descobrir chave privada (RSA)\n");
    printf("3 -> Encriptar mensagem (RSA)\n");
    printf("4 -> Desencriptar mensagem (RSA)\n");
    printf("0 -> SAIR\n");
}

lli t_euclides_estendido(lli n1, lli n2) {
    lli *a, *b, *r, *q; // utilizando vetores para armazenar e calcular s e t futuramente
    lli t_final;
    a = (lli *) malloc(sizeof(lli)); // alocação padrão para armazenar UM lli por enquanto
    b = (lli *) malloc(sizeof(lli));
    q = (lli *) malloc(sizeof(lli));
    r = (lli *) malloc(sizeof(lli));
    lli cont = 0; // contador para ver quantas iterações há
    a[0] = n1;
    b[0] = n2;
    q[0] = n1/n2;
    r[0] = n1%n2;
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
    i = 0; 
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
    if (t < 0) t += n;
    lli inv = t % n;
    return inv;
}

lli inverter(lli phi, lli num) {
    printf("\n\tPrecisamos calcular o t de %lld em Z%lld\n\n", num, phi);
    lli t = t_euclides_estendido(phi,num);
    printf("\n\tO t é %lld\n", t);
    printf("\te^-1 = t mod phi(n)\n");
    lli inv = num_inverso(phi,t);
    printf("\tO inverso eh '%lld'\n", inv);
    return inv;
}

private_key chave_privada(public_key B) {
    private_key T;
    T.p = 2;
    printf("\n\tPrecisamos achar os numeros p e q que resultam em %lld\n", B.n);
    while ((double)B.n/T.p != B.n/T.p) T.p++; // verificando se o número p é inteiro, se for, vai parar
    T.q = B.n/T.p; // se o primeiro valor foi divisível. então é só multiplicar p pelo valor q que encontraremos n 
    printf("\t(p,q) de Beto: (%lld,%lld)\n", T.p, T.q);
    printf("\tTendo p e q, podemos calcular o phi(n): ");
    lli phi = (T.p-1)*(T.q-1);
    printf("%lld\n", phi);
    printf("\tCom o phi(n), descobrimos o d, já que d é o inverso de e em phi(n)\n");
    T.d = inverter(phi,B.e);
    return T;
}

lli maior_potencia(lli expoente, lli maior_pot) {
    if(pow(2,maior_pot+1) > expoente) return maior_pot;
    else return maior_potencia(expoente,maior_pot+1);
}

lli encriptar_RSA(lli p, lli q, lli e, lli m) {

    lli *resultados; // vetor de resultados
    lli n = p * q; // n de Zn
    lli expo = e; // expoente temporário para atualizar e calcular a encriptação da mensagem
    lli maior_pot = 1; // potência de dois mais próxima do expoente temporário
    lli i; // variável auxiliar
    lli ant; // armazena o valor de um valor anterior

    maior_pot = maior_potencia(expo, maior_pot);

    resultados = (lli *) calloc(sizeof(lli),maior_pot);

    ant = m; // valor m
    // o i vai percorrer o vetor de resultados e preenchê-lo com valores válidos
    for(i = 0; i < maior_pot; i++){
        resultados[i] = (ant*ant) % n; // dando valor para cada posição do vetor de resultados
        ant = resultados[i]; // atualizando para calcular o próximo com base no novo anterior
    }
    
    printf("VETOR DE RESULTADOS:\n"); // print apenas para verificar os valores
    for (i = 0; i < maior_pot; i++) printf("\t[%lld^%.0lf]: %lld\n", m, pow(2,i+1), resultados[i]);
    printf("\n");

    printf("%lld^%lld = ", m, e); // printando o valor que quero encontrar

    i = maior_pot-1; // i recebe a maior potencia-1 porque uma posição no vetor começa com 0
    ant = 1; // A variável começa com 1 para ser multiplicado pelo resultado na posição i do vetor

    while(expo>0){
        printf("%lld * \n", resultados[i]); // Começo a lista dos valores que deverão ser multiplicados para se ter m^e
        ant = ant * resultados[i];
        expo = expo - pow(2, i+1); // ajusta o expoente ao próximo na lista de fatoração, que está na posição i+1
        i = maior_potencia(expo, i); // encontra a próxima maior potência de 2 antes do expoente atual
        printf("expo = %lld i = %lld\n", expo, i);
    }



    /*
    i = maior_pot-1; // i recebe a maior potencia-1 porque uma posição no vetor começa com 0
    ant = resultados[i] % n; // primeiro valor a ser somado para descobrir a mensagem encriptada
    expo = expo-pow(2,i); // atualizando o expoente (quando for reduzido a 0 é porque acabou)

    printf("%lld^%lld = ", m, e); // printando o valor que quero encontrar
    printf("%lld^%lf ", m, pow(2,i)); // printando o valor de m elevado a uma potência próxima mais a outra...

    while(expo!=0){
        i = 1;
        i = maior_potencia(expo, i); // i recebe a maior potência do novo expoente
        ant = (ant * resultados[i]) % n; // ant recebe os valores acumulados dos resultados válidos
        expo = expo-pow(2,i); // atualizando o expoente para o próximo cálculo
        
        //printf("+%% %lld^%lf", m, pow(2,i));
        if (expo == 0) printf("\n");
    }
    */

    return ant;
}