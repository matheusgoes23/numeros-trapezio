#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

double f(double x)
{ /* Calcula f(x) */
    double valor;
    valor = exp(x);
    return (valor);
}

int main(int argc, char *argv[])
{
    double integral;         /* Armazena resultado em integral */
    double a = 0.0, b = 1.0; /* Limite esquerdo e direito */
    long n = 8000000;        /* Número de Trapézios */
    double h;                /* Largura da base do Trapézio */
    clock_t inicio, fim;
    inicio = clock();
    h = (b - a) / n;
    integral = (f(a) + f(b)) / 2.0;

/* Usando OpenACC para paralelizar o loop */
#pragma acc parallel loop reduction(+ : integral)
    for (long i = 1; i < n - 1; i++)
    {
        integral += f(a + i * h);
    }
    integral *= h;

    fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    printf("Com n = %ld trapézios a estimativa\n", n);
    printf("Da integral de %f até %f = %lf \n", a, b, integral);
    printf("Tempo: %f segundos.\n", tempo);

    return (0);
}