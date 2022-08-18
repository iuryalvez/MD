#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef long long int lli;

int main(){

    
    k = e;
    for(i=1; pow(2,i)<k; i++){

    }

    i--;

    (lli *) calloc(sizeof(lli),i);
    
    for(j=0; j<i; j++){
        v[j]= (Maux*Maux)%n;
        Maux = v[j];
    }

    ant = v[i] mod n;
    k = k-pow(2,i);

    while(k!=0){
        for(i=1; pow(2,i)<k; i++){}
        i--;
        ant = (ant * v[i]) % n;
        k = k-pow(2,i);
    }

    return 0;
}