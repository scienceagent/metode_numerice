#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x) {
    // Define the actual function f(x) here, if needed
    return x * x + 2 * x + 1;
}

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
    int n = 7; // Number of points
    double x[] = {0.765, 1.867, 3.987, 5.601, 7.043, 9.231, 10.987};
    double y[] = {2.87611, 4.18432, 1.09673, -1.4587, -3.5729, 0.9876, 2.87644};

    double alpha = 1.276;
    printf("Interpolating for x=%.3f using Lagrange interpolation.\n", alpha);

    double result_interpolation = lagrange_interpolation(x, y, n, alpha);
    double result_actual = f(alpha);
    double error = fabs(result_interpolation - result_actual);

    printf("Valoarea f(x) pentru x=%.3f este: %.6f\n", alpha, result_interpolation);
    printf("Valoarea reala a lui f(x) pentru x=%.3f este: %.6f\n", alpha, result_actual);
    printf("Eroarea |f(x) - L_n(x)| este: %.6f\n", error);

    return 0;
}
