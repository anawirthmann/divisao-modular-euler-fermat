/*
 ============================================================================
 Aluna: Ana Beatriz Cunha Wirthmann - 190139048
 Disciplina: Matemática Discreta II – 2025.1
 Professora: Cristiane Loesch de Souza Costa
 ============================================================================
*/
#include <stdio.h>



// ---------- FUNÇÕES AUXILIARES ----------


int calcular_mdc(int a, int b) 
// Calcula o MDC entre a e b usando o Algoritmo de Euclides
// Se mdc(a, b) == 1, então a e b são coprimos
  {
    while (b != 0)
      {
        int r = a % b;
        a = b;
        b = r;
      }
    return a;
  }


int verifica_primo(int n)
// Verifica se n é um número primo
// Retorna 1 se n for primo, 0 caso contrário
  {
    if (n < 2) return 0;
    for (int i = 2; i * i <= n; i++)
      {
        if (n % i == 0) return 0;
      }
    return 1;
  }


int calcular_inverso(int G, int n)
// Calcula o inverso modular de G módulo n usando o Algoritmo de Euclides Estendido
// Retorna x tal que (G * x) ≡ 1 mod n, se G e n forem coprimos
  {
    int t = 0, novo_t = 1;
    int r = n, novo_r = G;

    while (novo_r != 0)
      {
        int quoc = r / novo_r;
        int temp_t = t - quoc * novo_t;
        int temp_r = r - quoc * novo_r;
        t = novo_t;
        novo_t = temp_t;
        r = novo_r;
        novo_r = temp_r;
      }

    if (r > 1) return -1;
    if (t < 0) t += n;
    return t;
  }



int totiente(int n1)
// Calcula φ(n1), função totiente de Euler
// Conta quantos inteiros positivos menores que n1 são coprimos com n1
  {
    int resultado = n1;
    for (int i = 2; i * i <= n1; i++)
      {
        if (n1 % i == 0)
          {
            while (n1 % i == 0)
              n1 /= i;
            resultado -= resultado / i;
          }
      }
    if (n1 > 1)
      {
        resultado -= resultado / n1;
      }
    return resultado;
  }


int exp_mod(int base, int expoente, int modulo)
// Calcula (base^expoente) mod modulo
// Essa função é usada para fazer potências com números grandes, mas sem deixar o número explodir
// Ela multiplica a base várias vezes por ela mesma, sempre pegando o resto da divisão pelo modulo
// Para manter os números pequenos e o cálculo mais rápido, mesmo com expoentes altos
  {
    int resultado = 1;
    base = base % modulo;

    while (expoente > 0)
      {
        if (expoente % 2 == 1)
          resultado = (resultado * base) % modulo;
        base = (base * base) % modulo;
        expoente /= 2;
      }
    return resultado;
  }


// ---------- FUNÇÃO PRINCIPAL ----------


int main()
  {
    int H, G, n, x, n1;

    printf("Digite os valores de H, G, n, x, n1: ");
    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);

    printf("\n1) Verificando se G e n sao coprimos usando o Algoritmo de Euclides...\n");
    int d = calcular_mdc(G, n);
    if (d != 1)
      {
        printf("mdc(%d, %d) = %d. Portanto, G e n nao sao coprimos. A divisao modular nao pode ser feita.\n", G, n, d);
        return 1;
      }
    printf("G e n sao coprimos. Prosseguindo...\n");

    printf("\n2) Calculando o inverso modular de G em Z_n...\n");
    int Ginv = calcular_inverso(G, n);
    if (Ginv == -1)
      {
        printf("G nao possui inverso modulo n. A divisao nao pode ser feita.\n");
        return 1;
      }
    printf("Inverso de G = %d mod %d e: %d\n", G, n, Ginv);

    printf("\n3) Calculando a = H * G⁻1 mod n...\n");
    int a = (H * Ginv) % n;
    printf("a = %d * %d mod %d = %d\n", H, Ginv, n, a);

    printf("\n4) Verificando se a = %d e n1 = %d sao coprimos...\n", a, n1);
    if (calcular_mdc(a, n1) != 1)
      {
        printf("a e n1 nao sao coprimos. O teorema nao se aplica.\n");
        return 1;
      }
    printf("Verificado! a e n1 sao coprimos. Prosseguindo...\n");

    int x1;
    if (verifica_primo(n1))
      {
        printf("\n5) n1 e primo.\n");
        printf("6) Aplicando o Pequeno Teorema de Fermat...\n");
        x1 = n1 - 1;
        printf("7) Passo 7 (Euler) nao se aplica pois n1 e primo.\n");
      }
    else
      {
        printf("\n5) n1 nao e primo.\n");
        printf("6) Passo 6 (Fermat) nao se aplica pois n1 nao e primo.\n");
        printf("7) Aplicando o Teorema de Euler...\n");
        x1 = totiente(n1);
      }
    printf("x1 = %d\n", x1);

    printf("\n8) Decompondo x = x1 * q + r...\n");
    int q = x / x1;
    int r = x % x1;
    printf("x = %d = %d * %d + %d\n", x, x1, q, r);

    printf("\n9) Calculando exponenciacoes modulares...\n");
    int x2 = exp_mod(a, x1, n1);
    int parte1 = exp_mod(x2, q, n1);
    int parte2 = exp_mod(a, r, n1);

    printf("x2 = a^x1 mod n1 = %d\n", x2);
    printf("x2^q mod n1 = %d\n", parte1);
    printf("a^r mod n1 = %d\n", parte2);

    int resultado = (parte1 * parte2) % n1;
    printf("\n10) Resultado final: a^x mod n1 = ((%d^%d) * %d) mod %d = %d\n", x2, q, parte2, n1, resultado);

    return 0;
  }
