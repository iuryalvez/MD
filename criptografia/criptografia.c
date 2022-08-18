#include "criptografia.h"

lli maior_potencia(lli expoente, lli maior_pot) {
    if(pow(2,maior_pot+1) > expoente) return maior_pot;
    else return maior_potencia(expoente,maior_pot+1);
}

lli encriptar(lli p, lli q, lli e, lli m) {

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
    for (i = 0; i < maior_pot; i++) printf("\t[%lld^%lld]: %lld\n", m, pow(2,i), resultados[i]);
    printf("\n");

    i = maior_pot-1; // i recebe a maior potencia-1 porque uma posição no vetor começa com 0
    ant = resultados[i] % n; // primeiro valor a ser somado para descobrir a mensagem encriptada
    expo = expo-pow(2,i); // atualizando o expoente (quando for reduzido a 0 é porque acabou)

    printf("%lld^%lld = ", m, e); // printando o valor que quero encontrar
    printf("%lld^%lld ", m, pow(2,i)); // printando o valor de m elevado a uma potência próxima mais a outra...

    while(expo!=0){
        i = 1;
        i = maior_potencia(expo, i); // i recebe a maior potência do novo expoente
        ant = (ant * resultados[i]) % n; // ant recebe os valores acumulados dos resultados válidos
        expo = expo-pow(2,i); // atualizando o expoente para o próximo cálculo
        
        printf("+%% %lld^%lld", m, pow(2,i));
        if (expo == 0) printf("\n");
    }

    return ant;
}
