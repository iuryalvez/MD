# UFG-MD
Repositório para códigos relacionados à disciplina de Matemática Discreta.

## Teoria dos Números

### Funções
  1. [**Crivo de Eratóstenes**](https://pt.wikipedia.org/wiki/Crivo_de_Eratóstenes)
  
      Encontra e imprime valores primos até um certo valor limite.
  
  2. **Maior divisor de um número**
  3. **Maior divisor comum entre dois números**
  4. **Árvore de fatores**
  
      Encontra quaisquer fatores do número, então os fatores destes números, etc, até que não seja possível fatorar mais.
  
  5. [**Algoritmo de Euclides**](https://pt.wikipedia.org/wiki/Algoritmo_de_Euclides)
    
      Sejam a, b ∈ N ∗ e c = a mod b.
    
      Então, mdc(a, b) = mdc(b, c).
  
  6. [**Algoritmo de Euclides estendido**](https://pt.wikipedia.org/wiki/Algoritmo_de_Euclides_estendido)

      Sejam a, b ∈ Z∗ e d = mdc(a, b).
    
      Então, existem s, t ∈ Z tais que d = sa + tb.
    
      De fato, mdc(a, b) é o menor valor positivo do conjunto
    
      {sa + tb t. q. s, t ∈ Z}.

  7. **Equação linear modular "a ⊗ x = b em Zn"**
      
      Dado os valores de a, b e n, exibe o x que satisfaz a equação.
      
  8. **Resolução de sistemas "xi ≡ ai mod mi"**
      
      "xi ≡ ai mod mi" Leia: "ai = x mod mi"
      
      Dado o número "i" de sistemas, os i números 'a' e i números 'm', exibe a solução x0 dos sistemas utilizando o teorema chinês do resto.

### Compilando e executando:

  Utilizando o gcc dentro da pasta de teoria dos números:

```  
gcc teoria-dos-numeros.c main.c -o teoria-dos-numeros.exe

./teoria-dos-numeros.exe
```
## Criptografia

### Funções
  1. **Descobrindo chave pública (RSA)**
  
      Dado uma chave privada (p,q,d), podemos descobrir sua chave pública (n,e) já que:
      * n = p*q;
      * phi(n) = (p-1)*(q-1);
      * d-¹ = e em Zphi(n);

  2. **Descobrindo chave privada (RSA)**

      Dado uma chave pública (n,e), podemos descobrir sua chave privada (p,q,d) com um processo intuitivo a partir de 1), temos que encontrar um número 'p' que divide 'n'. Encontrado p, q é o resultado da divisão de 'n' por 'p'.
      
      Com 'p' e 'q' podemos calcular calcular d, tendo em vista que d = e-¹ em Zphi(n).
      
  3. **Encriptar mensagem (RSA)**
  
      Função de codificação: E(M) = M^e mod n.
  
      Digamos que você queira encriptar uma mensagem para seu amigo Beto, para isso, deve-se ter a chave pública dele e encriptar a mensagem em cima disso. 
      
      Para M = 19, n = 973, e = 445. Deve-se resolver a potência: 19^445 mod 973.
      
  4. **Desencriptar mensagem (RSA)**
  
      Função de decodificação: D(N) = N^d mod n.
      
      Digamos que você queira desencriptar uma mensagem que sua amiga Ana lhe enviou, com posse de sua chave privada (p,q,d), você resolve a função de decodificação.  
      
      Para N = 649, p = 7, q = 139, d = 601. Deve-se resolver a potência: 649^601 mod 973.
  
### Compilando e executando:

  Utilizando o gcc dentro da pasta de criptografia:

```  
gcc criptografia.c main.c -o criptografia.exe

./criptografia.exe
```
