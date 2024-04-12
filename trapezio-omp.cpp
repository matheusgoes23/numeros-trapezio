#include <stdio.h>
#include <math.h>
#include <omp.h>

double f(double x)
{ /* Calcula f(x) */
    double valor;
    valor = exp(x);
    return (valor);
}

int main(int argc, char *argv[])
{
    double integral;        /* Armazena resultado em integral */
    double a = 0.0, b = 1.0;/* Limite esquerdo e direito */
    long n = 8000000;       /* Número de Trapézios */
    double h;               /* Largura da base do Trapézio */
    h = (b - a) / n;
    integral = (f(a) + f(b)) / 2.0;
    double t_inicio = omp_get_wtime();

    // Recebendo a quantidade desejada de threads da linha de comando
    int num_threads = 1;
    if (argc > 1) {
        num_threads = atoi(argv[1]);
    }

    // Configurando o número de threads
    omp_set_num_threads(num_threads);

    // Paralelizando o loop
    #pragma omp parallel for reduction(+: integral) 
    for (long i = 1; i < n - 1; i++)
    {
        integral += f(a + i * h);
    }
    integral *= h;
    double t_fim = omp_get_wtime();

    printf("Com n = %ld trapézios a estimativa\n", n);
    printf("Da integral de %f até %f = %lf \n", a, b, integral);
    printf("Tempo: %f segundos com %d threads.\n", t_fim - t_inicio, num_threads);
    
    return (0);
}

