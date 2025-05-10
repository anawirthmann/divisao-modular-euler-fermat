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

    printf("==========================================================================\n");
    printf("  NESTE PROGRAMA SERAO USADOS OS SEGUINTES VALORES:\n");
    printf("  H, G, n  → três números inteiros positivos usados para calcular a base a\n");
    printf("  x  → expoente\n");
    printf("  n1 → módulo\n");
    printf("==========================================================================\n\n");
    printf("  Digite os valores de H, G, n, x, n1: ");

    scanf("%d %d %d %d %d", &H, &G, &n, &x, &n1);
    
    //etapa 1

    printf("\n  1) Verificando se G e n sao coprimos usando o Algoritmo de Euclides...\n");
    int d = calcular_mdc(G, n);
    
    printf("   → Entenda: Dois inteiros G e n são coprimos se mdc(G, n) = 1\n");//explicando
    
    if (d != 1)
      {
        printf("\n  mdc(%d, %d) = %d. Portanto, G e n nao sao coprimos. A divisao modular nao pode ser feita.\n", G, n, d);
        return 1;
      }
    printf("\n     G e n sao coprimos. Prosseguindo...\n");
    
    //etapa 2

    printf("\n  2) Calculando o inverso modular de G em Z_n...\n");
    int Ginv = calcular_inverso(G, n);
    
    printf("   → Entenda: O inverso de G módulo n é o número G⁻¹ tal que G * G⁻¹ ≡ 1 (mod n)\n");//explicando
    
    if (Ginv == -1)
      {
        printf("\n     G nao possui inverso modulo n. A divisao nao pode ser feita.\n");
        return 1;
      }
    printf("\n     O inverso de G = %d mod %d eh: %d\n", G, n, Ginv);
    printf("     Pois %d * %d ≡ 1 mod %d\n", G, Ginv, n);

    
    //etapa 3

    printf("\n  3) Calculando a = H * G⁻1 mod n...\n");
    int a = (H * Ginv) % n;
    
    printf("   → Entenda: Multiplicamos H pelo inverso de G para efetuar a divisão H ⊘ G módulo n\n");//explicando
    
    printf("\n     a = %d * %d mod %d = %d\n", H, Ginv, n, a);
    
    //etapa 4

    printf("\n  4) Verificando se a = %d e n1 = %d sao coprimos...\n", a, n1);
    
    printf("   → Entenda: Precisamos garantir que a e n1 sejam coprimos para aplicar Fermat ou Euler\n");//explicando
    
    if (calcular_mdc(a, n1) != 1)
      {
        printf("\n  a e n1 nao sao coprimos. O teorema nao se aplica.\n");
        return 1;
      }
    printf("\n     Verificado! a e n1 sao coprimos. Prosseguindo...\n");

    int x1;
    printf("\n  5) Verificando se n1 eh primo\n");
    if (verifica_primo(n1))
      {
        printf("\n     n1 eh primo.\n");
        
        printf("\n  6) Aplicando o Pequeno Teorema de Fermat...\n");
        x1 = n1 - 1;
        printf("   → Entenda: x1 representa a ordem de a módulo n1, definida por Fermat (n1 primo) ou por Euler (n1 não primo)\n");//explicando
        
        printf("\n     x1 = %d\n", x1);        
        
        printf("\n  7) *Passo 7 (Euler) nao se aplica pois n1 eh primo.\n");
      }
    else
      {
        printf("\n     n1 nao eh primo.\n");
        
        printf("\n  6) *Passo 6 (Fermat) nao se aplica pois n1 nao eh primo.\n");
        
        printf("\n  7) Aplicando o Teorema de Euler...\n");
        x1 = totiente(n1);
        printf("   → Entenda: x1 representa a ordem de a módulo n1, definida por Fermat (n1 primo) ou por Euler (n1 não primo)\n");//explicando
      
        printf("\n     x1 = %d\n", x1);
      }
    
    

    printf("\n  8) Decompondo x = x1 * q + r...\n");
    int q = x / x1;
    int r = x % x1;
    printf("     x = %d = %d * %d + %d\n", x, x1, q, r);

    printf("\n  9) Calculando exponenciacoes modulares...\n");
    int x2 = exp_mod(a, x1, n1);
    int parte1 = exp_mod(x2, q, n1);
    int parte2 = exp_mod(a, r, n1);
    
    printf("   → Entenda: Utilizamos a^x = (a^x1)^q * a^r, aplicando módulo n1 em cada etapa para manter os números controlados\n");//explicando

    printf("\n     x2 = a^x1 mod n1 = %d\n", x2);
    printf("     x2^q mod n1 = %d\n", parte1);
    printf("     a^r mod n1 = %d\n", parte2);

    int resultado = (parte1 * parte2) % n1;
    printf("\n  10) Etapa final: a^x mod n1 = ((%d^%d) * %d) mod %d = %d\n", x2, q, parte2, n1, resultado);
    printf("   → Entenda: Usamos propriedades da congruência modular para combinar os resultados das potências e obter o valor final\n");//explicando
   
    printf("\n  Resultado: %d\n", resultado);
    printf("\n=====================================================================================================================\n");
    
    printf("\nAna Beatriz Cunha Wirthmann - 190139048\n");

    return 0;
  }
