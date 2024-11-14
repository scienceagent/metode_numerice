#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double lagrange_interpolation(double *x, double *y, int n, double xi) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (j != i) {
                term *= (xi - x[j]) / (x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

int main() {
    int n;
    printf("Introduceti numarul de puncte: ");
    scanf("%d", &n);

    double *x = (double *)malloc(n * sizeof(double));
    double *y = (double *)malloc(n * sizeof(double));

    if (x == NULL || y == NULL) {
        printf("Eroare la alocarea memoriei!\n");
        return 1;
    }

    printf("Introduceti valorile lui x si y:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d]= ", i);
        scanf("%lf", &x[i]);
        printf("y[%d]= ", i);
        scanf("%lf", &y[i]);
    }

    double alpha;
    printf("Introduceti valoarea pentru x=alpha: ");
    scanf("%lf", &alpha);

    double result_interpolation = lagrange_interpolation(x, y, n, alpha);
    printf("Valoarea f(x) pentru x=%.3f este: %.6f\n", alpha, result_interpolation);

    // Aproximarea valorii funcției f(x) pentru x=alpha cu eroarea ε=10^(-4)
    double epsilon = 1e-4;
    int m = n;

    while (1) {
        double *xm = (double *)malloc(m * sizeof(double));
        double *ym = (double *)malloc(m * sizeof(double));

        if (xm == NULL || ym == NULL) {
            printf("Eroare la alocarea memoriei!\n");
            free(x);
            free(y);
            return 1;
        }

        for (int i = 0; i < m; i++) {
            xm[i] = x[i];
            ym[i] = y[i];
        }

        double result_high_precision = lagrange_interpolation(xm, ym, m, alpha);
        double error = fabs(result_high_precision - result_interpolation);

        free(xm);
        free(ym);

        if (error < epsilon) {
            printf("Aproximarea cu eroarea ε=10^(-4) pentru x=%.3f este: %.6f\n", alpha, result_high_precision);
            break;
        }

        // Mărește m pentru o aproximare mai bună
        m++;
    }

    // Eliberarea memoriei
    free(x);
    free(y);

    return 0;
}
