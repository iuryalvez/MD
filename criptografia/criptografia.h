#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE -1

typedef long long int lli;

struct private_key {
    lli p;
    lli q;
    lli d;
};

typedef struct private_key private_key;

struct public_key {
    lli n;
    lli e;
};

typedef struct public_key public_key;

void menu();

private_key chave_privada(public_key B);

lli t_euclides_estendido(lli n1, lli n2);

lli num_inverso(lli n, lli t);

lli inverter(lli phi, lli num);

lli maior_potencia(lli expoente, lli pot);

lli encriptar_RSA(lli p, lli q, lli e, lli m);
