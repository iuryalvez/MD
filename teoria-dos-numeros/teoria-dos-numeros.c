#include "teoria-dos-numeros.h"

void clear_screen() {
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else

    #endif
}

void menu() {
    printf("TEORIA DOS NÚMEROS\n");
    printf("1  ->  CRIVO DE ERATÓSTENES\n");
    printf("2  ->  MAIOR DIVISOR DE UM NÚMERO\n");
    printf("3  ->  MAIOR DIVISOR COMUM ENTRE DOIS NÚMEROS\n");
    printf("4  ->  ÁRVORE DE FATORES\n");
    printf("5  ->  ALGORITMO DE EUCLIDES\n");
    printf("6  ->  ALGORITMO DE EUCLIDES ESTENDIDO\n");
    printf("7  ->  RESOLVER EQUAÇÃO LINEAR MODULAR \"a⊗ x = b em Zn\"\n");
    printf("8  ->  RESOLUÇÃO DE SISTEMAS (TEOREMA CHINÊS DO RESTO)\n");
    printf("99 ->  LIMPAR A TELA\n");
    printf("0  ->  SAIR\n");
}

void crivo_de_eratostenes(long int n) {
    int i, cont = 0, check = 0; // i eh meu percorredor, cont eh meu contador de primos
    for(i = 1; i < n; i++) { // ler todos os numeros ate 'n'
        if (num_primo(i) == TRUE) { // verifica se o numero é primo
            printf("%5d |", i);
            cont++;
            if (cont % 10 == 0) check = 1; // checar para pular linha
        }
        if (check == 1) printf("\n");
        check = 0;
    }
    printf("\nTotal de números primos encontrados: %d\n", cont);
}

long int num_primo(long int n) {
    long int i; // divisor para saber se é primo
    int cont = 0; // conta divisores
    for (i = 1; i <= n/2; i++) if (n % i == 0) cont++; // verificação até n/2 porque não há fatores maiores que n/2 
    if (cont == 1) return TRUE;
    else return FALSE;
}

long int mdc_dois_numeros(long int n1, long int n2) { // euclides recursivo
    if (n1 < n2) {
        long int temp = n1;
        n1 = n2;
        n2 = temp;
    }
    if (n2 == 0) return n1;
    else return mdc_dois_numeros(n2, n1 % n2);
}

long int MD(long int n) {
    long int i, mdc;
    for (i = 1; i < n/2; i++) {
        if (n % i == 0) mdc = i;
    }
    return mdc;
}

void arvore_de_fatores(long int n) {
    long int divisor = 2; // inicializar com 2 porque 1 divide todos
    long int expoente = 0; // expoente padrão
    printf("%ld = ", n); // primeiro print que é o número original
    while (n != 0) { // enquanto não chegarmos em n = 1, não vamos parar de dividí-lo
        if (n % divisor == 0) {
            n /= divisor; // se for um divisor, precisamos dividir n
            expoente++; // somar um ao expoente pq encontramos um fator
        }
        else { // se não for divisor
            if (expoente > 0) { // ver se encontramos um divisor antes, pq aí o expoente vai estar maior que 0 que é o padrão
                if (expoente == 1) printf("%ld ", divisor); // se estiver igual a 1, então não precisamos printar ele elevado a 1
                else printf("%ld^%ld ", divisor, expoente); // se não, é maior que um e printa o número e sua potência
                if (n != 1) printf("* ");  // se o número não for o último, printa o sinal de multiplicação
            }
            if (n == 1) break;
            divisor++; // soma mais um ao divisor para encontrar o próximo
            expoente = 0; // retorna o expoente ao padrão 0
        }
    }
    printf("\n");
}

void euclides(long int a, long int b) {
    long int n1 = a, n2 = b; // armazenando os números originais para printar no final
    long int r = a % b, q = a/b; // primeira linha -> r é o resto, q é o quociente de a por b
    printf("|   n   |   a   |   q   |  r  |\n");
    while (1) {
        printf("|%7ld|%7ld| %5ld |%5ld|\n", a, b, q, r); // printando primeiro pq vão ser atualizados daqui pra frente
        if (r == 0) { // condição de parada depois do printf pois imprimimos quando r é 0 também
            printf("mdc(%ld,%ld) = %ld\n", n1, n2, b); // maior divisor comum entre os dois números, o b da última linha
            break;
        }
        a = b; // a se torna o b
        b = r; // b se torna o resto
        q = a/b; // novo quociente
        r = a % b; // resto dos novos a e b
    } // repete até r == 0
}

void euclides_estendido(long int n1, long int n2) {
    long int *a, *b, *r, *q; // utilizando vetores para armazenar e calcular s e t futuramente
    a = (long int *) malloc(sizeof(long int)); // alocação padrão para armazenar UM long int por enquanto
    b = (long int *) malloc(sizeof(long int));
    q = (long int *) malloc(sizeof(long int));
    r = (long int *) malloc(sizeof(long int));
    long int cont = 0; // contador para ver quantas iterações há
    a[0] = n1;
    b[0] = n2;
    q[0] = n1/n2;
    r[0] = n1%n2;
    while (1) { // executando euclides para saber quantas iterações há para armazenarmos s e t em um vetor e printar depois
        cont++;
        if (r[cont-1] == 0) break; // importante: ver se o ultimo resto já é o mdc
        a = (long int *) realloc(a,sizeof(long int)*(cont+1)); // realocando memória para caber mais um elemento
        a[cont] = b[cont-1]; // o novo a é o antigo b 
        b = (long int *) realloc(b,sizeof(long int)*(cont+1));
        b[cont] = r[cont-1]; // o novo b é o antigo resto
        q = (long int *) realloc(q,sizeof(long int)*(cont+1));
        q[cont] = a[cont]/b[cont]; // o novo quociente
        r = (long int *) realloc(r,sizeof(long int)*(cont+1));
        r[cont] = a[cont] % b[cont]; // o novo resto
    }
    long int *s = (long int *) malloc(cont*sizeof(long int)); // alocação padrão para um long int
    long int *t = (long int *) malloc(cont*sizeof(long int));
    s[0] = 0; // início predefinido de s e t
    t[0] = 1;
    long int i = 1;
    while (i < cont) { // calcular s e t agora
        s[i] = t[i-1]; // fórmula do novo s
        t[i] = s[i-1] - (t[i-1]*q[cont-1-i]); // fórmula do novo t
        i++;
    }
    i = 0;
    printf("|iter.|    n    |    a    |  q  |   r   |   s   |   t   |\n"); // print formatado
    while (cont--) {
        printf("|%5ld|%9ld|%9ld|%5ld|%7ld|%7ld|%7ld|\n", i,a[i],b[i],q[i],r[i],s[cont],t[cont]);
        i++;
    } 
    free(a);
    free(b);
    free(q);
    free(r);
    free(s);
    free(t); // liberando memória utilizada
}

long int t_euclides_estendido(long int n1, long int n2) {
    long int *a, *b, *r, *q; // utilizando vetores para armazenar e calcular s e t futuramente
    long int t_final;
    a = (long int *) malloc(sizeof(long int)); // alocação padrão para armazenar UM long int por enquanto
    b = (long int *) malloc(sizeof(long int));
    q = (long int *) malloc(sizeof(long int));
    r = (long int *) malloc(sizeof(long int));
    long int cont = 0; // contador para ver quantas iterações há
    a[0] = n1;
    b[0] = n2;
    q[0] = n1/n2;
    r[0] = n1%n2;
    while (1) { // executando euclides para saber quantas iterações há para armazenarmos s e t em um vetor e printar depois
        cont++;
        if (r[cont-1] == 0) break; // importante: ver se o ultimo resto já é o mdc
        a = (long int *) realloc(a,sizeof(long int)*(cont+1)); // realocando memória para caber mais um elemento
        a[cont] = b[cont-1]; // o novo a é o antigo b 
        b = (long int *) realloc(b,sizeof(long int)*(cont+1));
        b[cont] = r[cont-1]; // o novo b é o antigo resto
        q = (long int *) realloc(q,sizeof(long int)*(cont+1));
        q[cont] = a[cont]/b[cont]; // o novo quociente
        r = (long int *) realloc(r,sizeof(long int)*(cont+1));
        r[cont] = a[cont] % b[cont]; // o novo resto
    }
    long int *s = (long int *) malloc(cont*sizeof(long int)); // alocação padrão para um long int
    long int *t = (long int *) malloc(cont*sizeof(long int));
    s[0] = 0; // início predefinido de s e t
    t[0] = 1;
    long int i = 1;
    while (i < cont) { // calcular s e t agora
        s[i] = t[i-1]; // fórmula do novo s
        t[i] = s[i-1] - (t[i-1]*q[cont-1-i]); // fórmula do novo t
        i++;
    }
    t_final = t[i-1]; 
    free(a);
    free(b);
    free(q);
    free(r);
    free(s);
    free(t); // liberando memória utilizada
    return t_final;
}

void equacoes_lineares() {
    long int a = 0, b = 0, n = 0; // a, b, n são números da equação linear modular
    long int x, x0; // x e x0 são as soluções da equação
    long int mdc, t, i, inv; // t de euclides, i é um contador, inv é o número inverso
    while (n < 2) {
        printf("Insira o número 'n': ");
        scanf("%ld", &n);
        if (n < 2) printf("O número deve ser maior do que 1.\n");
    }
    while (a < 1 || a > n) {
        printf("Insira o 'a': "); // a X x = b
        scanf("%ld", &a);
        if (a < 1 || a > n) printf("O número deve ser maior do que 1 e menor do que 'n'.\n");
    }
    while (b < 1 || b > n) {
        printf("Insira o 'b': "); // a X x = b
        scanf("%ld", &b);
        if (b < 1 || b > n) printf("O número deve ser maior do que 1 e menor do que 'n'.\n");
    }

    mdc = mdc_dois_numeros(n,a); // mdc para calcular as outras soluções
    if (mdc == 1) { // maior divisor comum igual a 1 significa que só existe uma solução
        printf("A equação \"%ld ⊗ x = %ld em Z=%ld\" só possui 1 solução: ", a, b, n); 
        t = t_euclides_estendido(n,a);
        // printf("t: %ld\n", t);
        inv = num_inverso(n,t);
        // printf("inverso: %ld\n", inv);
        x0 = (b * inv) % n; // primeira solução
        if (x0 < 0) x0 += n; // não pode ser negativo, é só somar o n
        printf("%ld", x0);
    }
    else if (b % mdc == 0) {
        printf("A equação \"%ld ⊗ x = %ld em Z=%ld\" possui %ld soluções:\n", a, b, n, mdc);
        t = t_euclides_estendido(n,a);
        x0 = (t * (b/mdc)) % n;
        if (x0 < 0) x0 += n;
        // printf("x = (%ld * %ld) %% %ld\n", b, inv, x0);
        printf("%ld", x0);
        for (i = 1; i < mdc; i++) {
            x = (x0 + i*(n/mdc)) % n; // fórmula para calcular outras soluções
            if (x < 0) x += n; // não pode ser negativo
            printf(", %ld", x);
        }
    }
    else printf("O mdc(n,a) não divide b, a equação não possui soluções");
    printf("\n");
}

long int num_inverso(long int n, long int t) {
    if (t < 0) t += n;
    long int inv = t % n;
    return inv;
}

void tcr() {
    int s = 0; // s = número de sistemas
    int i, j; // i,j são variáveis auxiliares
    while (s < 2) {
        printf("Número de sistemas a serem calculados: ");
        scanf("%d", &s);
        if (s < 2) printf("O número de sistemas deve ser maior que 1\n");
    }
    
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
    long int **tabela_tcr = NULL; 
    // se não igualar a NULL resulta em falha de segmentação depois de compilar

    tabela_tcr = aloca_matriz(s); // função que retorna uma matriz alocada
    
    long int m = 1; // número que armazena o m (m1*m2*m3*...*mi)
    
    /* 
     * 1. Mi = (m/mi);
     * 2. xi = Mi mod mi;
     * 3. yi = o inverso de xi em Zmi;
     * 4. solução de x = somatório de i = 1 indo até um número t calculando (ai * Mi * yi) mod m.
    */

    printf("Equação Referência: xi ≡ ai mod mi\n");
    for (i = 0; i < s; i++) {
        printf("Insira o a%d: ", i+1);
        scanf("%ld", &tabela_tcr[0][i]); // escaneando ai
    }
    printf("Equação Referência: xi ≡ ai mod mi\n");
    for (i = 0; i < s; i++) {
        printf("Insira o m%d: ", i+1);
        scanf("%ld", &tabela_tcr[1][i]); // escaneando mi
        m *= tabela_tcr[1][i]; // calculando m
    }
    // Para saber se tem solução, precisamos saber se o mdc entre
    // todos os números é 1, ou seja, se são primos entre si.
    
    for (i = 0; i < s; i++) {
        for (j = i+1; j < s; j++) {
            if (mdc_dois_numeros(tabela_tcr[1][i],tabela_tcr[1][j]) != 1) {
                printf("Os mi's não são primos entre si, o sistema não possui soluções\n");
                libera_matriz(tabela_tcr,s);
                return;
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

    long int t; // variável que armazena o t de euclides estendido (mi,xi)
    
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

    long int x = 0; // a solução do sistema
    for (i = 0; i < s; i++) x += tabela_tcr[6][i];
    x %= m;
    
    /* 
   TESTE:
   4 sistemas
   a1: 13
   a2: 11
   a3: 23
   a4: 3
   m1: 25
   m2: 27
   m3: 29
   m4: 32
   Resultado: 280163 
   */

    print_TCR(tabela_tcr,s,x);    
    libera_matriz(tabela_tcr,s);
} 

void print_TCR(long int **tabela_tcr, int s, long int x) {
    int i;
    printf("i              |");
    for (i = 0; i < s; i++) printf("%10d|", i);
    new_line();
    printf("ai             |");
    for (i = 0; i < s; i++) printf("%10ld|", tabela_tcr[0][i]);
    new_line();
    printf("mi             |");
    for (i = 0; i < s; i++) printf("%10ld|", tabela_tcr[1][i]);
    new_line();
    printf("Mi = m/mi      |");
    for (i = 0; i < s; i++) printf("%10ld|", tabela_tcr[2][i]);
    new_line();
    printf("xi = Mi mod mi |");
    for (i = 0; i < s; i++) printf("%10ld|", tabela_tcr[3][i]);
    new_line();
    printf("yi = (xi)-¹    |");
    for (i = 0; i < s; i++) printf("%10ld|", tabela_tcr[4][i]);
    new_line();
    printf("ai*Mi*yi       |");
    for (i = 0; i < s; i++) printf("%10ld|", tabela_tcr[5][i]);
    new_line();
    printf("ai*Mi*yi mod m |");
    for (i = 0; i < s; i++) printf("%10ld|", tabela_tcr[6][i]);
    new_line();
    printf("x0             |%10ld|",x);
}

// int verifica_tcr(long int **tabela, long int s, long int x) {
//     long int i;
//     float verifica;
//     for (i = 0; i < s; i++) {
//         verifica = (x - tabela[0][i]) / (float)tabela[1][0];
//         if (verifica % 1 != 0) return FALSE;
//     }
//     return TRUE;
// }

long int **aloca_matriz(int tam) {
    int i, j;
    long int **matriz = NULL;
    matriz = (long int **) calloc(sizeof(long int *),7);
    if (!matriz) {
        printf("Erro de alocação de memória!\n");
        return NULL;
    }
    for (i = 0; i < 7; i++) {
        matriz[i] = (long int *) calloc(sizeof(long int),tam);
        if (!matriz[i]) {
            printf("Erro de alocação de memória!\n");
            return NULL;
        }
    }
    return matriz;
}

void libera_matriz(long int **matriz, int tam) {
    int i, j;
    for (i = 0; i < 7; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

long int maior_numero (long int n1, long int n2) { // maior número entre dois números
    long int maior = (n1 > n2) ? n1 : n2;
    return maior;
}

void new_line() {
    printf("\n");
}

void end_msg() {
    printf("Obrigado por utilizar o programa :)\n");
    printf("~~~~~~~~########~~~~~~~~~~~~~~~~\n");
    printf("~~~~~#~~~~~~~~~~####~~~~~~~~~~~~\n");
    printf("~~#~~~~~~~~~~~~~~~~~##~~~~~~~~~~\n");
    printf("~~#~~~~~###~~~####~~~#~~~~~~~~~~\n");
    printf("##~~~~~~###~~~~##~~~~~##~~~~~~~~\n");
    printf("##~~~##~~~~~~~~~~~###~##~~~~~~~~\n");
    printf("##~~~#####~~~~~~####~~##~~~~~~~~\n");
    printf("~~#~~~~~#########~~~~#~~~~~~~~~~\n");
    printf("~~###~~~~~~~~~~~~~~~##~~~~~~~~~~\n");
    printf("~~~~####~~~~~~~~####~~~~~~~~~~~~\n");
    printf("~~~~~~~~########~~~~~~~~~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~~~###~~~~~###~~~~~\n");
    printf("~~~~~~~~~~~~~~#######~#######~~~\n");
    printf("~~~~~~~~~~~#####################\n");
    printf("~~~~~~~~~~~#####################\n");
    printf("~~~~~~~~~~~~~#################~~\n");
    printf("~~~~~~~~~~~~~~###############~~~\n");
    printf("~~~~~~~~~~~~~~~~###########~~~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~#####~~~~~~~~\n");
    printf("~~~~~~~~~~~~~~~~~~~~~#~~~~~~~~~~\n");
    printf("Volte sempre que quiser :*\n");
}
