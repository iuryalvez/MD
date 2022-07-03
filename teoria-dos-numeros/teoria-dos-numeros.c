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
    printf("0 - SAIR\n");
    printf("1 - CRIVO DE ERATÓSTENES\n");
    printf("2 - MAIOR DIVISOR DE UM NÚMERO\n");
    printf("3 - MAIOR DIVISOR COMUM ENTRE DOIS NÚMEROS\n");
    printf("4 - ÁRVORE DE FATORES\n");
    printf("5 - ALGORITMO DE EUCLIDES\n");
    printf("6 - ALGORITMO DE EUCLIDES ESTENDIDO\n");
    printf("99 - LIMPAR A TELA\n");
}

void crivo_de_eratostenes(int n) {
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

int num_primo(int n) {
    int i; // divisor para saber se é primo
    int cont = 0; // conta divisores
    for (i = 1; i <= n/2; i++) if (n % i == 0) cont++; // verificação até n/2 porque não há fatores maiores que n/2 
    if (cont == 1) return TRUE;
    else return FALSE;
}

int mdc_dois_numeros(int n1, int n2) {
    int i, mdc;
    int maior;
    if (num_primo(n1) == TRUE) {
        printf("O primeiro número é primo.\n");
        if (num_primo(n2) == TRUE) printf("O segundo número é primo.\n");    
        return FALSE;
    }
    if (num_primo(n2) == TRUE) printf("O segundo número é primo.\n"); // i deve ser diferente de n1 e n2 pq não sabemos se um dos dois números é fator do outro
    maior = maior_numero(n1,n2);
    for (i = 1; i <= maior/2; i++) if (n1 % i == 0 && n2 % i == 0 && (i != n1 || i != n2)) mdc = i; // verificação simultânea dos divisores, vai atualizar sempre que encontrar um número que divide os dois
    return mdc;
}

int MDC(int n) {
    int i, mdc;
    for (i = 1; i < n/2; i++) {
        if (n % i == 0) mdc = i;
    }
    return mdc;
}

void arvore_de_fatores(int n) {
    int divisor = 2; // inicializar com 2 porque 1 divide todos
    int expoente = 0; // expoente padrão
    printf("%d = ", n); // primeiro print que é o número original
    while (n != 0) { // enquanto não chegarmos em n = 1, não vamos parar de dividí-lo
        if (n % divisor == 0) {
            n /= divisor; // se for um divisor, precisamos dividir n
            expoente++; // somar um ao expoente pq encontramos um fator
        }
        else { // se não for divisor
            if (expoente > 0) { // ver se encontramos um divisor antes, pq aí o expoente vai estar maior que 0 que é o padrão
                if (expoente == 1) printf("%d ", divisor); // se estiver igual a 1, então não precisamos printar ele elevado a 1
                else printf("%d^%d ", divisor, expoente); // se não, é maior que um e printa o número e sua potência
                if (n != 1) printf("* ");  // se o número não for o último, printa o sinal de multiplicação
            }
            if (n == 1) break;
            divisor++; // soma mais um ao divisor para encontrar o próximo
            expoente = 0; // retorna o expoente ao padrão 0
        }
    }
    printf("\n");
}

void euclides(int a, int b) {
    int n1 = a, n2 = b; // armazenando os números originais para printar no final
    int r = a % b, q = a/b; // primeira linha -> r é o resto, q é o quociente de a por b
    while (1) {
        printf("a: %5d | b: %5d | q: %2d | r: %2d\n", a, b, q, r); // printando primeiro pq vão ser atualizados daqui pra frente
        if (r == 0) { // condição de parada depois do printf pois imprimimos quando r é 0 também
            printf("mdc(%d,%d) = %d\n", n1, n2, b); // maior divisor comum entre os dois números, o b da última linha
            break;
        }
        a = b; // a se torna o b
        b = r; // b se torna o resto
        q = a/b; // novo quociente
        r = a % b; // resto dos novos a e b
    } // repete até r == 0
}

void euclides_estendido(int n1, int n2) {
    int *a, *b, *r, *q; // utilizando vetores para armazenar e calcular s e t futuramente
    a = (int *) malloc(sizeof(int)); // alocação padrão para armazenar UM int por enquanto
    b = (int *) malloc(sizeof(int));
    q = (int *) malloc(sizeof(int));
    r = (int *) malloc(sizeof(int));
    int cont = 0; // contador para ver quantas iterações há
    a[0] = n1;
    b[0] = n2;
    q[0] = n1/n2;
    r[0] = n1%n2;
    while (1) { // executando euclides para saber quantas iterações há para armazenarmos s e t em um vetor e printar depois
        cont++;
        if (r[cont-1] == 0) break; // importante: ver se o ultimo resto já é o mdc
        a = (int *) realloc(a,sizeof(int)*(cont+1)); // realocando memória para caber mais um elemento
        a[cont] = b[cont-1]; // o novo a é o antigo b 
        b = (int *) realloc(b,sizeof(int)*(cont+1));
        b[cont] = r[cont-1]; // o novo b é o antigo resto
        q = (int *) realloc(q,sizeof(int)*(cont+1));
        q[cont] = a[cont]/b[cont]; // o novo quociente
        r = (int *) realloc(r,sizeof(int)*(cont+1));
        r[cont] = a[cont] % b[cont]; // o novo resto
    }
    int *s = (int *) malloc(cont*sizeof(int)); // alocação padrão para um int
    int *t = (int *) malloc(cont*sizeof(int));
    s[0] = 0; // início predefinido de s e t
    t[0] = 1;
    int i = 1;
    while (i < cont) { // calcular s e t agora
        s[i] = t[i-1]; // fórmula do novo s
        t[i] = s[i-1] - (t[i-1]*q[cont-1-i]); // fórmula do novo t
        i++;
    }
    i = 0;
    printf("|iter.|    a    |    b    |  q  |   r   |   s   |   t   |\n"); // print formatado
    while (cont--) {
        printf("|%5d|%9d|%9d|%5d|%7d|%7d|%7d|\n", i,a[i],b[i],q[i],r[i],s[cont],t[cont]);
        i++;
    } 
    free(a);
    free(b);
    free(q);
    free(r);
    free(s);
    free(t); // liberando memória utilizada
}

int maior_numero (int n1, int n2) { // maior número entre dois números
    int maior;
    if (n1 > n2) maior = n1;
    else maior = n2;
    return maior;
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
