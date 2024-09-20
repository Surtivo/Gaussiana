#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define LARGURA 70
#define ALTURA 20

// Função para gerar um número aleatório com distribuição normal
void gerar_gaussiano(double *x1, double *x2) {
    double u1 = (double)rand() / RAND_MAX;
    double u2 = (double)rand() / RAND_MAX;
    double r = sqrt(-2.0 * log(u1));
    double theta = 2.0 * M_PI * u2;

    *x1 = r * cos(theta);
    *x2 = r * sin(theta);
}

// Função para gerar um número aleatório com distribuição normal com média mu e desvio sigma
double gaussiano(double mu, double sigma) {
    double x1, x2;
    gerar_gaussiano(&x1, &x2);
    return mu + sigma * x1;
}

// Função para calcular a densidade da distribuição normal
double densidade_gaussiana(double x, double mu, double sigma) {
    double exponencial = exp(-0.5 * pow((x - mu) / sigma, 2));
    return (1 / (sigma * sqrt(2 * M_PI))) * exponencial;
}

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Definições
    double mu = 0.0;       // Média
    double sigma = 1.0;    // Desvio padrão
    int n = 1000;          // Número de amostras
    int histograma[LARGURA] = {0}; // Contador para o histograma

    // Gerar amostras e preencher o histograma
    for (int i = 0; i < n; i++) {
        double valor = gaussiano(mu, sigma);
        int index = (int)((valor - mu) / (3 * sigma) * (LARGURA / 2) + (LARGURA / 2));
        if (index >= 0 && index < LARGURA) {
            histograma[index]++;
        }
    }

    // Encontrar o valor máximo no histograma para normalizar
    int max_valor = 0;
    for (int i = 0; i < LARGURA; i++) {
        if (histograma[i] > max_valor) {
            max_valor = histograma[i];
        }
    }

    // Plotar o gráfico
    for (int y = ALTURA; y >= 0; y--) {
        for (int x = 0; x < LARGURA; x++) {
            if ((histograma[x] * ALTURA / max_valor) >= y) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}


/*

COM SRAND:
A função rand realiza uma distribuição uniforme, então não é possível gerar uma Gaussiana com ela.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LARGURA 70
#define ALTURA 20
#define NUM_AMOSTRAS 1000

int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    // Contador para o histograma
    int histograma[LARGURA] = {0};

    // Gerar amostras e preencher o histograma
    for (int i = 0; i < NUM_AMOSTRAS; i++) {
        int valor = rand() % LARGURA; // Número aleatório entre 0 e LARGURA-1
        histograma[valor]++;
    }

    // Encontrar o valor máximo no histograma para normalizar
    int max_valor = 0;
    for (int i = 0; i < LARGURA; i++) {
        if (histograma[i] > max_valor) {
            max_valor = histograma[i];
        }
    }

    // Plotar o gráfico
    for (int y = ALTURA; y >= 0; y--) {
        for (int x = 0; x < LARGURA; x++) {
            if ((histograma[x] * ALTURA / max_valor) >= y) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
*/
