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

lli * resultados_N(lli n, lli tam, lli m) {
    lli *resultados = calloc(sizeof(lli),tam); // criando o vetor de resultados para ser retornado no final da função
    lli i; // variável auxiliar para percorrer o vetor
    lli ant = m; // ant vale m antes de chamar essa função, devemos armazenar esse valor para os printfs
    // o i vai percorrer o vetor de resultados e preenchê-lo com valores válidos
    for(i = 0; i < tam; i++){
        resultados[i] = (ant*ant) % n; // dando valor para cada posição do vetor de resultados
        ant = resultados[i]; // atualizando para calcular o próximo com base no novo anterior
    }
    
    printf("\n\tVetor de resultados:\n"); // print apenas para verificar os valores
    for (i = 0; i < tam; i++) printf("\t[%lld^%.0lf]: %lld\n", m, pow(2,i+1), resultados[i]);
    printf("\n");

    return resultados;
}

void print_potencias_validas(public_key A, lli m) {
    lli e_limite = A.e; // e_limite é o expoente temporário para calcular quais potencias são válidas
    lli i;
    printf("\t%lld^%lld mod %lld eh o mesmo que: ", m, A.e, A.n);
    while(e_limite>1){
        i = 1;
        i = maior_potencia(e_limite, i); // encontra a próxima maior potência de 2 antes do expoente atual
        if (e_limite == A.e) printf("%lld^%.0lf", m, pow(2,i)); // se for o primeiro, printamos sem o ⊗
        else printf("⊗ %lld^%.0lf", m, pow(2,i));
        e_limite = e_limite - pow(2, i); // ajusta o expoente ao próximo na lista de fatoração
    }
    if(A.e % 2 != 0) printf("⊗ %lld^1", m);
    printf("\n");
}

lli multiplicacoes_modulares(lli n, lli e, lli *resultados, lli m) {
    lli e_limite = e; // expoente temporário que indica o limite das potencias
    lli ant = 1; // variável que armazena o valor anterior
    lli i; // auxiliar que calculará as maiores potências

    printf("\t%lld^%lld = ", m, e); // printando o valor que quero encontrar
    while(e_limite>1){
        i = 1; // atualizando i para somarmos ele e encontrar a nova maior potência
        i = maior_potencia(e_limite, i); // encontra a próxima maior potência de 2 antes do expoente atual
        i--; // o vetor é do tamanho da verdadeira maior potência, então para acessar a ultima posição devemos diminuir em 1
        // começamos a multiplicação dos valores válidos que deverão ser multiplicados para se ter m^e
        if (ant == 1) printf("%lld", resultados[i]); // se for o primeiro, printamos sem o ⊗
        else printf("⊗ %lld", resultados[i]);
        ant = (ant * resultados[i]) % n; // ant recebe os valores acumulados dos resultados válidos
        // printf("ant = %lld\n", ant);
        e_limite = e_limite - pow(2, i+1); // ajusta o expoente ao próximo na lista de fatoração, +1 porque diminuímos 1 antes
    }
    if(e % 2 != 0) { // se for ímpar, devemos executar o caso de multiplicar por M^1
        printf("⊗ %lld", m);
        ant = (ant*m) % n;
    }
    printf("\n\t%lld^%lld = %lld\n\n", m, e, ant); // valor das multiplicações
    return ant;
}

lli encriptar_RSA(public_key A, lli m) {
    lli *resultados = NULL; // vetor de resultados
    lli maior_pot = 1; // potência de dois mais próxima do expoente da chave pública, também é o tamanho do nosso vetor de resultados
    lli res;

    printf("\tPrecisamos calcular E(M) = M^e mod n\n"); // fórmula de encriptação
    printf("\tIsto eh %lld^%lld mod %lld\n", m, A.e, A.n);
    
    print_potencias_validas(A,m);

    maior_pot = maior_potencia(A.e, maior_pot); // recebe a maior potência de 2 mais próxima do expoente

    resultados = resultados_N(A.n, maior_pot, m); // calculando o vetor de potências

    res = multiplicacoes_modulares(A.n,A.e,resultados,m); // calculando o valor das multiplicações modulares das potências válidas

    return res;
}

lli desencriptar_RSA (private_key Apvt, lli N) {
    
    lli n = Apvt.p * Apvt.q;
    lli msg;

    printf("\n\tD(N) = N^d mod n, ou seja -> D(%lld) = %lld^%lld mod %lld\n", N, N, Apvt.d, N);
    printf("\tDevemos calcular\n");
    printf("\t1 - (N mod p)^(d mod p-1) mod p -> (%lld mod %lld)^(%lld mod %lld) mod %lld\n", N, Apvt.p, Apvt.d, Apvt.p-1, Apvt.p);
    printf("\t2 - (N mod q)^(d mod q-1) mod q -> (%lld mod %lld)^(%lld mod %lld) mod %lld\n", N, Apvt.q, Apvt.d, Apvt.q-1, Apvt.q);
    
    lli n1 = N % Apvt.p; // n da equação 1
    lli e1 = Apvt.d % (Apvt.p-1); // expoente da equação 1
    lli n2 = N % Apvt.q; // n da equacao 2
    lli e2 = Apvt.d % (Apvt.q-1);  // expoente da equação 2

    printf("\tResolvendo os mod...\n");
    printf("\t1 - (%lld)^%lld mod %lld\n", n1, e1, Apvt.p);
    printf("\t2 - (%lld)^%lld mod %lld\n", n2, e2, Apvt.q);
    printf("\tAgora precisamos calcular o valor dessas potências\n");
    
    printf("\tPara equacao 1:\n");
    lli *r1 = resultados_N(Apvt.p,maior_potencia(e1,1),n1); // vetor de resultados de 1
    lli v1 = multiplicacoes_modulares(Apvt.p,e1,r1,n1); // retornar o valor das mult.

    printf("\tPara equacao 2:\n");
    lli *r2 = resultados_N(Apvt.q,maior_potencia(e2,1),n2); // vetor de resultados de 2
    lli v2 = multiplicacoes_modulares(Apvt.q,e2,r2,n2); // retornar o valor das mult.

    printf("\tAgora precisamos resolver o sistema de equacoes lineares modulares:\n");
    
    msg = tcr(v1, v2, Apvt.p, Apvt.q); // retorna o valor calculado no TCR

    return msg;
}

lli tcr(lli a1, lli a2, lli p, lli q) {
    int s = 2; // s = número de sistemas
    int i, j; // i,j são variáveis auxiliares
    
    /*
    uma matriz que armazena os números de cada sistema 
    1. tabela_tcr[0][i] = ai;
    2. tabela_tcr[1][i] = mi;
    3. tabela_tcr[2][i] = Mi;
    4. tabela_tcr[3][i] = xi;
    5. tabela_tcr[4][i] = yi = inverso de xi;
    6. tabela_tcr[5][i] = ai*Mi*yi;
    7. tabela_tcr[6][i] = (ai*Mi*yi) mod m;
    8. tabela_tcr[7][i] = + modular;
    */
   
    lli tabela_tcr[7][2];
    lli m = p*q; // número que armazena o m (m1*m2*m3*...*mi)
    
    /* 
     * 1. Mi = (m/mi);
     * 2. xi = Mi mod mi;
     * 3. yi = o inverso de xi em Zmi;
     * 4. solução de x = somatório de i = 1 indo até um número t calculando (ai * Mi * yi) mod m.
    */

    tabela_tcr[0][0] = a1; // armazenando a1 
    tabela_tcr[0][1] = a2; // armazenando a2

    tabela_tcr[1][1] = p; // armazenando m1
    tabela_tcr[1][2] = q; // armazenando m2
    
    // Para saber se tem solução, precisamos saber se o mdc entre
    // todos os números é 1, ou seja, se são primos entre si.
    
    for (i = 0; i < s; i++) {
        for (j = i+1; j < s; j++) {
            if (mdc_dois_numeros(tabela_tcr[1][i],tabela_tcr[1][j]) != 1) {
                printf("Os mi's não são primos entre si, o sistema não possui soluções\n");
                return FALSE;
            }
        }
    }
    // printf("m: %ld\n", m);
    for (i = 0; i < s; i++) { // calculando Mi (Mi = m/mi)
        tabela_tcr[2][i] = m/(double)tabela_tcr[1][i]; 
        // printf("M%i = %ld/%ld\n", i, m, tabela_tcr[2][i]); 
    }
    for (i = 0; i < s; i++) { // calculando xi
        tabela_tcr[3][i] = tabela_tcr[2][i] % tabela_tcr[1][i];
        // printf("x%d = %ld\n", i, tabela_tcr[3][i]);
    }

    lli t; // variável que armazena o t de euclides estendido (mi,xi)
    
    for (i = 0; i < s; i++) { // calculando yi, o inverso de xi em Zmi
        t = t_euclides_estendido(tabela_tcr[1][i],tabela_tcr[3][i]); // t de euclides estendido
        // printf("t de m%d,x%d: %ld\n", i, i, t);
        tabela_tcr[4][i] = num_inverso(tabela_tcr[1][i],t); // número inverso de xi em Zmi
        // printf("y%d: %ld\n",i,tabela_tcr[4][i]);
    }
    for (i = 0; i < s; i++) { // calculando ai*Mi*yi
        tabela_tcr[5][i] = tabela_tcr[0][i]*tabela_tcr[2][i]*tabela_tcr[4][i];
    }
    for (i = 0; i < s; i++) { // calculando (ai*Mi*yi) mod m
        tabela_tcr[6][i] = tabela_tcr[5][i] % m;
        if (tabela_tcr[6][i] < 0) tabela_tcr[6][i] += m;
    }

    lli x = 0; // a solução do sistema
    
    for (i = 0; i < s; i++) x = (x + tabela_tcr[6][i]) % m;
    
    print_TCR(tabela_tcr,s,x);
    return x;    
}

void print_TCR(lli tabela_tcr[7][2], int s, lli x) {
    int i;
    printf("i              |");
    for (i = 0; i < s; i++) printf("%10d|", i);
    printf("\n");
    printf("ai             |");
    for (i = 0; i < s; i++) printf("%10lld|", tabela_tcr[0][i]);
    printf("\n");
    printf("mi             |");
    for (i = 0; i < s; i++) printf("%10lld|", tabela_tcr[1][i]);
    printf("\n");
    printf("Mi = m/mi      |");
    for (i = 0; i < s; i++) printf("%10lld|", tabela_tcr[2][i]);
    printf("\n");
    printf("xi = Mi mod mi |");
    for (i = 0; i < s; i++) printf("%10lld|", tabela_tcr[3][i]);
    printf("\n");
    printf("yi = (xi)-¹    |");
    for (i = 0; i < s; i++) printf("%10lld|", tabela_tcr[4][i]);
    printf("\n");
    printf("ai*Mi*yi       |");
    for (i = 0; i < s; i++) printf("%10lld|", tabela_tcr[5][i]);
    printf("\n");
    printf("ai*Mi*yi mod m |");
    for (i = 0; i < s; i++) printf("%10lld|", tabela_tcr[6][i]);
    printf("\n");
    printf("x0             |%10lld|",x);
}

lli maior_numero (lli n1, lli n2) { // maior número entre dois números
    lli maior = (n1 > n2) ? n1 : n2;
    return maior;
}

lli mdc_dois_numeros(lli n1, lli n2) {
    lli i, mdc;
    lli maior;
    // if (num_primo(n1) == TRUE) {
    //     printf("O primeiro número é primo.\n");
    //     if (num_primo(n2) == TRUE) printf("O segundo número é primo.\n");    
    //     return FALSE;
    // }
    // if (num_primo(n2) == TRUE) printf("O segundo número é primo.\n"); // i deve ser diferente de n1 e n2 pq não sabemos se um dos dois números é fator do outro
    maior = maior_numero(n1,n2);
    for (i = 1; i <= maior/2; i++) if (n1 % i == 0 && n2 % i == 0 && (i != n1 || i != n2)) mdc = i; // verificação simultânea dos divisores, vai atualizar sempre que encontrar um número que divide os dois
    return mdc;
}
